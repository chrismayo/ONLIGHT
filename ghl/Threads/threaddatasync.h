/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDataSync.h
 * 概   要：数据同步线程。
 *                前置任务：数据处理线程 | 数据通信线程
 *                内容：1.基于前置任务，根据系统配置生成有效的显示数据和事件数据
 *                            2.添加有效的显示数据和事件数据至各自的缓冲区，并更新相应的数据库
 *                            3.根据配置决定是否刷新到数据库
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
#ifndef THREADDATASYNC_H
#define THREADDATASYNC_H

#include <QObject>
#include <QThread>
#include <QMap>

#include "./GlobalData/cfgGlobalDef.h"
#include "../GlobalData/dataGlobalDef_ModbusReg.h"

#define EVNET_INTERVAL_NUM  17          //事件记录周期个数

class ThreadDataSync : public QObject
{
    Q_OBJECT
public:
    static ThreadDataSync *instance();

signals:
    void sigSyncData();

signals:
    void sigDataUpdated();  //共享内存--Modbus寄存器分配表数据更新信号

public slots:
    void slotHandleResults();

    void slotManualSample();    //手动采样事件处理
    void slotPeriodChanged();   //测量周期、趋势周期、事件记录周期改变处理
    void slotRecordStop();  //记录停止处理函数，在停止记录时触发该函数

private:
    explicit ThreadDataSync(QObject *parent = 0);
    void mapInit();
private:
    QThread m_dataSyncThread;
    QMap<quint32, quint32> m_event2display;   //"ms" -> "s"
};

/*数据同步工作对象*/
class SyncProcess : public QObject
{
    Q_OBJECT

public slots:
    void slotSyncProcess();

signals:
    void sigResultReady();          //数据同步完成信号
    void sigDispDataReady();     //有效显示数据信号
    void sigEventDataReady();   //有效事件数据信号
    void sigManualDataReady();//有效手动采样数据信号

private:
    void dataBufferProcess(bool first); //显示、事件数据处理
    void dataSampleProcess();  //采样数据处理
};

#endif // THREADDATASYNC_H
