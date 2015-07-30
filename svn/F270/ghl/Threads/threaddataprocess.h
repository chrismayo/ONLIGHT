/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDataProcess.h
 * 概   要：数据处理线程，基于Modbus协议，对板内RS485总线上的子板卡进行数据的
 * 查询，并根据通道配置做简单的运算，最后将数据各通道数据映射到原始数据对象中。
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-6-15
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/

#ifndef THREADDATAPROCESS_H
#define THREADDATAPROCESS_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QTimer>
#include "./GlobalData/cfgGlobalDef.h"
#include "../GlobalData/dataGlobalDef_ModbusReg.h"

#include "../Common/dataqueryrtd.h"
#include "../Common/dataquerytc.h"
#include "../Common/mathexpanalysis.h"

#include "../GlobalData/cfgchannel.h"

#include <modbus/modbus.h>

#define EXT_VALID 0xAA

/*
 * 子板卡状态及配置寄存器结构体
 */
typedef struct SUB_BOARD_STATUS_STRUCT{
    quint16  status;           //板卡状态寄存器
    union{
        quint16 dataModbus[(EXT_UNIT_MODULE_NUM*EXT_UNIT_NUM)>>1];//Modbus寄存器表
        quint8  dataExtStatus[EXT_UNIT_MODULE_NUM][EXT_UNIT_NUM];    //6*6个扩展板卡状态，EXT_VALID-有效，其它-无效
    }config;

}SUB_BOARD_STATUS;

/*
 *板卡数据寄存器表结构体
 */
typedef struct SUB_BOARD_DATA_STRUCT{
    union{
        quint16  dataModbus[UNIT_CHAN_NUM_USE_MAX<<1];                         //Modbus寄存器表
        float       dataSample[UNIT_CHAN_NUM_USE_MAX];                                 //AI类型板卡采样数据, 对应的float32
        quint32  dataDICount[UNIT_CHAN_NUM_USE_MAX];                               //DI脉冲类型脉冲计数, 对应的uint32
    };
    quint16 bitsInputDI;           //DI输入值
    quint16 bitsInputDO;         //DO输入值
}SUB_BOARD_DATA;

typedef struct SUB_BOARD_DATA_PROCESSED_STRUCT{
    qint16 dataStatus[UNIT_CHAN_NUM_USE_MAX];        //通道状态
    float  dataSample[UNIT_CHAN_NUM_USE_MAX];        //AI类型板卡采样数据输入
    quint32 dataDICount[UNIT_CHAN_NUM_USE_MAX];  //DI脉冲类型脉冲计数
    float   dataCalcu[UNIT_CHAN_NUM_USE_MAX];          //采样数据计算结果

    quint16 bitsInputDI;           //DI输入值
    quint16 bitsStatusDI;          //DI状态值
    quint16 bitsInputDO;         //DO输入值
    quint16 bitsStatusDO;        //DO状态值
}SUB_BOARD_DATA_PROCESSED;

/*子板卡数据处理线程对象*/
class ThreadDataProcess : public QObject
{
    Q_OBJECT
public:
    static ThreadDataProcess *instance();
    void setMathStatus(Math_Status_Type status);        //运算状态设定
    void changeMeasurePeriod();                                    //测量周期变更

signals:
    void sigChannelConfigChangedAI(quint8 unit, quint8 module, quint8 channel);
    void sigChannelConfigChangedMath(quint32 index);
    void sigDataProcessFinished();                          //子板数据获取完成信号
    void sigMathProcessFinished();                         //运算通道运算完成信号

public slots:

private:
    explicit ThreadDataProcess(QObject *parent = 0);

private:
    QThread m_dataProcessThread;
    QTimer m_dataQueryTimer;
};

/*子板卡数据处理工作对象*/
class DataProcess : public QObject
{
    Q_OBJECT

public slots:
    int slotDataQuery();
    int slotStatusQuery();
    void slotChannelConfigChangedAI(quint8 unit, quint8 module, quint8 channel);

signals:
    void sigResultReady();

private:
    void dataInputProcess(SUB_BOARD_DATA *dataSrc, SUB_BOARD_DATA_PROCESSED *dataDest);
    void dataInputRemap(quint8 unit, quint8 module, quint16 status, SUB_BOARD_DATA_PROCESSED *pData);

    void chanAICalculate(quint8 unit, quint8 module, quint8 channel, AI_CONFIG *pconfig);
    void chanDICalculate(quint8 module, quint8 channel, DI_CONFIG *pconfig);

    //本机AI类型通道移动平均采样值FIFO，输入值是经过基本查表处理后的数据
    QQueue<qreal>    m_mainUnit_Moving[MAIN_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    //扩展单元AI类型通道移动平均采样值FIFO，输入值是经过基本查表处理后的数据
    QQueue<qreal>    m_extUnit_Moving[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];

    //本机AI类型通道报警变化率采样值FIFO
    QQueue<qreal>    m_mainUnit_RateInc[MAIN_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    QQueue<qreal>    m_mainUnit_RateDec[MAIN_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    //扩展单元AI类型通道报警变化率采样值FIFO
    QQueue<qreal>    m_extUnit_RateInc[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    QQueue<qreal>    m_extUnit_RateDec[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];

    //本机AI类型通道报警延迟上、下限周期计数
    quint32 m_mainUnit_DelayUpper[MAIN_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    quint32 m_mainUnit_DelayDowner[MAIN_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    //扩展单元AI类型通道报警延迟上、下限周期计数
    quint32  m_extUnit_DelayUpper[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
    quint32  m_extUnit_DelayDowner[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][AI_UNIT_CHAN_NUM_USE];
};

/*运算通道计算工作对象*/
class MathProcess : public QObject
{
    Q_OBJECT

public slots:
    void slotMathProcess();
    void slotChannelConfigChangedMath(quint32 index);

signals:
    void sigResultReady();

private:
    void chanMathCalculate(quint32 index, MathExpAnalysis *pMathExp);


private:
    MODBUS_REGISTER_MAP m_modbusRegMapTemp;

    //各运算通道采样间隔计数
    quint32 m_sampleCount[MATH_CHANNEL_NUM_MAX];
    //各运算通道移动平均采样值FIFO
    QQueue<qreal>    m_sample_moving[MATH_CHANNEL_NUM_MAX];

    //各运算通道报警延迟上、下限周期计数
    quint32 m_math_DelayUpper[MATH_CHANNEL_NUM_MAX];
    quint32 m_math_DelayDowner[MATH_CHANNEL_NUM_MAX];
};

#endif // THREADDATAPROCESS_H
