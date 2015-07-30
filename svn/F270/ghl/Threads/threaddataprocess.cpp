/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDataProcess.cpp
 * 概   要：数据处理线程，包含子板卡通信工作对象、运算通道计算工作对象
 *      ---基于Modbus协议，对板内RS485总线上的子板卡进行数据查询，并根据通道配
 * 置做简单的运算，最后将数据各通道数据映射到原始数据对象中。
 *      ---基于原始数据对象，对各运算通道进行计算，并更新Modbus寄存器分配表（共
 * 享 内存）
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-7-8
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "threaddataprocess.h"

#include <QDebug>
#include <QBitArray>
#include <QSharedMemory>

MODBUS_REGISTER_MAP  g_originDataMap;   //全局变量，原始数据对象

extern DEVICE_CONFIG                   *p_gDeviceCfg;        //全局变量指针，指向LPSRAM中的设备配置结构
extern QSharedMemory                  g_sharedDataTable;//全局共享内存对象，Modbus寄存器分配表

static Math_Status_Type _mathStatus;    //系统当前运算状态

/*
 * 功能：
 * 	  获取基准通道测量值，如果基准通道号比当前通道号大，则取基准通道上次测量值，否则取当前测量值
 * 参数：
 * 	  1.quint32 self: 当前通道编码
 *       2.quint32 basic：基准通道编码
 * 返回值：
 * 	  基准通道测量值
 */
float getChannelData(quint32 self, quint32 basic)
{
    MODBUS_REGISTER_MAP *pModbusRegMap;
    quint16 chanType, uninNum, moduleIndex, number;
    float * pData;
    quint8 *pDataDIO;

    chanType = CHANNEL_TYPE(basic);           //通道类型
    uninNum = CHANNEL_UNIT(basic);           //单元号
    moduleIndex = CHANNEL_MODULE(basic);  //卡槽号
    number = CHANNEL_NUM(basic);              //通道号

    if(self<basic) {
         //获取basic通道上次测量值
        return CfgChannel::instance()->getChannelData(basic).toFloat();
    } else {
        //获取basic通道本次测量值
        pModbusRegMap = &g_originDataMap;
        switch(chanType){
        case Channel_Type_AI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
                if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                    goto ERR;
                } else {
                    pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2+(number<<1)];
                }
            } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
                switch (uninNum){
                case CHANNEL_UNIN_EXT1:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit1_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                case CHANNEL_UNIN_EXT2:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit2_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                case CHANNEL_UNIN_EXT3:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit3_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                case CHANNEL_UNIN_EXT4:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit4_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                case CHANNEL_UNIN_EXT5:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit5_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                case CHANNEL_UNIN_EXT6:
                    pData = (float *)&pModbusRegMap->inputReg_ExtUnit6_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE*2 + (number<<1)];
                    break;
                default:
                    goto ERR;
                }
            } else {
                goto ERR;
            }
            return *pData;
        case Channel_Type_DI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE + number];
            } else {    //DI不支持扩展单元
                goto ERR;
            }
            return *pData;
        case Channel_Type_DO:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
                pDataDIO = &pModbusRegMap->relay_MainUnit_IO_Data_Bit[moduleIndex*UNIT_CHAN_NUM_PRE + number];
            } else {    //DO不支持扩展单元
                goto ERR;
            }
            return *pDataDIO;
        case Channel_Type_Math:
            if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
                goto ERR;

            pData = (float *)&pModbusRegMap->inputReg_MainUnit_Math_Data_Float32[number<<1];
            return *pData;
        case Channel_Type_Comm:
            if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
                goto ERR;

            pData = (float *)&pModbusRegMap->holdReg_MainUnit_Comm_Data_Float32[number<<1];
            return *pData;
        default:
            goto ERR;
        }
    }

ERR:
        return 0;
}

/*
 * 功能：
 * 	  子板卡数据处理类静态成员函数，返回静态数据处理实例指针
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
ThreadDataProcess *ThreadDataProcess::instance()
{
    static ThreadDataProcess data;
    return &data;
}

/*
 * 功能：
 * 	  运算状态设定
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataProcess::setMathStatus(Math_Status_Type status)
{
    _mathStatus = status;
}

/*
 * 功能：
 * 	  测量周期切换
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataProcess::changeMeasurePeriod()
{
    if (m_dataQueryTimer.isActive()) {
        m_dataQueryTimer.stop();
    }
    m_dataQueryTimer.start(p_gDeviceCfg->measureInterval_ms<100 ? 100 : p_gDeviceCfg->measureInterval_ms);
}

/*
 * 功能：
 * 	  子板卡数据处理类构造函数
 * 参数：
 * 	  1.QObject *parent: 父对象，默认为0
 * 返回值：
 * 	  无
 */
ThreadDataProcess::ThreadDataProcess(QObject *parent) :
    QObject(parent)
{
    char * pDataTable;

    //共享内存attach/create
    g_sharedDataTable.setKey(MODBUS_MAP_KEY);
    if (g_sharedDataTable.create(sizeof(MODBUS_REGISTER_MAP))) {
        //初始化
        g_sharedDataTable.lock();
        pDataTable = static_cast<char*>(g_sharedDataTable.data());
        ::memset(pDataTable, 0, sizeof(MODBUS_REGISTER_MAP));
        g_sharedDataTable.unlock();
    } else {
        if (g_sharedDataTable.error() == QSharedMemory::AlreadyExists) {
            g_sharedDataTable.attach();
            g_sharedDataTable.detach();
            if (g_sharedDataTable.create(sizeof(MODBUS_REGISTER_MAP))) {
                g_sharedDataTable.lock();
                pDataTable = static_cast<char*>(g_sharedDataTable.data());
                ::memset(pDataTable, 0, sizeof(MODBUS_REGISTER_MAP));
                g_sharedDataTable.unlock();
            } else {
                qDebug()<<"Err CreateSharedMemory of data1";
            }
        } else {
            qDebug()<<"Err CreateSharedMemory of data2";
        }
    }

    //数据处理工作
    DataProcess *dataProcess = new DataProcess;
    dataProcess->moveToThread(&m_dataProcessThread);
    connect(&m_dataProcessThread, &QThread::finished, dataProcess, &QObject::deleteLater);

    connect(&m_dataQueryTimer, &QTimer::timeout, dataProcess, &DataProcess::slotDataQuery);
    connect(dataProcess, &DataProcess::sigResultReady, this, &ThreadDataProcess::sigDataProcessFinished);

    connect(this, SIGNAL(sigChannelConfigChangedAI(quint8,quint8,quint8)), dataProcess, SLOT(slotChannelConfigChangedAI(quint8,quint8,quint8)));

    //通道运算工作
    MathProcess *mathProcess = new MathProcess;
    mathProcess->moveToThread(&m_dataProcessThread);
    connect(&m_dataProcessThread, &QThread::finished, mathProcess, &QObject::deleteLater);

    connect(this, &ThreadDataProcess::sigDataProcessFinished, mathProcess, &MathProcess::slotMathProcess);
    connect(mathProcess, &MathProcess::sigResultReady, this, &ThreadDataProcess::sigMathProcessFinished);

    connect(this, SIGNAL(sigChannelConfigChangedMath(quint32)), mathProcess, SLOT(slotChannelConfigChangedMath(quint32)));

    m_dataProcessThread.start();
}

