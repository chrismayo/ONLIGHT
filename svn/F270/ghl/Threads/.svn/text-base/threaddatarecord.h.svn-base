/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDatRecord.h
 * 概   要：数据记录线程。
 *                1.根据系统配置以及传入的参数将数据保存到数据库
 *                2.如果配置了同步到外部存储功能，则将数据以文件的方式保存到外部存储器
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 开始日期：2015-7-13
 * 完成日期：
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#ifndef THREADDATARECORD_H
#define THREADDATARECORD_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QTimer>
#include <QtSql/QSqlDatabase>

#include "./GlobalData/cfgGlobalDef.h"
#include "../GlobalData/dataGlobalDef_ModbusReg.h"

#include "../GlobalData/sqlBlock_fileFormat.h"
#include "../GlobalData/sqlBlock_fileInfo.h"
#include "../GlobalData/sqlBlock_sysConfig.h"
#include "../GlobalData/sqlBlock_GroupInfo.h"
#include "../GlobalData/sqlBlock_RecordChanInfo.h"
#include "../GlobalData/sqlBlock_batchInfo.h"
#include "../GlobalData/sqlBlock_reportInfo.h"
#include "../GlobalData/sqlTable_Alarm.h"
#include "../GlobalData/sqlTable_Message.h"

/* 数据记录处理线程*/
class ThreadDataRecord : public QThread
{
    Q_OBJECT
public:
    static ThreadDataRecord *instance();
    void newDispData(DISPLAY_DATA_RECORD *dispData);
    void newEventData(EVENT_DATA_RECORD *eventData);
    void newManualData(EVENT_DATA_RECORD *manualData);
    void newReportData(REPORT_DATA_RECORD *reportData);
    void newAlarmData(ALARM_DATA *alarmData);
    void newMessageData(MSG_DATA *msgData);

private:
    explicit ThreadDataRecord(QObject *parent = 0);
    bool createConnection();
    void init();

    //显示数据处理相关函数
    void dispDataRecord(DISPLAY_DATA_RECORD *dispData);
    QString getDispSubTableName(QString mainTable);
    bool createDispDataMainTable();
    QString createDispDataSubTable(quint64 ID);
    bool addNewRecordDispMain(quint64 ID);
    bool updateRecordDispMain(quint64 dataCount, quint64 ID);
    bool endRecordDispMain(SQL_Record_Status status, quint64 ID);
    bool addDispDataSub(QString dispTableName, DISPLAY_DATA_RECORD *dispData);
    void getDispBlobData(DISPLAY_DATA_RECORD *dispData, DISPLAY_DATA *pData);

    //事件数据处理相关函数
    void eventDataRecord(EVENT_DATA_RECORD *eventData);
    QString getEventSubTableName(QString mainTable);
    bool createEventDataMainTable();
    QString createEventDataSubTable(quint64 ID);
    bool addNewRecordEventMain(quint64 ID);
    bool updateRecordEventMain(quint64 dataCount, quint64 ID);
    bool endRecordEventMain(SQL_Record_Status status, quint64 ID);
    bool addEventDataSub(QString eventTableName, EVENT_DATA_RECORD *eventData);
    void getEventBlobData(EVENT_DATA_RECORD *eventData, qreal *pData);

    //手动采样数据处理相关函数
    void manualDataRecord(EVENT_DATA_RECORD *manualData);
    QString getManualSubTableName(QString mainTable);
    bool createManualDataMainTable();
    QString createManualDataSubTable(quint64 ID);
    bool addNewRecordManualMain(quint64 ID);
    bool updateRecordManualMain(quint64 dataCount, quint64 ID);
//    bool endRecordManualMain(SQL_Record_Status status, quint64 ID);
    bool addManualDataSub(QString manualTableName, EVENT_DATA_RECORD *manualData);
    void getManualBlobData(EVENT_DATA_RECORD *manualData, qreal *pData);

