/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDataSync.cpp
 * 概   要：数据同步线程。
 *                前置任务：数据处理线程 | 数据通信线程
 *                内容：1.基于前置任务，根据系统配置生成有效的显示数据和事件数据
 *                            2.添加有效的显示数据和事件数据至各自的缓冲区，并更新相应的数据库
 *                            3.根据配置决定是否刷新到数据库
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-6-16
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "threaddatasync.h"
#include "threaddatarecord.h"

#include <QMutex>
#include <QSharedMemory>
extern QSharedMemory                  g_sharedDataTable;//全局共享内存对象，Modbus寄存器分配表
extern DEVICE_CONFIG                   *p_gDeviceCfg;        //全局变量指针，指向LPSRAM中的设备配置结构

typedef struct DATA_STATUS_STRUCT {
    //系统当前记录状态，false--记录停止， true-记录运行中
    bool  recordStatus;
    //停止标记，true：表示下个测量周期数据是第一个采样数据点
    bool   stopFlag;
    //手动采样标记
    bool   manualSampleFlag;
    //记录个数，根据测量周期、显示记录周期计算：多少个测量数据生成一个显示数据
    quint32 dispRecordCount;
    //显示测量周期计数
    quint32 dispcounts;
    //记录个数，根据测量周期、事件记录周期计算：多少个测量数据生成一个事件数据
    quint32 eventRecordCount;
    //事件测量周期计数
    quint32 eventCounts;
}DATA_STATUS;

static QMutex   _statusLocker;    //数据状态锁
static DATA_STATUS  _dataStatus;//数据状态
static DISPLAY_DATA_RECORD     _displayDataRecord;    //显示数据缓冲
static EVENT_DATA_RECORD        _eventDataRecord;       //事件数据缓冲
static EVENT_DATA_RECORD        _manualDataRecord;    //手动采样数据缓冲
static REPORT_DATA_RECORD     _reportDataRecord;       //报表数据缓冲

//事件记录周期表
static const quint32 s_eventRecordInterval[EVNET_INTERVAL_NUM] = {
    Event_Record_Interval_100ms,
    Event_Record_Interval_200ms,
    Event_Record_Interval_500ms,
    Event_Record_Interval_1s,
    Event_Record_Interval_2s,
    Event_Record_Interval_5s,
    Event_Record_Interval_10s,
    Event_Record_Interval_15s,
    Event_Record_Interval_20s,
    Event_Record_Interval_30s,
    Event_Record_Interval_1min,
    Event_Record_Interval_2min,
    Event_Record_Interval_5min,
    Event_Record_Interval_10min,
    Event_Record_Interval_15min,
    Event_Record_Interval_20min,
    Event_Record_Interval_30min,
};

//事件记录周期对应的趋势周期表
static const quint32 s_trendDiv[EVNET_INTERVAL_NUM] = {
    5, 10, 15, 30, 60, 150, 300, 450, 600, 900, 1800, 3600, 9000, 18000, 27000, 36000, 54000,
};

/*
 * 功能：
 * 	  数据同步处理类静态成员函数，返回静态数据同步处理实例指针
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
ThreadDataSync *ThreadDataSync::instance()
{
    static ThreadDataSync data;
    return &data;
}

/*
 * 功能：
 * 	  数据记录状态修改
 * 参数：
 * 	  1.bool status：记录开始/结束
 * 返回值：
 * 	  无
 */
void ThreadDataSync::setRecordStatus(bool status)
{
    _statusLocker.lock();
    _dataStatus.recordStatus = status;
    _dataStatus.stopFlag = true;
    _statusLocker.unlock();

    ThreadDataRecord::instance()->m_startDispFlag = status;
    ThreadDataRecord::instance()->m_startEventFlag = status;
}