/************************子板卡数据处理工作对象*******************************************/

#define SERIAL_PORT_OF_SUBBOARD_DATA    "/dev/ttyUSB0"
#define SERIAL_PORT_OF_SUBBOARD_STATUS "/dev/ttyUSB1"
#define SERIAL_PORT_OF_BOARDRATE    1000000

static modbus_t *s_ctx_data = 0;        //modbus数据通信上下文指针
static modbus_t *s_ctx_status = 0;      //modbus状态及配置上下文指针

/*
 * 功能：
 * 	  槽函数，运行于数据处理线程，根据系统当前状态，获取各模块数据(输入寄存器)
 *       Step1: 获取各板卡输入数据，并映射到原始数据对象中
 *       Step2: 基于Step1中的原始数据对象，对各板卡数据进行查表、通道运算以及通道状态确定操作
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功返回0; 失败返回-1
 */
int DataProcess::slotDataQuery()
{
    SUB_BOARD_DATA  dataRev;
    SUB_BOARD_DATA_PROCESSED dataProcessed;
    bool extValidFlag = false;
    int extBoardNum = 0;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;

    if (!s_ctx_data)
        s_ctx_data = modbus_new_rtu(SERIAL_PORT_OF_SUBBOARD_DATA, SERIAL_PORT_OF_BOARDRATE, 'N', 8, 1);

    if (s_ctx_data == NULL){
        qDebug("Unable to allocate libmodbus data context\n");
        return -1;
    }

    //Step1-1:本机板卡(AI/DI/DO/DIO)数据查询---通道测量输入数据获取
    for (int i=1; i<=MAIN_UNIT_MODULE_NUM; ++i){
        modbus_set_slave(s_ctx_data, i);
        if (modbus_connect(s_ctx_data) == -1) {
            qDebug("Connection failed: %s\n", modbus_strerror(errno));
            return -1;
        }

        quint16 boardStatus = p_gDeviceCfg->sysStatus.mainUnit_ModuleStatus[i-1];
        if (STATUS_BOARD_TYPE(boardStatus)>STATUS_BOARD_TYPE_NONE \
            && STATUS_BOARD_TYPE(boardStatus) < STATUS_BOARD_TYPE_EXT \
            && STATUS_BOARD_STATUS(boardStatus) ){
            //运算数据清零
            ::memset(&dataProcessed, 0x00, sizeof(SUB_BOARD_DATA_PROCESSED));

            //获取板卡数据
            int boardRegMapSize = sizeof(SUB_BOARD_DATA)>>1;
            int rc = modbus_read_input_registers(s_ctx_data, 0x00, boardRegMapSize, (uint16_t *)&dataRev);

             //通道运算预处理
            if (rc != boardRegMapSize){
                for (int j=0; j<UNIT_CHAN_NUM_USE_MAX; ++j){
                    dataProcessed.dataStatus[j] |= DATA_ERROR_INVALID<<DATA_STATUS_ERROR_BITSOFF;
                }
            } else {
                dataInputProcess(&dataRev, &dataProcessed);
            }

            //测量输入数据（输入值）映射
            dataInputRemap(0, i-1, boardStatus, &dataProcessed);
        } else if(STATUS_BOARD_TYPE(boardStatus) == STATUS_BOARD_TYPE_EXT && STATUS_BOARD_EXT_STATUS(boardStatus)) {
            extValidFlag = true;
            extBoardNum = i;
        }

        modbus_close(s_ctx_data);
    }

    //Step1-2:扩展单元板卡(AI)数据查询---通道测量输入数据获取
    if (extValidFlag) {
        modbus_set_slave(s_ctx_data, extBoardNum);

        if (modbus_connect(s_ctx_data) == -1) {
            qDebug("Connection failed: %s\n", modbus_strerror(errno));
            return -1;
        }

        for (int i=0; i<EXT_UNIT_NUM; ++i){
            for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                quint16 boardStatus = p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j];
                int boardRegMapSize = sizeof(SUB_BOARD_DATA)>>1;
                int regAddr = i * (boardRegMapSize * EXT_UNIT_MODULE_NUM) + boardRegMapSize * j;
                if (STATUS_BOARD_TYPE(boardStatus) == STATUS_BOARD_TYPE_AI && STATUS_BOARD_STATUS(boardStatus)){
                    //运算数据清零
                    ::memset(&dataProcessed, 0x00, sizeof(SUB_BOARD_DATA_PROCESSED));

                    //从主机扩展板卡上获取各扩展单元上的板卡数据
                    int rc = modbus_read_input_registers(s_ctx_data, regAddr, boardRegMapSize, (uint16_t *)&dataRev);

                    //通道运算预处理
                   if (rc != boardRegMapSize){
                       for (int k=0; k<UNIT_CHAN_NUM_USE_MAX; ++k){
                           dataProcessed.dataStatus[k] |= DATA_ERROR_INVALID<<DATA_STATUS_ERROR_BITSOFF;
                       }
                   } else {
                       dataInputProcess(&dataRev, &dataProcessed);
                   }

                   //测量输入数据（输入值）映射
                   dataInputRemap(i+1, j, boardStatus, &dataProcessed);
                }
            }
        }

        modbus_close(s_ctx_data);
    }

    //Step2-1:本机板卡 ---通道测量值查表、计算以及状态确定
    extValidFlag = false;
    for (int i=1; i<=MAIN_UNIT_MODULE_NUM; ++i){
        quint16 boardStatus = p_gDeviceCfg->sysStatus.mainUnit_ModuleStatus[i-1];
        quint8 boardType = STATUS_BOARD_TYPE(boardStatus);
        quint8 boardCh0  = STATUS_BOARD_CHAN0_NUM(boardStatus);
        if (boardType>STATUS_BOARD_TYPE_NONE && boardType < STATUS_BOARD_TYPE_EXT \
            && STATUS_BOARD_STATUS(boardStatus) ){
            switch (boardType){
            case STATUS_BOARD_TYPE_AI:
                for (int j=0; j<boardCh0 && j<UNIT_CHAN_NUM_PRE; ++j){
                    pAIConfig = &p_gDeviceCfg->mainUnitAI[i-1][j];
                    chanAICalculate(0, i-1, j, pAIConfig);
                }
                break;
            case STATUS_BOARD_TYPE_DI:
                for (int j=0; j<boardCh0 && j<UNIT_CHAN_NUM_PRE; ++j) {
                    pDIConfig = &p_gDeviceCfg->mainUnitDI[i-1][j];
                    chanDICalculate(i-1, j, pDIConfig);
                }
                break;
            case STATUS_BOARD_TYPE_DO:
                //DO通道无相关运算
                break;
            case STATUS_BOARD_TYPE_DIO:
                for (int j=0; j<boardCh0 && j<UNIT_CHAN_NUM_PRE; ++j) {
                    pDIConfig = &p_gDeviceCfg->mainUnitDI[i-1][j];
                    chanDICalculate(i-1, j, pDIConfig);
                }
                break;
            default:
                break;
            }
        } else if(STATUS_BOARD_TYPE(boardStatus) == STATUS_BOARD_TYPE_EXT && STATUS_BOARD_EXT_STATUS(boardStatus)) {
            extValidFlag = true;
        }

    }

    //Step2-2:扩展单元板卡
    if (extValidFlag) {
        for (int i=0; i<EXT_UNIT_NUM; ++i){
            for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                quint16 boardStatus = p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j];
                quint8 boardType = STATUS_BOARD_TYPE(boardStatus);
                quint8 boardCh0  = STATUS_BOARD_CHAN0_NUM(boardStatus);
                if (boardType == STATUS_BOARD_TYPE_AI && STATUS_BOARD_STATUS(boardStatus)){
                    for (int k=0; k<boardCh0 && k<UNIT_CHAN_NUM_PRE; ++k){
                        pAIConfig = &p_gDeviceCfg->extUnitAI[i][j][k];
                        chanAICalculate(i+1, j, k, pAIConfig);
                    }
                }
            }
        }
    }

    //数据通信结束信号
    emit   sigResultReady();

    return 0;
}

