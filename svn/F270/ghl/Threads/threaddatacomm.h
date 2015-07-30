/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDataComm.h
 * 概   要：数据通信线程，即运行在网络及串口上的Modbus客户端程序，按用户设定的
 * 命令执行各个Modbus命令，从目标从机（服务器）上获取数据，并映射到原始数据对
 * 象中。
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
#ifndef THREADDATACOMM_H
#define THREADDATACOMM_H

#include <QObject>
#include <QThread>

#include "./GlobalData/cfgGlobalDef.h"
#include "../GlobalData/dataGlobalDef_ModbusReg.h"

class ThreadDataComm : public QObject
{
    Q_OBJECT
public:
    static ThreadDataComm *instance();

signals:

public slots:

private:
    explicit ThreadDataComm(QObject *parent = 0);

private:
    QThread m_dataCommThread;

};

#endif // THREADDATACOMM_H