/*
 * 功能：
 * 	  启动手动采样
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataSync::setManualSample()
{
    _statusLocker.lock();
    _dataStatus.manualSampleFlag = true;
    _statusLocker.unlock();
}

/*
 * 功能：
 * 	  数据同步处理类构造函数
 * 参数：
 * 	  1.QObject *parent: 父对象，默认为0
 * 返回值：
 * 	  无
 */
ThreadDataSync::ThreadDataSync(QObject *parent) :
    QObject(parent)
{
    mapInit();

    SyncProcess *syncProcess = new SyncProcess;
    syncProcess->moveToThread(&m_dataSyncThread);
    connect(&m_dataSyncThread, &QThread::finished, syncProcess, &QObject::deleteLater);

    connect(this, &ThreadDataSync::sigSyncData, syncProcess, &SyncProcess::slotSyncProcess);
    connect(syncProcess, &SyncProcess::sigResultReady, this, &ThreadDataSync::slotHandleResults);

    m_dataSyncThread.start();
}

/*
 * 功能：
 * 	  事件记录周期与趋势周期映射表初始化
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataSync::mapInit()
{
    for (int i=0; i<EVNET_INTERVAL_NUM; ++i){
        m_event2display[s_eventRecordInterval[i]] = s_trendDiv[i];
    }
}

/*
 * 功能：
 * 	  槽函数，在数据同步工作完成后调用
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataSync::slotHandleResults()
{
}

/*
 * 功能：
 * 	  槽函数，周期配置修改处理函数
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataSync::slotPeriodChanged()
{
    quint8 countDIV;

    quint32 testPeriod, dispPeriod, eventPeriod;

    //测量周期
    testPeriod = p_gDeviceCfg->measureInterval_ms;
    //事件记录周期
    eventPeriod = p_gDeviceCfg->eventRecordInterval_ms;

    //事件记录模式时，参考事件记录周期与趋势周期关系表
    if (Record_Mode_Event == p_gDeviceCfg->recordMode)
        dispPeriod = m_event2display.value(eventPeriod);
    else
        dispPeriod = p_gDeviceCfg->displayTrend.trendInterval_s;

    countDIV = dispPeriod>Trend_Interval_10s ? 30 : 50;

    _statusLocker.lock();
    _dataStatus.dispRecordCount = dispPeriod * 1000 / countDIV / testPeriod;
    _dataStatus.eventRecordCount = eventPeriod / testPeriod;
    _statusLocker.unlock();

    qDebug("Test Period: %dms, Event Period:%dms, Display Period:%ds\n", testPeriod, eventPeriod, dispPeriod);
    qDebug("Display buffer count:%d, Event buffer count:%d\n", _dataStatus.dispRecordCount, _dataStatus.eventRecordCount);
}

/*************************数据同步处理工作对象***************************/
/*
 * 功能：
 * 	  槽函数，运行于数据同步线程，根据系统当前状态及配置，生成显示数据、事件数据
 * 以及手动采样数据，并根据需要刷新响应的数据库
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void SyncProcess::slotSyncProcess()
{
    _statusLocker.lock();
    //显示、事件数据生成
    if (_dataStatus.recordStatus && _dataStatus.stopFlag) { //记录开始且是第一次
        dataBufferProcess(true);
        _dataStatus.dispcounts = 1;
        _dataStatus.eventCounts = 1;
        _dataStatus.stopFlag = false;
    } else if (_dataStatus.recordStatus) { //记录运行中
        dataBufferProcess(false);
        _dataStatus.dispcounts++;
        _dataStatus.eventCounts++;
    } else {    //记录已停止，清空测量周期计数
        _dataStatus.dispcounts = 0;
        _dataStatus.eventCounts = 0;
    }

    //手动采样数据处理
    if (_dataStatus.manualSampleFlag){
        dataSampleProcess();
        _dataStatus.manualSampleFlag  = false;
        ThreadDataRecord::instance()->newManualData(&_manualDataRecord);
        emit sigManualDataReady();
    }

    //有效显示数据信号发射
    if (_dataStatus.dispcounts == _dataStatus.dispRecordCount){
        _dataStatus.dispcounts = 0;
        if (p_gDeviceCfg->recordMode != Record_Mode_Event)
            ThreadDataRecord::instance()->newDispData(&_displayDataRecord);
        emit sigDispDataReady();
    }

    //有效事件数据信号发射
    if (_dataStatus.eventCounts == _dataStatus.eventRecordCount){
        _dataStatus.eventCounts = 0;
        if (p_gDeviceCfg->recordMode != Record_Mode_Display)
            ThreadDataRecord::instance()->newEventData(&_eventDataRecord);
        emit sigEventDataReady();
    }
    _statusLocker.unlock();

    //数据同步完成信号
    emit   sigResultReady();
}

/*
 * 功能：
 * 	  数据帧缓冲，并根据配置生成相应的显示数据、事件数据
 * 参数：
 * 	  bool first：ture--记录开始的第一帧数据， false---非记录开始的第一帧数据
 * 返回值：
 * 	  无
 */