/*
 * 功能：
 * 	  槽函数，子板卡状态查询（保持寄存器）
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功返回0; 失败返回-1
 */
int DataProcess::slotStatusQuery()
{
    SUB_BOARD_STATUS extStatus;
    quint16 boardStatus;
    bool extValidFlag = false;
    int extBoardNum = 0;

    if (!s_ctx_status)
        s_ctx_status = modbus_new_rtu(SERIAL_PORT_OF_SUBBOARD_STATUS, SERIAL_PORT_OF_BOARDRATE, 'N', 8, 1);

    if (s_ctx_status == NULL){
        qDebug("Unable to allocate libmodbus status context\n");
        return -1;
    }

    //本机板卡
    for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i){
        modbus_set_slave(s_ctx_status, i+1);
        if (modbus_connect(s_ctx_status) == -1) {
            qDebug("status port connection failed on Main: %s\n", modbus_strerror(errno));
            return -1;
        }

        //获取板卡状态
        int rc = modbus_read_registers(s_ctx_status, 0x00, 1, (uint16_t *)&boardStatus);
        if (rc == -1) {
            p_gDeviceCfg->sysStatus.mainUnit_ModuleStatus[i] = 0;
        } else {
            p_gDeviceCfg->sysStatus.mainUnit_ModuleStatus[i] = boardStatus;
        }

        if (STATUS_BOARD_TYPE(boardStatus) == STATUS_BOARD_TYPE_EXT && STATUS_BOARD_EXT_STATUS(boardStatus)){
            extValidFlag = true;
            extBoardNum = i+1;
        }
        modbus_close(s_ctx_status);
    }

    //扩展板卡
    if(extValidFlag) {
        modbus_set_slave(s_ctx_status, extBoardNum);
        if (modbus_connect(s_ctx_status) == -1) {
            qDebug("status port connection failed on Ext: %s\n", modbus_strerror(errno));
            return -1;
        }

        //获取本机扩展板卡状态
        int extRegMapSize = sizeof(SUB_BOARD_STATUS)>>1;
        int rc = modbus_read_registers(s_ctx_status, 0x00, extRegMapSize, (uint16_t *)&extStatus);

        if (rc != extRegMapSize) {  //各扩展单元板卡状态复位
            for (int i=0; i<EXT_UNIT_NUM; ++i){
                for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                     p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j] = 0;
                }
            }
        } else {    //获取各扩展单元板卡状态
            for (int i=0; i<EXT_UNIT_NUM; ++i){
                for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                    if (extStatus.config.dataExtStatus[i][j] == EXT_VALID){
                        int boardRegMapSize = sizeof(SUB_BOARD_STATUS)>>1;
                        int regAddr = boardRegMapSize + i * (boardRegMapSize * EXT_UNIT_MODULE_NUM) + boardRegMapSize * j;
                        int rc = modbus_read_registers(s_ctx_status, regAddr, 1, (uint16_t *)&boardStatus);
                        if (rc == 1)
                            p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j] = boardStatus;
                        else
                            p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j] = 0;
                    }
                }
            }
        }

        modbus_close(s_ctx_status);
    }

    return 0;
}

/*
 * 功能：
 * 	  槽函数，AI板卡配置变更处理函数
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void DataProcess::slotChannelConfigChangedAI(quint8 unit, quint8 module, quint8 channel)
{
    if (0 == unit && module<MAIN_UNIT_MODULE_NUM && channel<AI_UNIT_CHAN_NUM_USE) {    //本机
        m_mainUnit_Moving[module][channel].clear();
        m_mainUnit_RateInc[module][channel].clear();
        m_mainUnit_RateDec[module][channel].clear();

        m_mainUnit_DelayUpper[module][channel] = 0;
        m_mainUnit_DelayDowner[module][channel] = 0;
    } else if (unit < EXT_UNIT_NUM && module<EXT_UNIT_MODULE_NUM \
               && channel<AI_UNIT_CHAN_NUM_USE){ //扩展单元
        m_extUnit_Moving[unit][module][channel].clear();
        m_extUnit_RateInc[unit][module][channel].clear();
        m_extUnit_RateDec[unit][module][channel].clear();

        m_extUnit_DelayUpper[unit][module][channel] = 0;
        m_extUnit_DelayDowner[unit][module][channel] = 0;
    }
}

/*
 * 功能：
 * 	  输入值处理，测量通道输入数据预处理
 * 参数：
 * 	  1.SUB_BOARD_DATA *dataSrc：模块查询数据
 *       2.SUB_BOARD_DATA_PROCESSED *dataDest：模块查询数据结算结果
 * 返回值：
 * 	  无
 */
void DataProcess::dataInputProcess(SUB_BOARD_DATA *dataSrc, SUB_BOARD_DATA_PROCESSED *dataDest)
{
    //AI类型通道测量输入数据拷贝
    ::memcpy(dataDest->dataSample, dataSrc->dataSample, sizeof(float)*UNIT_CHAN_NUM_USE_MAX);
    //DI脉冲类型脉冲计数数据拷贝
    ::memcpy(dataDest->dataDICount, dataSrc->dataDICount, sizeof(quint32)*UNIT_CHAN_NUM_USE_MAX);
    //DI、DO类型通道输入数据、状态数据拷贝
    dataDest->bitsInputDI = dataSrc->bitsInputDI;
    dataDest->bitsStatusDI = dataSrc->bitsInputDI;
    dataDest->bitsInputDO = dataSrc->bitsInputDO;
    dataDest->bitsStatusDO = dataSrc->bitsInputDO;
}