    //报表数据处理相关函数
    void reportDataRecord(REPORT_DATA_RECORD *reportData);
    QString getReportSubTableName(QString mainTable);
    bool createReportDataMainTable();
    QString createReportDataSubTable(quint64 ID);
    bool addNewRecordReportMain(quint64 ID);
    bool addReportDataSub(QString reportTableName, REPORT_DATA_RECORD *reportData);
    void getReportBlobData(REPORT_DATA_RECORD *reportData, qreal *pData);

    //报警数据处理相关函数
    void alarmDataRecord(ALARM_DATA * alarmData);
    bool createAlarmDataMainTable();
    bool addAlarmData(ALARM_DATA * alarmData);

    //消息数据处理相关函数
    void msgDataRecord(MSG_DATA *msgData);
    bool createMsgDataMainTable();
    bool addMsgData(MSG_DATA *msgData);

    //数据表通用操作函数
    bool isTableExist(QString tableName);
    bool getTabelRecordNum(QString tableName, quint64 *pCount);
    bool getTableMaxID(QString tableName, quint64 *pID);
    bool getTableMinID(QString tableName, quint64 *pID);
    bool deleteTableRecord(QString tableName, quint64 ID);
    bool dropTable(QString tableName);

public slots:

signals:

protected:
    void run();

private:
    QQueue<void *>   m_dispDataList;        //待处理的显示数据指针FIFO
    quint64  m_dispDataCount;                    //显示数据存储计数，单位：定时器间隔
    quint64  m_dispDataLengthCount;        //显示数据存储长度周期数，单位：定时器间隔
    QMutex  m_dispLock;

    QQueue<void *>   m_eventDataList;       //待处理的事件数据指针FIFO
    quint64  m_eventDataCount;                    //事件数据存储计数，单位：定时器间隔
    quint64  m_eventDataLengthCount;        //事件数据存储长度周期数，单位：定时器间隔
    QMutex  m_eventLock;

    QQueue<void *>   m_manualDataList;    //待处理的手动采样数据指针FIFO
    QMutex  m_manualLock;

    QQueue<void *>   m_reportDataList;      //待处理的报表数据指针FIFO
    QMutex  m_reportLock;

    QQueue<void *>   m_AlarmDataList;       //待处理的报警数据指针FIFO
    QMutex  m_alarmLock;

    QQueue<void *>   m_messageDataList; //待处理的消息数据指针FIFO
    QMutex  m_messageLock;

    QSqlDatabase* p_db;
    quint64 m_timeTag;                                  //时间变更ID
    bool    m_startDispFlag;                            //记录开始标记
    bool    m_startEventFlag;                            //记录开始标记
    quint64    m_startDispRecordID;             //显示数据表开始记录ID号
    quint64    m_startEventRecordID;           //事件数据表开始记录ID号

    //数据库表记录字段相关数据结构体
    SQL_FILE_FORMAT m_fileFormat;           //共用
    SQL_FILE_INFO       m_fileInfo;                //共用
    SQL_BATCH_INFO   m_batchInfo;           //共用
    SQL_GROUP_INFO  m_groupInfo;          //共用
    GROUP_INFO          *p_groupInfo;         //共用
    SQL_SYS_CONFIG   m_sysConfig;           //共用
    SQL_REPORT_INFO m_reportInfo;          //报表数据表用

    SQL_RECORD_CHAN_INFO    m_channelInfoDisp;  //显示数据记录通道结构体
    CHAN_INFO   *p_channelDisp;             //显示数据记录通道指针
    SQL_RECORD_CHAN_INFO    m_channelInfoEvent;  //事件数据记录通道结构体
    CHAN_INFO   *p_channelEvent;             //事件数据记录通道指针
    SQL_RECORD_CHAN_INFO    m_channelInfoManual;  //手动采样数据记录通道结构体
    CHAN_INFO   *p_channelManual;             //手动采样数据记录通道指针

    QString m_fileName_disp;        //显示记录数据文件名称
    QString m_fileName_event;      //事件记录数据文件名称

    friend class ThreadDataSync;
};

#endif // THREADDATARECORD_H