void SyncProcess::dataBufferProcess(bool first)
{
    MODBUS_REGISTER_MAP *pModbusRegMap;
    float * pData;
    quint8 *pDataDIO;

    g_sharedDataTable.lock();
    pModbusRegMap = const_cast<MODBUS_REGISTER_MAP*>(static_cast<MODBUS_REGISTER_MAP const *>(g_sharedDataTable.constData()));
    if (first) {
        //本机AI类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; i++){
            for (int j=0; j<UNIT_CHAN_NUM_PRE; j++){
                pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[i*100+(j<<1)];
                _displayDataRecord.mainUnit_AI_Data[i][j].Max = *pData;
                _displayDataRecord.mainUnit_AI_Data[i][j].Min = *pData;

                _eventDataRecord.mainUnit_AI_Data[i][j] = *pData;
            }
        }
        //扩展AI类型通道数据
        for (int i=0; i<EXT_UNIT_NUM; ++i){
            for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                for (int k=0; k<UNIT_CHAN_NUM_PRE; ++k){
                    switch (i) {
                    case 0:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit1_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 1:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit2_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 2:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit3_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 3:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit4_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 4:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit5_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 5:
                    default:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit6_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    }

                    _displayDataRecord.extUnit_AI_Data[i][j][k].Max = *pData;
                    _displayDataRecord.extUnit_AI_Data[i][j][k].Min = *pData;

                    _eventDataRecord.extUnit_AI_Data[i][j][k] = *pData;
                }
            }
        }

        //本机DI类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
            for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
                pDataDIO = &pModbusRegMap->coil_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
                _displayDataRecord.mainUnit_DI_Data[i][j].Max = *pDataDIO;
                _displayDataRecord.mainUnit_DI_Data[i][j].Min = *pDataDIO;

                _eventDataRecord.mainUnit_DI_Data[i][j] = *pDataDIO;
            }
        }

        //本机DO类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
            for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
                pDataDIO = &pModbusRegMap->relay_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
                _displayDataRecord.mainUnit_DO_Data[i][j].Max = *pDataDIO;
                _displayDataRecord.mainUnit_DO_Data[i][j].Min = *pDataDIO;

                _eventDataRecord.mainUnit_DO_Data[i][j] = *pDataDIO;
            }
        }

        //MATH通道数据
        for (int i=0; i<MAIN_UNIT_MATH_CHAN_NUM_PRE; ++i){
            pData = (float *)&pModbusRegMap->inputReg_MainUnit_Math_Data_Float32[i<<1];
            _displayDataRecord.device_Math_Data[i].Max = *pData;
            _displayDataRecord.device_Math_Data[i].Min = *pData;

            _eventDataRecord.device_Math_Data[i] = *pData;
        }

        //COMM通道数据
        for (int i=0; i<MAIN_UNIT_COMM_CHAN_NUM_PRE; ++i){
            pData = (float *)&pModbusRegMap->holdReg_MainUnit_Comm_Data_Float32[i<<1];
            _displayDataRecord.device_Comm_Data[i].Max = *pData;
            _displayDataRecord.device_Comm_Data[i].Min = *pData;

            _eventDataRecord.device_Comm_Data[i] = *pData;
        }
    } else {
        //本机AI类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; i++){
            for (int j=0; j<UNIT_CHAN_NUM_PRE; j++){
                pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[i*100+(j<<1)];
                _displayDataRecord.mainUnit_AI_Data[i][j].Max =\
                        _displayDataRecord.mainUnit_AI_Data[i][j].Max>(*pData) ? _displayDataRecord.mainUnit_AI_Data[i][j].Max : (*pData);
                _displayDataRecord.mainUnit_AI_Data[i][j].Min = \
                        _displayDataRecord.mainUnit_AI_Data[i][j].Min<(*pData) ? _displayDataRecord.mainUnit_AI_Data[i][j].Min : (*pData);

                _eventDataRecord.mainUnit_AI_Data[i][j] = *pData;
            }
        }
        //扩展AI类型通道数据
        for (int i=0; i<EXT_UNIT_NUM; ++i){
            for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                for (int k=0; k<UNIT_CHAN_NUM_PRE; ++k){
                    switch (i) {
                    case 0:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit1_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 1:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit2_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 2:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit3_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 3:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit4_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 4:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit5_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    case 5:
                    default:
                        pData = (float *)&pModbusRegMap->inputReg_ExtUnit6_IO_Data_Float32[j*100 + (k<<1)];
                        break;
                    }

                    _displayDataRecord.extUnit_AI_Data[i][j][k].Max = \
                            _displayDataRecord.extUnit_AI_Data[i][j][k].Max>(*pData) ? _displayDataRecord.mainUnit_AI_Data[i][j].Max : (*pData);
                    _displayDataRecord.extUnit_AI_Data[i][j][k].Min = \
                            _displayDataRecord.extUnit_AI_Data[i][j][k].Min<(*pData) ? _displayDataRecord.extUnit_AI_Data[i][j][k].Min : (*pData);

                    _eventDataRecord.extUnit_AI_Data[i][j][k] = *pData;
                }
            }
        }

        //本机DI类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
            for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
                pDataDIO = &pModbusRegMap->coil_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
                _displayDataRecord.mainUnit_DI_Data[i][j].Max = \
                        _displayDataRecord.mainUnit_DI_Data[i][j].Max>(*pDataDIO) ? _displayDataRecord.mainUnit_DI_Data[i][j].Max : (*pDataDIO);
                _displayDataRecord.mainUnit_DI_Data[i][j].Min = \
                        _displayDataRecord.mainUnit_DI_Data[i][j].Min<(*pDataDIO) ? _displayDataRecord.mainUnit_DI_Data[i][j].Min : (*pDataDIO);

                _eventDataRecord.mainUnit_DI_Data[i][j] = *pDataDIO;
            }
        }

        //本机DO类型通道数据
        for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
            for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
                pDataDIO = &pModbusRegMap->relay_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
                _displayDataRecord.mainUnit_DO_Data[i][j].Max = \
                        _displayDataRecord.mainUnit_DO_Data[i][j].Max>(*pDataDIO) ? _displayDataRecord.mainUnit_DO_Data[i][j].Max : (*pDataDIO);
                _displayDataRecord.mainUnit_DO_Data[i][j].Min = \
                        _displayDataRecord.mainUnit_DO_Data[i][j].Min<(*pDataDIO) ? _displayDataRecord.mainUnit_DO_Data[i][j].Min : (*pDataDIO);

                _eventDataRecord.mainUnit_DO_Data[i][j] = *pDataDIO;
            }
        }

        //MATH通道数据
        for (int i=0; i<MAIN_UNIT_MATH_CHAN_NUM_PRE; ++i){
            pData = (float *)&pModbusRegMap->inputReg_MainUnit_Math_Data_Float32[i<<1];
            _displayDataRecord.device_Math_Data[i].Max = \
                    _displayDataRecord.device_Math_Data[i].Max>(*pData) ? _displayDataRecord.device_Math_Data[i].Max : (*pData);
            _displayDataRecord.device_Math_Data[i].Min = \
                    _displayDataRecord.device_Math_Data[i].Min<(*pData) ? _displayDataRecord.device_Math_Data[i].Min : (*pData);

            _eventDataRecord.device_Math_Data[i] = *pData;
        }

        //COMM通道数据
        for (int i=0; i<MAIN_UNIT_COMM_CHAN_NUM_PRE; ++i){
            pData = (float *)&pModbusRegMap->holdReg_MainUnit_Comm_Data_Float32[i<<1];
            _displayDataRecord.device_Comm_Data[i].Max = \
                    _displayDataRecord.device_Comm_Data[i].Max>(*pData) ? _displayDataRecord.device_Comm_Data[i].Max : (*pData);
            _displayDataRecord.device_Comm_Data[i].Min = \
                    _displayDataRecord.device_Comm_Data[i].Min<(*pData) ? _displayDataRecord.device_Comm_Data[i].Min : (*pData);

            _eventDataRecord.device_Comm_Data[i] = *pData;
        }
    }
    g_sharedDataTable.unlock();
}