/*
 * 功能：
 * 	  测量输入数据（输入值）映射-->原始数据对象
 * 参数：
 * 	  1.quint8 unit：单元号（0: 本机，1-6:扩展）
 *       2.quint8 module：模块号(本机：0-9, 扩展：0-5)
 *       3.quint16 status : 板卡状态
 *       4.SUB_BOARD_DATA_PROCESSED *pData： 数据指针
 * 返回值：
 * 	  无
 */
void DataProcess::dataInputRemap(quint8 unit, quint8 module, quint16 status, SUB_BOARD_DATA_PROCESSED *pData)
{
    void *ptrModbusReg;
    quint8 *ptrBitReg, *ptrBitStatusReg;
    quint8 chan0Num = STATUS_BOARD_CHAN0_NUM(status);
    quint8 chan1Num = STATUS_BOARD_CHAN1_NUM(status);

    switch (STATUS_BOARD_TYPE(status))
    {
    case STATUS_BOARD_TYPE_AI:
        chan0Num = chan0Num>AI_UNIT_CHAN_NUM_USE ? AI_UNIT_CHAN_NUM_USE : chan0Num;
        switch (unit)
        {
        case 0: //本机
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Data_Int32_Linear[module*AI_UNIT_CHAN_NUM_USE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16_Linear[module*AI_UNIT_CHAN_NUM_USE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 1:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit1_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit1_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 2:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit2_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit2_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 3:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit3_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit3_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 4:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit4_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit4_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 5:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit5_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit5_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        case 6:
            //采样输入数据
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit6_IO_Data_Int32[module*UNIT_CHAN_NUM_PRE*2];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataSample, sizeof(float)*chan0Num);
            //通道状态值
            ptrModbusReg = &g_originDataMap.inputReg_ExtUnit6_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
            ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);
            break;
        default:
            break;
        }
        break;
    case STATUS_BOARD_TYPE_DI:
        if (unit) return;   //扩展单元不支持DI/DO/DIO
        chan0Num = chan0Num>DIO_UNIT_CHAN_NUM_USE_MAX ? DIO_UNIT_CHAN_NUM_USE_MAX : chan0Num;

        ptrBitReg = &g_originDataMap.coil_MainUnit_IO_Data_Bit[module*UNIT_CHAN_NUM_PRE];
        ptrBitStatusReg = &g_originDataMap.coil_MainUnit_IO_Status_Bit[module*UNIT_CHAN_NUM_PRE];

        //DI通道状态值
        ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
        ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);

        for(int i=0; i<chan0Num; ++i){
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+i)<<1];
            if (pData->bitsInputDI & (0x01<<i)) {
                ptrBitReg[i] = ON;
                ptrBitStatusReg[i] = ON;
            } else {
                ptrBitReg[i] = OFF;
                ptrBitStatusReg[i] = OFF;
            }

            if (p_gDeviceCfg->mainUnitDI[module][i].rangeConfig.type == DI_Range_Type_DI){
                *(quint32*)ptrModbusReg = ptrBitReg[i];
            } else {
                *(quint32*)ptrModbusReg =  pData->dataDICount[i];  //DI 脉冲计数数据拷贝
            }

        }
        break;
    case STATUS_BOARD_TYPE_DO:
        if (unit) return;   //扩展单元不支持DI/DO/DIO
        chan0Num = chan0Num>DIO_UNIT_CHAN_NUM_USE_MAX ? DIO_UNIT_CHAN_NUM_USE_MAX : chan0Num;

        ptrBitReg = &g_originDataMap.relay_MainUnit_IO_Data_Bit[module*UNIT_CHAN_NUM_PRE];
        ptrBitStatusReg = &g_originDataMap.relay_MainUnit_IO_Status_Bit[module*UNIT_CHAN_NUM_PRE];
        for(int i=0; i<chan0Num; ++i){
            if (pData->bitsInputDO & (0x01<<i)) {
                ptrBitReg[i] = ON;
                ptrBitStatusReg[i] = ON;
            } else {
                ptrBitReg[i] = OFF;
                ptrBitStatusReg[i] = OFF;
            }
        }
        break;
    case STATUS_BOARD_TYPE_DIO:
        if (unit) return;   //扩展单元不支持DI/DO/DIO
        chan0Num = chan0Num>DIO_UNIT_CHAN_NUM_USE_MAX ? DIO_UNIT_CHAN_NUM_USE_MAX : chan0Num;
        chan1Num = chan1Num>DIO_UNIT_CHAN_NUM_USE_MAX ? DIO_UNIT_CHAN_NUM_USE_MAX : chan1Num;

        //DI
        ptrBitReg = &g_originDataMap.coil_MainUnit_IO_Data_Bit[module*UNIT_CHAN_NUM_PRE];
        ptrBitStatusReg = &g_originDataMap.coil_MainUnit_IO_Status_Bit[module*UNIT_CHAN_NUM_PRE];

        //DI通道状态值，DI无对应的线性状态区域
        ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE];
        ::memcpy((void*)ptrModbusReg, (void*)pData->dataStatus, sizeof(qint16)*chan0Num);

        for(int i=0; i<chan0Num; ++i){
            ptrModbusReg = &g_originDataMap.inputReg_MainUnit_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+i)<<1];
            if (pData->bitsInputDI & (0x01<<i)) {
                ptrBitReg[i] = ON;
                ptrBitStatusReg[i] = ON;
            } else {
                ptrBitReg[i] = OFF;
                ptrBitStatusReg[i] = OFF;
            }

            if (p_gDeviceCfg->mainUnitDI[module][i].rangeConfig.type == DI_Range_Type_DI){
                *(quint32*)ptrModbusReg = ptrBitReg[i];
            } else {
                *(quint32*)ptrModbusReg =  pData->dataDICount[i];  //DI 脉冲计数数据拷贝
            }
        }

        //DO
        ptrBitReg = &g_originDataMap.relay_MainUnit_IO_Data_Bit[module*UNIT_CHAN_NUM_PRE];
        ptrBitStatusReg = &g_originDataMap.relay_MainUnit_IO_Status_Bit[module*UNIT_CHAN_NUM_PRE];
        for(int i=0; i<chan1Num; ++i){
            if (pData->bitsInputDO & (0x01<<i)) {
                ptrBitReg[i] = ON;
                ptrBitStatusReg[i] = ON;
            } else {
                ptrBitReg[i] = OFF;
                ptrBitStatusReg[i] = OFF;
            }
        }
        break;
    case STATUS_BOARD_TYPE_EXT:
        break;
    default:
        break;
    }
}

/*
 * 功能：
 * 	  AI通道计算
 * 参数：
 * 	  1.quint8 unit： 单元号，0：本机，1-6：扩展单元
 *       2.quint8 module：模块号，本机（0-9）,扩展单元（0-5）
 *       3.quint8 channel： 通道号
 *       4.AI_CONFIG *pconfig：AI类型通道配置
 * 返回值：
 * 	  无
 */