/*
 * 功能：
 * 	  采样数据处理函数
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void SyncProcess::dataSampleProcess()
{
    MODBUS_REGISTER_MAP *pModbusRegMap;
    float * pData;
    quint8 *pDataDIO;

    g_sharedDataTable.lock();
    pModbusRegMap = const_cast<MODBUS_REGISTER_MAP*>(static_cast<MODBUS_REGISTER_MAP const *>(g_sharedDataTable.constData()));

    //本机AI类型通道数据
    for (int i=0; i<MAIN_UNIT_MODULE_NUM; i++){
        for (int j=0; j<UNIT_CHAN_NUM_PRE; j++){
            pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[i*100+(j<<1)];
            _manualDataRecord.mainUnit_AI_Data[i][j] = *pData;
        }
    }

    //扩展AI类型通道数据
    for (int i=0; i<EXT_UNIT_NUM; ++i){
        for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
            for (int k=0; k<UNIT_CHAN_NUM_PRE; ++k){
                switch (i) {
                case 0:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit1_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                case 1:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit2_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                case 2:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit3_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                case 3:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit4_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                case 4:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit5_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                case 5:
                default:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit6_IO_Data_Float32[j*100 + (k<<1)];
                    break;
                }
                _manualDataRecord.extUnit_AI_Data[i][j][k] = *pData;
            }
        }
    }

    //本机DI类型通道数据
    for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
        for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
            pDataDIO = &pModbusRegMap->coil_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
            _manualDataRecord.mainUnit_DI_Data[i][j] = *pDataDIO;
        }
    }

    //本机DO类型通道数据
    for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i) {
        for(int j=0; j<UNIT_CHAN_NUM_PRE; ++j){
            pDataDIO = &pModbusRegMap->relay_MainUnit_IO_Data_Bit[i*UNIT_CHAN_NUM_PRE + j];
            _manualDataRecord.mainUnit_DO_Data[i][j] = *pDataDIO;
        }
    }

    //MATH通道数据
    for (int i=0; i<MAIN_UNIT_MATH_CHAN_NUM_PRE; ++i){
        pData = (float *)&pModbusRegMap->inputReg_MainUnit_Math_Data_Float32[i<<1];
        _manualDataRecord.device_Math_Data[i] = *pData;
    }

    //COMM通道数据
    for (int i=0; i<MAIN_UNIT_COMM_CHAN_NUM_PRE; ++i){
        pData = (float *)&pModbusRegMap->holdReg_MainUnit_Comm_Data_Float32[i<<1];
        _manualDataRecord.device_Comm_Data[i] = *pData;
    }
    g_sharedDataTable.unlock();
}