void DataProcess::chanAICalculate(quint8 unit, quint8 module, quint8 channel, AI_CONFIG *pconfig)
{
    float inputData;                                     //通道测量输入数据（输入值）
    float tempData;                                     //临时数据,代表inputData经过查表、移动平均、冷端补偿后的值
    qreal tempDataCalc;                             //测量数据，代表tempData经过Delta/Linear/Sqrt以及偏移处理后的值
    float *pCalculateData;                          //通道测量值地址指针
    float *pCalculateDataLinear = NULL;  //通道测量值连续区域地址指针，只对本机AI有效
    qint16 *pChanStatus;                           //通道状态地址指针
    qint16 *pChanStatusLinear = NULL;   //本机AI通道连续区域通道状态地址指针，只对本机AI有效

    switch (unit) {
    case 0:
        inputData = *((float*)&g_originDataMap.inputReg_MainUnit_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_MainUnit_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pCalculateDataLinear = (float*)&g_originDataMap.inputReg_MainUnit_IO_Data_Float32_Linear[(module*AI_UNIT_CHAN_NUM_USE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        pChanStatusLinear = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16_Linear[module*AI_UNIT_CHAN_NUM_USE+channel];
        break;
    case 1:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit1_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit1_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit1_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    case 2:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit2_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit2_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit2_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    case 3:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit3_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit3_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit3_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    case 4:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit4_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit4_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit4_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    case 5:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit5_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit5_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit5_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    case 6:
        inputData = *((float*)&g_originDataMap.inputReg_ExtUnit6_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2]);
        pCalculateData =  (float*)&g_originDataMap.inputReg_ExtUnit6_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
        pChanStatus = &g_originDataMap.inputReg_ExtUnit6_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
        break;
    }

    //通道数据无效，直接返回
    if (IS_DATA_INVALID(*pChanStatus)) return;

    if(pconfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) { //通道未使用，设置状态并返回
        *pChanStatus = DATA_ERROR_OFF<<DATA_STATUS_ERROR_BITSOFF;
        if (pChanStatusLinear != NULL) *pChanStatusLinear = *pChanStatus;
        return;
    } else if (pconfig->rangeConfig.rangeType == AI_RANGE_Type_TC) { //热电耦，查表获取对应值
        if (DataQueryTC::instance()->getTempValTC(pconfig->rangeConfig.config.rangeTC, inputData, &tempData) == false){
            *pChanStatus = DATA_ERROR_AD_ERROR<<DATA_STATUS_ERROR_BITSOFF;
            return;
        }
    } else if (pconfig->rangeConfig.rangeType == AI_RANGE_Type_RTD) { //热电阻，查表获取对应值
        if (DataQueryRTD::instance()->getTempValRTD(pconfig->rangeConfig.config.rangeRTD, inputData, &tempData) == false){
            *pChanStatus = DATA_ERROR_AD_ERROR<<DATA_STATUS_ERROR_BITSOFF;
            return;
        }
    }  else {
        tempData = inputData;
    }

    //移动平均计算
    if (pconfig->rangeConfig.rangeMovingAvg.avgOnOff){
        quint8 count = pconfig->rangeConfig.rangeMovingAvg.avgCount;
        qreal ave=0;
        switch (unit) {
        case 0: //本机
            if (m_mainUnit_Moving[module][channel].count()<count) {
                m_mainUnit_Moving[module][channel].enqueue(tempData);
            } else {
                m_mainUnit_Moving[module][channel].dequeue();
                m_mainUnit_Moving[module][channel].enqueue(tempData);
            }
            for (int i=0; i<m_mainUnit_Moving[module][channel].count(); ++i){
                ave += m_mainUnit_Moving[module][channel].at(i);
            }
            tempData = ave/m_mainUnit_Moving[module][channel].count();
            break;
        default: //扩展单元
            if (m_extUnit_Moving[unit][module][channel].count()<count) {
                m_extUnit_Moving[unit][module][channel].enqueue(tempData);
            } else {
                m_extUnit_Moving[unit][module][channel].dequeue();
                m_extUnit_Moving[unit][module][channel].enqueue(tempData);
            }
            for (int i=0; i<m_extUnit_Moving[unit][module][channel].count(); ++i){
                ave += m_extUnit_Moving[unit][module][channel].at(i);
            }
            tempData = ave/m_extUnit_Moving[unit][module][channel].count();
            break;
        }
    }

    //冷端补偿处理
    if (pconfig->rangeConfig.rangeType == AI_RANGE_Type_TC \
        && pconfig->rangeConfig.rangeRJCCompensation.rjcCompMode == 1){
        tempData += pconfig->rangeConfig.rangeRJCCompensation.rjcTemp;
    }

    //通道计算
    qreal K,D;
    qreal a,b,A,B;  //a/b : 量程范围； A/B : 设定范围
    a = pconfig->rangeConfig.rangeMin;
    b = pconfig->rangeConfig.rangeMax;
    A = pconfig->rangeConfig.rangeScale.scaleMin/::pow10(pconfig->rangeConfig.rangeScale.scalePosition);
    B = pconfig->rangeConfig.rangeScale.scaleMax/::pow10(pconfig->rangeConfig.rangeScale.scalePosition);
    K = (B-A)/(b-a);
    D = (a*A - a*B)/(b-a);
    switch (pconfig->rangeConfig.rangeCalculateType) {
    case AI_Range_Calculate_Disabled:
        tempDataCalc = tempData;
        break;
    case AI_Range_Calculate_Delta:  //如果基准通道号比当前通道号大，则取该基准通道上次的测量值
        tempDataCalc = tempData - getChannelData(Channel_Type_AI<<CHANNEL_TYPE_BITOFF | unit<<CHANNEL_UNIN_BITOFF | \
                                                                                    module<<CHANNEL_MODULE_BITOFF | channel, pconfig->rangeConfig.rangeBasicChannel);
        break;
    case AI_Range_Calculate_Linear: //线性缩放运算
        tempDataCalc = K*tempData + D;
        break;
    case AI_Range_Calculate_Sqrt:   //平方根运算
        tempDataCalc = (B-A)*::sqrt((tempData-a)/(b-a)) + A;
        break;
    default:
        tempDataCalc = tempData;
        break;
    }

    //小信号切除
    if ((pconfig->rangeConfig.rangeType == AI_RANGE_Type_Vlot && pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Sqrt) || \
        (pconfig->rangeConfig.rangeType == AI_RANGE_Type_GS && \
        (pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Linear || pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Sqrt))) {
        if(pconfig->rangeConfig.rangeLowCut.lowCutOnOff) {
            qreal lowCutVal = K*((b-a)*pconfig->rangeConfig.rangeLowCut.lowCutPos) + D;
            if (tempData<=lowCutVal) {
                if (pconfig->rangeConfig.rangeLowCut.lowCutOut == 0) {  //%0输出
                    tempDataCalc = A;
                } else {    //线性输出
                    tempDataCalc = K*tempData + D;
                }
            }
        }
    }


    //偏移处理
    if (pconfig->rangeConfig.rangeType != AI_RANGE_Type_DI)
        tempDataCalc += pconfig->rangeConfig.rangeBias;

    //通道溢出判定
    if (p_gDeviceCfg->measureOverRange == Measure_OverRange_Free  \
        || pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Disabled){  //自由或运算关闭时，基于量程范围5%进行判定
        qreal rangeOver = (pconfig->rangeConfig.rangeMax - pconfig->rangeConfig.rangeMin) /20;
        if (tempDataCalc > (pconfig->rangeConfig.rangeMax + rangeOver)){    //正溢出
            *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
        } else if (tempDataCalc < (pconfig->rangeConfig.rangeMin - rangeOver)){ //负溢出
            *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        }
    } else {    //溢出，基于设定范围5%进行判定
        qreal rangeOver = (pconfig->rangeConfig.rangeScale.scaleMax - pconfig->rangeConfig.rangeScale.scaleMin) /20;
        if (tempDataCalc > (pconfig->rangeConfig.rangeScale.scaleMax + rangeOver)){    //正溢出
            *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
        } else if (tempDataCalc < (pconfig->rangeConfig.rangeScale.scaleMin - rangeOver)){ //负溢出
            *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        }
    }

    //通道断偶判定
    //....

    //通道报警: 变化率/延迟报警相关数据处理
    quint8 rateIncCount = p_gDeviceCfg->systemConfig.rateIncNum;
    quint8 rateDecCount = p_gDeviceCfg->systemConfig.rateDecNum;
    qreal compareData;
    QQueue<qreal> *pQueueInc, *pQueueDec;
    quint32 *pDelayUpper, *pDelayDowner;

    if (pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Delta)
        compareData = tempData;
    else
        compareData = tempDataCalc;

    if (unit==0){ //本机
        if (m_mainUnit_RateInc[module][channel].count()<(rateIncCount+1)){
            m_mainUnit_RateInc[module][channel].enqueue(compareData);
        } else {
            m_mainUnit_RateInc[module][channel].dequeue();
            m_mainUnit_RateInc[module][channel].enqueue(compareData);
        }

        if (m_mainUnit_RateDec[module][channel].count()<(rateDecCount+1)){
            m_mainUnit_RateDec[module][channel].enqueue(compareData);
        } else {
            m_mainUnit_RateDec[module][channel].dequeue();
            m_mainUnit_RateDec[module][channel].enqueue(compareData);
        }

        pQueueInc = &m_mainUnit_RateInc[module][channel];
        pQueueDec = &m_mainUnit_RateDec[module][channel];

        pDelayUpper = &m_mainUnit_DelayUpper[module][channel];
        pDelayDowner  = &m_mainUnit_DelayDowner[module][channel];
    } else { //扩展单元
        if (m_extUnit_RateInc[unit][module][channel].count()<(rateIncCount+1)){
            m_extUnit_RateInc[unit][module][channel].enqueue(compareData);
        } else {
            m_extUnit_RateInc[unit][module][channel].dequeue();
            m_extUnit_RateInc[unit][module][channel].enqueue(compareData);
        }

        if (m_extUnit_RateDec[unit][module][channel].count()<(rateDecCount+1)){
            m_extUnit_RateDec[unit][module][channel].enqueue(compareData);
        } else {
            m_extUnit_RateDec[unit][module][channel].dequeue();
            m_extUnit_RateDec[unit][module][channel].enqueue(compareData);
        }

        pQueueInc = &m_extUnit_RateInc[unit][module][channel];
        pQueueDec = &m_extUnit_RateDec[unit][module][channel];

        pDelayUpper = &m_extUnit_DelayUpper[unit][module][channel];
        pDelayDowner  = &m_extUnit_DelayDowner[unit][module][channel];
    }

    //通道报警: 状态判定
    quint32 curTimems, holdTimems;
    for (int i=0; i<4; ++i) {
        if (pconfig->alarmConfig.alarmOnOff[i]){
            switch(pconfig->alarmConfig.alarmType[i]){
            case Alarm_Type_H:       //上限报警
                if (compareData > pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_L:       //下限报警
                if (compareData < pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_R:       //变化率上升限报警
                if (pQueueInc->count() == (rateIncCount+1)){
                    if ((pQueueInc->at(rateIncCount) - pQueueInc->at(0)) > pconfig->alarmConfig.alarmValue[i])
                        *pChanStatus |= 1<<i;
                }
                break;
            case Alarm_Type_r:        //变化率下降限报警
                if (pQueueDec->count() == (rateDecCount+1)){
                    if ((pQueueInc->at(0) - pQueueInc->at(rateIncCount)) > pconfig->alarmConfig.alarmValue[i])
                        *pChanStatus |= 1<<i;
                }
                break;
            case Alarm_Type_T:       //延迟上限---上限持续时间报警
                if (compareData > pconfig->alarmConfig.alarmValue[i]){
                    (*pDelayUpper)++;
                    curTimems = (*pDelayUpper) * p_gDeviceCfg->measureInterval_ms;
                    holdTimems = ((pconfig->alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((pconfig->alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (pconfig->alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayUpper = 0;
                }
                break;
            case Alarm_Type_t:       //延迟下限---下限持续时间报警
                if (compareData < pconfig->alarmConfig.alarmValue[i]){
                    (*pDelayDowner)++;
                    curTimems = (*pDelayDowner) * p_gDeviceCfg->measureInterval_ms;
                    holdTimems = ((pconfig->alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((pconfig->alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (pconfig->alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayDowner = 0;
                }
                break;
            case Alarm_Type_h:      //Delta计算适用，差值上限报警
                if(pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Delta && \
                   compareData > pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_l:       //Delta计算适用，差值下限报警
                if(pconfig->rangeConfig.rangeCalculateType == AI_Range_Calculate_Delta && \
                   compareData < pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            default:
                break;
            }
        }
    }


    *pCalculateData = tempDataCalc;
    if(pCalculateDataLinear != NULL) *pCalculateDataLinear = tempDataCalc;
    if(pChanStatusLinear !=NULL) *pChanStatusLinear = *pChanStatus;
}

/*
 * 功能：
 * 	  DI通道计算
 * 参数：
 *       1.quint8 module：模块号，本机（0-9）
 *       2.quint8 channel： 通道号
 *       3.DI_CONFIG *pconfig：DI类型通道配置
 * 返回值：
 * 	  无
 */
void DataProcess::chanDICalculate(quint8 module, quint8 channel, DI_CONFIG *pconfig)
{
    float *pCalculateData;                          //通道测量值地址指针
    qint16 *pChanStatus;                           //通道状态地址指针
    qint32 dataDI;                                       //通道输入值

    pChanStatus = &g_originDataMap.inputReg_MainUnit_IO_Status_Int16[module*UNIT_CHAN_NUM_PRE+channel];
    pCalculateData =  (float*)&g_originDataMap.inputReg_MainUnit_IO_Data_Float32[(module*UNIT_CHAN_NUM_PRE+channel)*2];
    dataDI = *(qint32 *)&g_originDataMap.inputReg_MainUnit_IO_Data_Int32[(module*UNIT_CHAN_NUM_PRE+channel)*2];

    //通道数据无效，直接返回
    if (IS_DATA_INVALID(*pChanStatus)) return;

    switch (pconfig->rangeConfig.type){
    case DI_Range_Type_Disabled://通道未使用，设置状态并返回
        *pChanStatus = DATA_ERROR_OFF<<DATA_STATUS_ERROR_BITSOFF;
        return;
    case DI_Range_Type_DI: //DI类型，进行Delta或Linear运算
        if (pconfig->rangeConfig.calculateType == DI_Range_Calculate_Delta){
            //通道计算
            *pCalculateData = dataDI - getChannelData(Channel_Type_DI<<CHANNEL_TYPE_BITOFF | module<<CHANNEL_MODULE_BITOFF | channel, \
                                                                                        pconfig->rangeConfig.basicChannel);
            //溢出判定
            if((qint32)*pCalculateData>=1)
                *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
            else if((qint32)*pCalculateData<=-1)
                *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        } else if (pconfig->rangeConfig.calculateType == DI_Range_Calculate_Linear) {
            //通道计算
            if (dataDI == 0) {
                *pCalculateData = pconfig->rangeConfig.scale.scaleMin/::pow10(pconfig->rangeConfig.scale.scalePosition);
            } else {
                *pCalculateData = pconfig->rangeConfig.scale.scaleMax/::pow10(pconfig->rangeConfig.scale.scalePosition);
            }
            //溢出判定
            if (dataDI>=1)
                *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
            else if (dataDI<=0)
                *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        } else {
            *pCalculateData = dataDI;
            //溢出判定
            if (dataDI>=1)
                *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
            else if (dataDI<=0)
                *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        }
        break;
    case DI_Range_Type_Pluse://脉冲类型，无运算功能
        *pCalculateData = dataDI;

        //溢出判定 0~999999
        if (dataDI>=999999)
            *pChanStatus = DATA_ERROR_OVER_POSITIVE<<DATA_STATUS_ERROR_BITSOFF;
        else if (dataDI<=0)
            *pChanStatus = DATA_ERROR_OVER_NEGATIVE<<DATA_STATUS_ERROR_BITSOFF;
        break;
    }

    //通道报警: 变化率/延迟报警相关数据处理
    quint8 rateIncCount = p_gDeviceCfg->systemConfig.rateIncNum;
    quint8 rateDecCount = p_gDeviceCfg->systemConfig.rateDecNum;
    qreal compareData;
    QQueue<qreal> *pQueueInc, *pQueueDec;
    quint32 *pDelayUpper, *pDelayDowner;

    compareData = dataDI;

    if (m_mainUnit_RateInc[module][channel].count()<(rateIncCount+1)){
        m_mainUnit_RateInc[module][channel].enqueue(compareData);
    } else {
        m_mainUnit_RateInc[module][channel].dequeue();
        m_mainUnit_RateInc[module][channel].enqueue(compareData);
    }

    if (m_mainUnit_RateDec[module][channel].count()<(rateDecCount+1)){
        m_mainUnit_RateDec[module][channel].enqueue(compareData);
    } else {
        m_mainUnit_RateDec[module][channel].dequeue();
        m_mainUnit_RateDec[module][channel].enqueue(compareData);
    }

    pQueueInc = &m_mainUnit_RateInc[module][channel];
    pQueueDec = &m_mainUnit_RateDec[module][channel];

    pDelayUpper = &m_mainUnit_DelayUpper[module][channel];
    pDelayDowner  = &m_mainUnit_DelayDowner[module][channel];

    //通道报警: 状态判定
    quint32 curTimems, holdTimems;
    for (int i=0; i<4; ++i) {
        if (pconfig->alarmConfig.alarmOnOff[i]){
            switch(pconfig->alarmConfig.alarmType[i]){
            case Alarm_Type_H:       //上限报警
                if (dataDI >= pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_L:       //下限报警
                if (compareData <= pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_R:       //变化率上升限报警
                if (pQueueInc->count() == (rateIncCount+1)){
                    if ((pQueueInc->at(rateIncCount) - pQueueInc->at(0)) >= pconfig->alarmConfig.alarmValue[i])
                        *pChanStatus |= 1<<i;
                }
                break;
            case Alarm_Type_r:        //变化率下降限报警
                if (pQueueDec->count() == (rateDecCount+1)){
                    if ((pQueueInc->at(0) - pQueueInc->at(rateIncCount)) >= pconfig->alarmConfig.alarmValue[i])
                        *pChanStatus |= 1<<i;
                }
                break;
            case Alarm_Type_T:       //延迟上限---上限持续时间报警
                if (compareData > pconfig->alarmConfig.alarmValue[i]){
                    (*pDelayUpper)++;
                    curTimems = (*pDelayUpper) * p_gDeviceCfg->measureInterval_ms;
                    holdTimems = ((pconfig->alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((pconfig->alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (pconfig->alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayUpper = 0;
                }
                break;
            case Alarm_Type_t:       //延迟下限---下限持续时间报警
                if (compareData < pconfig->alarmConfig.alarmValue[i]){
                    (*pDelayDowner)++;
                    curTimems = (*pDelayDowner) * p_gDeviceCfg->measureInterval_ms;
                    holdTimems = ((pconfig->alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((pconfig->alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (pconfig->alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayDowner = 0;
                }
                break;
            case Alarm_Type_h:      //Delta计算适用，差值上限报警
                if(pconfig->rangeConfig.calculateType == DI_Range_Calculate_Delta && \
                   compareData >= pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_l:       //Delta计算适用，差值下限报警
                if(pconfig->rangeConfig.calculateType == DI_Range_Calculate_Delta && \
                   compareData <= pconfig->alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            default:
                break;
            }
        }
    }
}

/************************运算通道计算工作对象*********************************/
/*
 * 功能：
 * 	  槽函数，运行于数据处理线程，根据系统当前状态，获取各运算通道数据
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MathProcess::slotMathProcess()
{
    char * pDataTable, *pDataTableTemp;
    qreal chanData;
    MathExpAnalysis *pMathExpAnalysis;
    quint32 selfNum, basicNum, mathIndex;

    //拷贝原始数据对象中各基础通道数据->m_modbusRegMapTemp
    ::memcpy(&m_modbusRegMapTemp, &g_originDataMap, sizeof(MODBUS_REGISTER_MAP));

    if (_mathStatus) {
        //各运算通道相关TLOG计算
        for (int i=0; i<MathExpAnalysis::m_mathExplist.count(); ++i){
            pMathExpAnalysis = MathExpAnalysis::m_mathExplist.at(i);
            if (pMathExpAnalysis->m_tlog_type) {
                selfNum = (Channel_Type_Math<<CHANNEL_TYPE_BITOFF) | pMathExpAnalysis->m_index;
                basicNum = pMathExpAnalysis->m_tlog_channel;
                chanData = getChannelData(selfNum, basicNum);

                pMathExpAnalysis->m_tlog_count++;
                pMathExpAnalysis->m_tlog_sum += chanData;
                pMathExpAnalysis->m_tlog_max = pMathExpAnalysis->m_tlog_max > chanData ? pMathExpAnalysis->m_tlog_max : chanData;
                pMathExpAnalysis->m_tlog_min = pMathExpAnalysis->m_tlog_min < chanData ? pMathExpAnalysis->m_tlog_min : chanData;
                pMathExpAnalysis->m_tlog_ave = pMathExpAnalysis->m_tlog_sum/pMathExpAnalysis->m_tlog_count;
                pMathExpAnalysis->m_tlog_p2p = pMathExpAnalysis->m_tlog_max - pMathExpAnalysis->m_tlog_min;
            }
        }

        //计算运算通道数据-->m_modbusRegMapTemp
        for (int i=0; i<MathExpAnalysis::m_mathExplist.count(); ++i) {
            pMathExpAnalysis = MathExpAnalysis::m_mathExplist.at(i);
            mathIndex = pMathExpAnalysis->m_index;
            chanMathCalculate(mathIndex, pMathExpAnalysis);
        }
    }

    //共享内存Modbus寄存器表更新
    if(g_sharedDataTable.isAttached()) {
        g_sharedDataTable.lock();
        pDataTable = static_cast<char*>(g_sharedDataTable.data());
        pDataTableTemp = (char *)(&m_modbusRegMapTemp);
        ::memcpy(pDataTable, pDataTableTemp, sizeof(MODBUS_REGISTER_MAP));
        g_sharedDataTable.unlock();
    }

    //运算通道运算结束信号
    emit   sigResultReady();
}

/*
 * 功能：
 * 	  槽函数，运算通道配置变更处理
 * 参数：
 * 	  1.quint32 index:运算通道索引
 * 返回值：
 * 	  无
 */
void MathProcess::slotChannelConfigChangedMath(quint32 index)
{
    if (index<MATH_CHANNEL_NUM_MAX) {
        m_sample_moving[index].clear();
        m_math_DelayUpper[index] = 0;
        m_math_DelayDowner[index] = 0;
        m_sampleCount[index] = 0;
    }
}

/*
 * 功能：
 * 	  MATH通道计算
 * 参数：
 *       1.quint32 index ：MATH通道索引号
 *       2.MathExpAnalysis *pMathExp : MATH通道运算表达式指针
 * 返回值：
 * 	  无
 */
void MathProcess::chanMathCalculate(quint32 index, MathExpAnalysis *pMathExp)
{
    quint32 measureInterval_ms;
    qreal mathData;

    //根据MATH通道配置计算TLOG最终值m_tlog_value
    measureInterval_ms = p_gDeviceCfg->measureInterval_ms;
    switch (pMathExp->m_tlog_type) {
    case Tlog_type_sum:
        if (p_gDeviceCfg->chanMath[index].expressConfig.expTlogSumScale) {
            pMathExp->m_tlog_value = pMathExp->m_tlog_sum * \
                                                          (measureInterval_ms/p_gDeviceCfg->chanMath[index].expressConfig.expTlogSumScale);
        }
        pMathExp->m_tlog_value = pMathExp->m_tlog_sum;
        break;
    case Tlog_type_max:
        pMathExp->m_tlog_value = pMathExp->m_tlog_max;
        break;
    case Tlog_type_min:
        pMathExp->m_tlog_value = pMathExp->m_tlog_min;
        break;
    case Tlog_type_ave:
        pMathExp->m_tlog_value = pMathExp->m_tlog_ave;
        break;
    case Tlog_type_p2p:
        pMathExp->m_tlog_value = pMathExp->m_tlog_p2p;
        break;
    default:
        pMathExp->m_tlog_value = 0;
        break;
    }

    mathData = pMathExp->getMathExpValue();

    //长时间移动平均计算
    if (p_gDeviceCfg->chanMath[index].expressConfig.expRollingAvgSwtich) {
        qreal movingAve = 0;
        quint32 count = p_gDeviceCfg->chanMath[index].expressConfig.expRollingAvgNumber;    //采样个数
        quint32 interval_ms =p_gDeviceCfg->chanMath[index].expressConfig.expRollingAvgInterval *1000;
        interval_ms = interval_ms < measureInterval_ms ? measureInterval_ms : interval_ms;
        quint32 sampleInterval = interval_ms/measureInterval_ms;        //采样间隔---隔多少个测量周期采样
        if (interval_ms%measureInterval_ms) {
            sampleInterval += 1;
            interval_ms = sampleInterval * measureInterval_ms;
        }

        if (++m_sampleCount[index] == sampleInterval){  //采样间隔满足，则添加采样值
            m_sampleCount[index] = 0;
            if (m_sample_moving[index].count()<(int)count) {
                m_sample_moving[index].enqueue(mathData);
            } else {
                m_sample_moving[index].dequeue();
                m_sample_moving[index].enqueue(mathData);
            }
        }


        for (int i=0; i<m_sample_moving[index].count(); ++i) {
            movingAve += m_sample_moving[index].at(i);
        }
        mathData = movingAve/m_sample_moving[index].count();
    }

    //Math通道赋值
    m_modbusRegMapTemp.inputReg_MainUnit_Math_Data_Float32[index<<1] = mathData;

    //通道状态判定
    //Math通道无实际量程上、下限，配置中的上下限仅用于显示，故状态判定略
    qint16 *pChanStatus;                           //通道状态地址指针
    pChanStatus = &m_modbusRegMapTemp.inputReg_MainUnit_Math_Status_Int16[index];
    *pChanStatus = 0;

    //通道报警判定
    quint32 curTimems, holdTimems;
    quint32 *pDelayUpper, *pDelayDowner;
    pDelayUpper = &m_math_DelayUpper[index];
    pDelayDowner = &m_math_DelayDowner[index];
    for (int i=0; i<4; ++i) {
        if (p_gDeviceCfg->chanMath[index].alarmConfig.alarmOnOff[i]) {
            switch (p_gDeviceCfg->chanMath[index].alarmConfig.alarmType[i]) {
            case Alarm_Type_H:
                if (mathData > p_gDeviceCfg->chanMath[index].alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_L:
                if (mathData < p_gDeviceCfg->chanMath[index].alarmConfig.alarmValue[i])
                    *pChanStatus |= 1<<i;
                break;
            case Alarm_Type_T:
                if (mathData > p_gDeviceCfg->chanMath[index].alarmConfig.alarmValue[i]) {
                    (*pDelayUpper)++;
                    curTimems = (*pDelayUpper) * measureInterval_ms;
                    holdTimems = ((p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayUpper = 0;
                }
                break;
            case Alarm_Type_t:
                if (mathData < p_gDeviceCfg->chanMath[index].alarmConfig.alarmValue[i]) {
                    (*pDelayDowner)++;
                    curTimems = (*pDelayUpper) * measureInterval_ms;
                    holdTimems = ((p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i]>>16) & 0xFF) * 3600000;
                    holdTimems += ((p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i]>>8) & 0xFF) * 60000;
                    holdTimems += (p_gDeviceCfg->chanMath[index].alarmConfig.alarmDelay[i] & 0xFF) * 1000;
                    if (curTimems > holdTimems)
                        *pChanStatus |= 1<<i;
                } else {
                    *pDelayDowner = 0;
                }
                break;
            default:
                break;
            }
        }
    }

}

