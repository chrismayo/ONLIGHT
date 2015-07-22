/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：ThreadDatRecord.cpp
 * 概   要：数据记录线程。
 *               根据系统配置以及传入的参数将数据保存到数据库
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-7-13
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "threaddatarecord.h"
#include "../GlobalData/cfgchannel.h"
#include <QDebug>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

extern DEVICE_CONFIG                   *p_gDeviceCfg;        //全局变量指针，指向LPSRAM中的设备配置结构

#define DISP_MAIN_TABLE      "table_Main_Disp"     //显示数据主表
#define EVENT_MAIN_TABLE    "table_Main_Event"  //事件数据主表
#define MANUAL_MAIN_TABLE "table_Main_Manual"   //手动采样数据主表
#define REPORT_MAIN_TABLE   "table_Main_Report" //报表数据主表
#define ALARM_MAIN_TABLE    "table_Main_Alarm"  //报警数据主表
#define MESSAGE_MAIN_TABLE  "table_Main_Message"    //消息数据主表
#define TIME_CHANGE_TABLE   "table_Change_Time" //时间变更表

#define MANUAL_SUB_RECORD_MAX   500              //手动采样数据子表最大记录数
#define MANUAL_MAIN_RECORD_MAX  400            //手动采样数据主表最大记录数

ThreadDataRecord::ThreadDataRecord(QObject *parent) :
    QThread(parent)
{
    init();

    if (createConnection())
        qDebug()<<"sql database open";
    else
        qDebug()<<"sql database open failed";
}

/*
 * 功能：
 * 	 数据库连接
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::createConnection()
{
    p_db  = new QSqlDatabase;

    if (QSqlDatabase::contains("db_record")) {
        *p_db = QSqlDatabase::database("db_record");
    } else {
         *p_db = QSqlDatabase::addDatabase("QSQLITE");
         p_db->setDatabaseName("db_record");
    }

    if (!p_db->open())
        return false;

    return true;
}

void ThreadDataRecord::init()
{
    m_dispDataList.clear();
    m_dispDataCount = 0;
    m_dispDataLengthCount = 1;
    m_eventDataList.clear();
    m_eventDataCount = 0;
    m_eventDataLengthCount = 1;
    m_manualDataList.clear();
    m_reportDataList.clear();
}

/*
 * 功能：
 * 	  根据记录通道配置，将相关显示数据保存至数据库，涉及数据表：显示数据总表 && 显示数据表
 * 参数：
 * 	  1.DISPLAY_DATA_RECORD *dispData ：显示数据结构体指针，包含了所有通道的显示数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::dispDataRecord(DISPLAY_DATA_RECORD *dispData)
{
    //显示数据主表查询, 不存在则创建
    if (!isTableExist(DISP_MAIN_TABLE) && !createDispDataMainTable()) {
        qDebug()<<QString("%1: Error---Disp main table not exist!").arg(__func__);
        return;
    }

    //获取显示记录表名
    QString recordTableName = getDispSubTableName(DISP_MAIN_TABLE);
    if (recordTableName.isEmpty()) {
        qDebug()<<QString("%1: Error---Disp sub table empty!").arg(__func__);
        return;
    } else {
        addDispDataSub(recordTableName, dispData);
    }
}

/*
 * 功能：
 * 	  显示数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createDispDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //显示主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "FileFormat BLOB, "
                                     "FileInfo BLOB,"
                                     "BatchInfo BLOB,"
                                     "GroupInfo BLOB,"
                                     "ChannelInfo BLOB,"
                                     "SystemInfo BLOB,"
                                     "TimeTag INTEGER,"
                                     "StartTime INTEGER,"
                                     "EndTime INTEGER,"
                                     "StartStatus   INTEGER,"
                                     "EndStatus   INTEGER,"
                                     "DataCount INTEGER,"
                                     "FileName VARCHAR(50), "
                                     "RecordStatus INTEGER)").arg(DISP_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  显示数据子表创建
 * 参数：
 * 	  1.quint64 ID：显示数据子表序号，对应主表的主键ID
 * 返回值：
 * 	  成功：显示数据子表
 *       失败：空字符串
 */
QString ThreadDataRecord::createDispDataSubTable(quint64 ID)
{
    QSqlQuery query(*p_db);
    QString dispDataTableName;
    dispDataTableName = QString("DispData_%1").arg(ID);

    bool result = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "RecordTime INTEGER, "
                                     "Data BLOB)").arg(dispDataTableName));

    if (result)
        return dispDataTableName;
    else
        return QString();
}

/*
 * 功能：
 * 	 显示数据总表新记录添加
 * 参数：
 * 	  1.quint64 ID：记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::addNewRecordDispMain(quint64 ID)
{
    QSqlQuery query(*p_db);
    QByteArray blobData;
    QString tableName(DISP_MAIN_TABLE);
    bool ret;

    //主表记录添加
    query.prepare(QString("INSERT INTO %1 (ID, FileFormat, FileInfo, BatchInfo, GroupInfo,"
                                "ChannelInfo, SystemInfo, TimeTag, StartTime, EndTime, StartStatus, EndStatus, DataCount,"
                                  "FileName, RecordStatus) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(tableName));
    /*ID*/
    query.addBindValue(ID);
    /*FileFormat*/
    blobData.clear();
    blobData.append((const char *)&m_fileFormat, sizeof(SQL_FILE_FORMAT));
    query.addBindValue(blobData);
     /*FileInfo*/
    blobData.clear();
    blobData.append((const char *)&m_fileInfo, sizeof(SQL_FILE_INFO));
    query.addBindValue(blobData);
    /*BatchInfo*/
    blobData.clear();
    blobData.append((const char *)&m_batchInfo, sizeof(SQL_BATCH_INFO));
    query.addBindValue(blobData);
     /*GroupInfo*/
    blobData.clear();
    blobData.append((const char *)&m_groupInfo, sizeof(SQL_GROUP_INFO));
    if (m_groupInfo.groupNum>0) {
        blobData.append((const char*)p_groupInfo, sizeof(GROUP_INFO)*m_groupInfo.groupNum);
    }
    query.addBindValue(blobData);
     /*ChannelInfo*/
    blobData.clear();
    blobData.append((const char *)&m_channelInfoDisp, sizeof(SQL_RECORD_CHAN_INFO));
    if (m_channelInfoDisp.channelNum>0) {
        blobData.append((const char *)p_channelDisp, sizeof(CHAN_INFO)*m_channelInfoDisp.channelNum);
    }
    query.addBindValue(blobData);
    /*SystemInfo*/
    blobData.clear();
    blobData.append((const char *)&m_sysConfig, sizeof(SQL_SYS_CONFIG));
    query.addBindValue(blobData);
    /*TimeTag*/
    query.addBindValue(m_timeTag);
     /*StartTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
     /*EndTime*/
     query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
     /*StartStatus*/
     query.addBindValue(SQL_Record_Status_ManualKey);
     /*EndStatus*/
     query.addBindValue(SQL_Record_Status_Recording);
    /*DataCount*/
     query.addBindValue(1);
    /*FileName*/
     query.addBindValue(m_fileName_disp);
     /*RecordStatus*/
     if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
         query.addBindValue(SQL_Record_Sync_On_Unsaved);
     } else {
         query.addBindValue(SQL_Record_Sync_Off);
     }

     ret = query.exec();

     if (ret == false)
         qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	 显示数据总表记录更新，相关区域：结束时间、数据个数
 * 参数：
 *       2.quint64 dataCount：记录对应的数据表中的数据个数
 * 	  1.quint64 ID：需要更新的记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::updateRecordDispMain(quint64 dataCount, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    //主表记录更新：结束时间、数据个数
    query.prepare(QString("UPDATE %1 set EndTime=?, DataCount=? where ID=?").arg(DISP_MAIN_TABLE));
    /*EndTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
    /*DataCount*/
    query.addBindValue(dataCount);
    /*ID*/
    query.addBindValue(ID);

    ret = query.exec();

    if (ret == false)
        qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	 显示数据总表记录状态更新，相关区域：结束状态
 * 参数：
 *       2.SQL_Record_Status status：记录状态
 * 	  1.quint64 ID：需要更新的记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::endRecordDispMain(SQL_Record_Status status, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    //主表记录结束：结束状态
    query.prepare(QString("UPDATE %1 set EndStatus=?  where ID=?").arg(DISP_MAIN_TABLE));
    query.addBindValue(status);
    query.addBindValue(ID);

    ret = query.exec();

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  显示数据记录保存至显示数据表
 * 参数：
 * 	  1.QString dispTableName ：显示数据表名称
 *       2.DISPLAY_DATA_RECORD *dispData：显示数据，包含了所有通道
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addDispDataSub(QString dispTableName, DISPLAY_DATA_RECORD *dispData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;
    QByteArray blobData;
    DISPLAY_DATA *pData;
    quint32 dataCount = m_channelInfoDisp.channelNum;

    if (getTableMaxID(dispTableName, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, RecordTime, Data)"
                                    "VALUES(?, ?, ?)").arg(dispTableName));
        /*ID*/
        query.addBindValue(maxID);
        /*RecordTime*/
        query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
        /*DispData*/
        blobData.clear();
        blobData.append((const char *)&m_channelInfoDisp, sizeof(SQL_RECORD_CHAN_INFO));
        if (dataCount>0) {
            pData = new DISPLAY_DATA[dataCount];
            getDispBlobData(dispData, pData);
            blobData.append((const char *)pData, sizeof(DISPLAY_DATA)*dataCount);
            delete [] pData;
        }
        query.addBindValue(blobData);

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	  获取显示数据子表名称，用于添加显示数据记录
 * 参数：
 * 	  1.QString mainTable：显示数据主表名称
 * 返回值：
 * 	  成功：显示数据子表名称
 *       失败：空字符串
 */
QString ThreadDataRecord::getDispSubTableName(QString mainTable)
{
    QString dispDataTableName;
    quint64 count;
    quint64 maxID;

    //显示数据主表无记录时处理
    if (getTabelRecordNum(mainTable, &count) && (count == 0)){
        //第一条记录添加
       qDebug()<<QString("First record insert into %1").arg(mainTable);
       addNewRecordDispMain(1);

        //显示数据记录子表创建
       dispDataTableName = createDispDataSubTable(1);

       return dispDataTableName;
    }

    if (getTableMaxID(mainTable, &maxID)) {
        if (m_dispDataCount >= m_dispDataLengthCount) { /*显示数据记录分割*/
            m_dispDataCount = 0;
            //结束当前记录
            endRecordDispMain(SQL_Record_Status_AutoSplitter, maxID);
            //新记录添加
            addNewRecordDispMain(++maxID);

            //显示数据记录子表创建
           dispDataTableName = createDispDataSubTable(maxID);

           return dispDataTableName;
        } else {                                                                            /*显示数据正常记录*/
            dispDataTableName = QString("DispData_%1").arg(maxID);

            quint64 count;
            getTabelRecordNum(dispDataTableName, &count);
            //更新当前记录
            updateRecordDispMain(++count, maxID);

           return dispDataTableName;
        }

    }

    return QString();
}

/*
 * 功能：
 * 	  根据记录通道配置，将相关事件数据保存至数据库，涉及数据表：事件数据总表 && 事件数据子表
 * 参数：
 * 	  1.EVENT_DATA_RECORD *eventData ：事件数据结构体指针，包含了所有通道的事件数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::eventDataRecord(EVENT_DATA_RECORD *eventData)
{
    //事件数据主表查询，不存在则创建
    if (!isTableExist(EVENT_MAIN_TABLE) && !createEventDataMainTable()) {
        qDebug()<<QString("%1: Error---Event main table not exist!").arg(__func__);
        return;
    }

    //获取显示记录表名
    QString recordTableName = getEventSubTableName(EVENT_MAIN_TABLE);
    if (recordTableName.isEmpty()) {
        qDebug()<<QString("%1: Error---Event sub table empty!").arg(__func__);
        return;
    } else {
        addEventDataSub(recordTableName, eventData);
    }
}

/*
 * 功能：
 * 	  获取事件数据子表名称，用于添加事件数据记录
 * 参数：
 * 	  1.QString mainTable：事件数据主表名称
 * 返回值：
 * 	  成功：事件数据子表名称
 *       失败：空字符串
 */
QString ThreadDataRecord::getEventSubTableName(QString mainTable)
{
    QString eventDataTableName;
    quint64 count;
    quint64 maxID;

    //事件数据主表无记录时处理
    if (getTabelRecordNum(mainTable, &count) && (count ==0)) {
        //第一条记录添加
       qDebug()<<QString("First record insert into %1").arg(mainTable);
       addNewRecordEventMain(1);

        //事件数据记录子表创建
       eventDataTableName = createEventDataSubTable(1);

       return eventDataTableName;
    }

    if (getTableMaxID(mainTable, &maxID)) {
        if (m_eventDataCount >= m_eventDataLengthCount) { /*事件数据记录分割*/
            m_eventDataCount = 0;
            //结束当前记录
            endRecordEventMain(SQL_Record_Status_AutoSplitter, maxID);
            //新记录添加
            addNewRecordEventMain(++maxID);

            //事件数据记录子表创建
           eventDataTableName = createEventDataSubTable(maxID);

           return eventDataTableName;
        } else {                                                                            /*事件数据正常记录*/
            eventDataTableName = QString("EventData_%1").arg(maxID);

            quint64 count;
            getTabelRecordNum(eventDataTableName, &count);
            //更新当前记录
            updateRecordEventMain(++count, maxID);

           return eventDataTableName;
        }

    }

    return QString();
}

/*
 * 功能：
 * 	  事件数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createEventDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //事件主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                             "FileFormat BLOB, "
                             "FileInfo BLOB,"
                             "BatchInfo BLOB,"
                             "GroupInfo BLOB,"
                             "ChannelInfo BLOB,"
                             "SystemInfo BLOB,"
                             "TimeTag INTEGER, "
                             "StartTime INTEGER,"
                             "EndTime INTEGER,"
                             "StartStatus   INTEGER,"
                             "EndStatus   INTEGER,"
                             "DataCount INTEGER,"
                             "FileName VARCHAR(50), "
                             "RecordStatus INTEGER)").arg(EVENT_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  事件数据子表创建
 * 参数：
 * 	  1.quint64 ID：事件数据子表序号，对应主表的主键ID
 * 返回值：
 * 	  成功：事件数据子表
 *       失败：空字符串
 */
QString ThreadDataRecord::createEventDataSubTable(quint64 ID)
{
    QSqlQuery query(*p_db);
    QString eventDataTableName;
    eventDataTableName = QString("EventData_%1").arg(ID);

    bool result = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "RecordTime INTEGER, "
                                     "Data BLOB)").arg(eventDataTableName));

    if (result)
        return eventDataTableName;
    else
        return QString();
}

/*
 * 功能：
 * 	 事件数据总表新记录添加
 * 参数：
 * 	  1.quint64 ID：记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::addNewRecordEventMain(quint64 ID)
{
    QSqlQuery query(*p_db);
    QByteArray blobData;
    QString tableName(EVENT_MAIN_TABLE);
    bool ret;

    //主表记录添加
    query.prepare(QString("INSERT INTO %1 (ID, FileFormat, FileInfo, BatchInfo, GroupInfo,"
                                "ChannelInfo, SystemInfo, TimeTag, StartTime, EndTime, StartStatus, EndStatus, DataCount,"
                                  "FileName, RecordStatus) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(tableName));
    /*ID*/
    query.addBindValue(ID);
    /*FileFormat*/
    blobData.clear();
    blobData.append((const char *)&m_fileFormat, sizeof(SQL_FILE_FORMAT));
    query.addBindValue(blobData);
     /*FileInfo*/
    blobData.clear();
    blobData.append((const char *)&m_fileInfo, sizeof(SQL_FILE_INFO));
    query.addBindValue(blobData);
    /*BatchInfo*/
    blobData.clear();
    blobData.append((const char *)&m_batchInfo, sizeof(SQL_BATCH_INFO));
    query.addBindValue(blobData);
     /*GroupInfo*/
    blobData.clear();
    blobData.append((const char *)&m_groupInfo, sizeof(SQL_GROUP_INFO));
    if (m_groupInfo.groupNum>0) {
        blobData.append((const char*)p_groupInfo, sizeof(GROUP_INFO)*m_groupInfo.groupNum);
    }
    query.addBindValue(blobData);
     /*ChannelInfo*/
    blobData.clear();
    blobData.append((const char *)&m_channelInfoEvent, sizeof(SQL_RECORD_CHAN_INFO));
    if (m_channelInfoEvent.channelNum>0) {
        blobData.append((const char *)p_channelEvent, sizeof(CHAN_INFO)*m_channelInfoEvent.channelNum);
    }
    query.addBindValue(blobData);
    /*SystemInfo*/
    blobData.clear();
    blobData.append((const char *)&m_sysConfig, sizeof(SQL_SYS_CONFIG));
    query.addBindValue(blobData);
    /*TimeTag*/
    query.addBindValue(m_timeTag);
     /*StartTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
     /*EndTime*/
     query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
     /*StartStatus*/
     query.addBindValue(SQL_Record_Status_ManualKey);
     /*EndStatus*/
     query.addBindValue(SQL_Record_Status_Recording);
    /*DataCount*/
     query.addBindValue(1);
    /*FileName*/
     query.addBindValue(m_fileName_event);
     /*RecordStatus*/
     if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
         query.addBindValue(SQL_Record_Sync_On_Unsaved);
     } else {
         query.addBindValue(SQL_Record_Sync_Off);
     }

     ret = query.exec();

     if (ret == false)
         qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	 事件数据总表记录更新，相关区域：结束时间、数据个数
 * 参数：
 *       2.quint64 dataCount：记录对应的数据表中的数据个数
 * 	  1.quint64 ID：需要更新的记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::updateRecordEventMain(quint64 dataCount, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    //主表记录更新：结束时间、数据个数
    query.prepare(QString("UPDATE %1 set EndTime=?, DataCount=? where ID=?").arg(EVENT_MAIN_TABLE));
    /*EndTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
    /*DataCount*/
    query.addBindValue(dataCount);
    /*ID*/
    query.addBindValue(ID);

    ret = query.exec();

    if (ret == false)
        qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	 事件数据总表记录状态更新，相关区域：结束状态
 * 参数：
 *       2.SQL_Record_Status status：记录状态
 * 	  1.quint64 ID：需要更新的记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::endRecordEventMain(SQL_Record_Status status, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    //主表记录结束：结束状态
    query.prepare(QString("UPDATE %1 set EndStatus=?  where ID=?").arg(EVENT_MAIN_TABLE));
    query.addBindValue(status);
    query.addBindValue(ID);

    ret = query.exec();

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  事件数据记录保存至事件数据表
 * 参数：
 * 	  1.QString dispTableName ：事件数据表名称
 *       2.DISPLAY_DATA_RECORD *dispData：事件数据，包含了所有通道
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addEventDataSub(QString eventTableName, EVENT_DATA_RECORD *eventData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;
    QByteArray blobData;
    qreal *pData;
    quint32 dataCount = m_channelInfoEvent.channelNum;

    if (getTableMaxID(eventTableName, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, RecordTime, Data)"
                                    "VALUES(?, ?, ?)").arg(eventTableName));
        /*ID*/
        query.addBindValue(maxID);
        /*RecordTime*/
        query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
        /*DispData*/
        blobData.clear();
        blobData.append((const char *)&m_channelInfoEvent, sizeof(SQL_RECORD_CHAN_INFO));
        if (dataCount>0) {
            pData = new qreal[dataCount];
            getEventBlobData(eventData, pData);
            blobData.append((const char *)pData, sizeof(qreal)*dataCount);
            delete [] pData;
        }

        query.addBindValue(blobData);

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	  根据记录通道配置，将相关手动采样数据保存至数据库，涉及数据表：手动采样数据总表 && 手动采样数据子表
 * 参数：
 * 	  1.EVENT_DATA_RECORD *manualData ：手动采样数据结构体指针，包含了所有通道的手动采样数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::manualDataRecord(EVENT_DATA_RECORD *manualData)
{
    //手动采样数据主表查询, 不存在则创建
    if (!isTableExist(MANUAL_MAIN_TABLE) && !createManualDataMainTable()) {
        qDebug()<<QString("%1: Error---Manual main table not exist!").arg(__func__);
        return;
    }

    //获取显示记录表名
    QString recordTableName = getManualSubTableName(MANUAL_MAIN_TABLE);
    if (recordTableName.isEmpty()) {
        qDebug()<<QString("%1: Error---Manual sub table empty!").arg(__func__);
        return;
    } else {
        addManualDataSub(recordTableName, manualData);
    }
}

/*
 * 功能：
 * 	  获取手动采样数据子表名称，用于添加手动采样数据记录
 * 参数：
 * 	  1.QString mainTable：手动采样数据主表名称
 * 返回值：
 * 	  成功：手动采样数据子表名称
 *       失败：空字符串
 */
QString ThreadDataRecord::getManualSubTableName(QString mainTable)
{
    QString manualDataTableName;
    quint64 count;
    quint64 maxID;

    //手动采样数据主表无记录时处理
    if (getTabelRecordNum(mainTable, &count) && (count ==0)) {
        //第一条记录添加
       qDebug()<<QString("First record insert into %1").arg(mainTable);
       addNewRecordManualMain(1);

        //手动采样数据记录子表创建
       manualDataTableName = createManualDataSubTable(1);

       return manualDataTableName;
    }

    if (getTableMaxID(mainTable, &maxID)) {
        manualDataTableName = QString("ManualData_%1").arg(maxID);
        if (getTabelRecordNum(manualDataTableName, &count)) {
            if (count==MANUAL_SUB_RECORD_MAX){ /*手动采样数据记录分割*/
             //新记录添加
            addNewRecordManualMain(++maxID);

            //手动采样数据记录子表创建
            manualDataTableName = createManualDataSubTable(maxID);

            return manualDataTableName;

            } else {                                                            /*手动采样数据记录分割*/
                quint64 count;
                getTabelRecordNum(manualDataTableName, &count);
                //更新当前记录
                updateRecordManualMain(++count, maxID);

                 return manualDataTableName;
            }
        }
    }

    return QString();
}

/*
 * 功能：
 * 	  手动采样数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createManualDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //显示主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "FileFormat BLOB, "
                                     "FileInfo BLOB,"
                                     "BatchInfo BLOB,"
                                     "GroupInfo BLOB,"
                                     "ChannelInfo BLOB,"
                                     "SystemInfo BLOB,"
                                     "TimeTag INTEGER, "
                                     "LastTime INTEGER,"
                                     "DataCount INTEGER,"
                                     "FileName VARCHAR(50), "
                                    "RecordStatus INTEGER)").arg(MANUAL_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  手动采样数据子表创建
 * 参数：
 * 	  1.quint64 ID：手动采样数据子表序号，对应主表的主键ID
 * 返回值：
 * 	  成功：手动采样数据子表
 *       失败：空字符串
 */
QString ThreadDataRecord::createManualDataSubTable(quint64 ID)
{
    QSqlQuery query(*p_db);
    QString manualDataTableName;
    manualDataTableName = QString("ManualData_%1").arg(ID);

    bool result = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "RecordTime INTEGER, "
                                     "Data BLOB)").arg(manualDataTableName));

    if (result)
        return manualDataTableName;
    else
        return QString();
}

/*
 * 功能：
 * 	 手动采样数据总表新记录添加
 * 参数：
 * 	  1.quint64 ID：记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::addNewRecordManualMain(quint64 ID)
{
    QSqlQuery query(*p_db);
    QByteArray blobData;
    QString tableName(MANUAL_MAIN_TABLE);
    bool ret;
    quint64 count, minID;

    //手动采样主表记录数确认
    if (getTabelRecordNum(tableName, &count) && (count >= MANUAL_MAIN_RECORD_MAX)) {
        getTableMinID(tableName, &minID);
        deleteTableRecord(tableName, minID);
        dropTable(QString("ManualData_%1").arg(ID));
    }
    //主表记录添加
    query.prepare(QString("INSERT INTO %1 (ID, FileFormat, FileInfo, BatchInfo, GroupInfo, "
                                "ChannelInfo, SystemInfo, TimeTag, LastTime, DataCount, FileName, RecordStatus) "
                                  "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(tableName));
    /*ID*/
    query.addBindValue(ID);
    /*FileFormat*/
    blobData.clear();
    blobData.append((const char *)&m_fileFormat, sizeof(SQL_FILE_FORMAT));
    query.addBindValue(blobData);
     /*FileInfo*/
    blobData.clear();
    blobData.append((const char *)&m_fileInfo, sizeof(SQL_FILE_INFO));
    query.addBindValue(blobData);
    /*BatchInfo*/
    blobData.clear();
    blobData.append((const char *)&m_batchInfo, sizeof(SQL_BATCH_INFO));
    query.addBindValue(blobData);
     /*GroupInfo*/
    blobData.clear();
    blobData.append((const char *)&m_groupInfo, sizeof(SQL_GROUP_INFO));
    if (m_groupInfo.groupNum>0) {
        blobData.append((const char*)p_groupInfo, sizeof(GROUP_INFO)*m_groupInfo.groupNum);
    }
    query.addBindValue(blobData);
     /*ChannelInfo*/
    blobData.clear();
    blobData.append((const char *)&m_channelInfoManual, sizeof(SQL_RECORD_CHAN_INFO));
    if (m_channelInfoManual.channelNum>0) {
        blobData.append((const char *)p_channelManual, sizeof(CHAN_INFO)*m_channelInfoManual.channelNum);
    }
    query.addBindValue(blobData);
    /*SystemInfo*/
    blobData.clear();
    blobData.append((const char *)&m_sysConfig, sizeof(SQL_SYS_CONFIG));
    query.addBindValue(blobData);
    /*TimeTag*/
    query.addBindValue(m_timeTag);
     /*LastTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
    /*DataCount*/
     query.addBindValue(1);
    /*FileName*/
     query.addBindValue(m_fileName_disp);
     /*RecordStatus*/
     if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
         query.addBindValue(SQL_Record_Sync_On_Unsaved);
     } else {
         query.addBindValue(SQL_Record_Sync_Off);
     }

     ret = query.exec();

     if (ret == false)
         qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	 显示数据总表记录更新，相关区域：最新采样时间、数据个数
 * 参数：
 *       2.quint64 dataCount：记录对应的数据表中的数据个数
 * 	  1.quint64 ID：需要更新的记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::updateRecordManualMain(quint64 dataCount, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    //主表记录更新：结束时间、数据个数
    query.prepare(QString("UPDATE %1 set LastTime=?, DataCount=? where ID=?").arg(MANUAL_MAIN_TABLE));
    /*EndTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
    /*DataCount*/
    query.addBindValue(dataCount);
    /*ID*/
    query.addBindValue(ID);

    ret = query.exec();

    if (ret == false)
        qDebug()<<query.lastError().text();

    return ret;
}


//bool ThreadDataRecord::endRecordManualMain(SQL_Record_Status status, quint64 ID)
//{

//}

/*
 * 功能：
 * 	  手动采样数据记录保存至手动采样数据表
 * 参数：
 * 	  1.QString dispTableName ：手动采样数据表名称
 *       2.EVENT_DATA_RECORD *manualData：手动采样数据，包含了所有通道
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addManualDataSub(QString manualTableName, EVENT_DATA_RECORD *manualData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;
    QByteArray blobData;
    qreal *pData;
    quint32 dataCount = m_channelInfoManual.channelNum;

    if (getTableMaxID(manualTableName, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, RecordTime, Data)"
                                    "VALUES(?, ?, ?)").arg(manualTableName));
        /*ID*/
        query.addBindValue(maxID);
        /*RecordTime*/
        query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
        /*DispData*/
        blobData.clear();
        blobData.append((const char *)&m_channelInfoManual, sizeof(SQL_RECORD_CHAN_INFO));
        if (dataCount>0) {
            pData = new qreal[dataCount];
            getManualBlobData(manualData, pData);
            blobData.append((const char *)pData, sizeof(qreal)*dataCount);
            delete [] pData;
        }
        query.addBindValue(blobData);

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	  根据报表配置，将相关报表数据保存至数据库，涉及数据表：报表数据总表 && 报表数据子表
 * 参数：
 * 	  1.REPORT_DATA_RECORD *reportData ：报表数据结构体指针，包含了所有通道的报表数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::reportDataRecord(REPORT_DATA_RECORD *reportData)
{
    //报表数据主表查询, 不存在则创建
    if (!isTableExist(REPORT_MAIN_TABLE) && !createReportDataMainTable()) {
        qDebug()<<QString("%1: Error---Report main table not exist!").arg(__func__);
        return;
    }

    //获取报表记录表名
    QString recordTableName = getReportSubTableName(REPORT_MAIN_TABLE);
    if (recordTableName.isEmpty()) {
        qDebug()<<QString("%1: Error---Report sub table empty!").arg(__func__);
        return;
    } else {
        addReportDataSub(recordTableName, reportData);
    }
}

/*
 * 功能：
 * 	  获取报表数据子表名称，用于添加报表数据记录
 * 参数：
 * 	  1.QString mainTable：报表数据主表名称
 * 返回值：
 * 	  成功：报表数据子表名称
 *       失败：空字符串
 */
QString ThreadDataRecord::getReportSubTableName(QString mainTable)
{
    QString reportDataTableName;
    quint64 count;
    quint64 maxID;

    //报表数据主表无记录时处理
    if (getTabelRecordNum(mainTable, &count) && (count ==0)) {
        //第一条记录添加
       qDebug()<<QString("First record insert into %1").arg(mainTable);
       addNewRecordReportMain(1);

        //报表数据记录子表创建
       reportDataTableName = createReportDataSubTable(1);

       return reportDataTableName;
    }

    if (getTableMaxID(mainTable, &maxID)) {
        /*报表数据正常记录*/
        reportDataTableName = QString("ReportData_%1").arg(maxID);

        return reportDataTableName;
    }

    return QString();
}

/*
 * 功能：
 * 	  报表数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createReportDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //显示主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "FileFormat BLOB, "
                                     "FileInfo BLOB,"
                                     "BatchInfo BLOB,"
                                     "GroupInfo BLOB,"
                                     "ReportInfo BLOB,"
                                     "SystemInfo BLOB,"
                                     "TimeTag INTEGER, "
                                     "StartTime INTEGER,"
                                     "EndTime INTEGER,"
                                     "FileName VARCHAR(50), "
                                    "RecordStatus INTEGER)").arg(REPORT_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  报表数据子表创建
 * 参数：
 * 	  1.quint64 ID：事件数据子表序号，对应主表的主键ID
 * 返回值：
 * 	  成功：报表数据子表
 *       失败：空字符串
 */
QString ThreadDataRecord::createReportDataSubTable(quint64 ID)
{
    QSqlQuery query(*p_db);
    QString reportDataTableName;
    reportDataTableName = QString("ReportData_%1").arg(ID);

    bool result = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "RecordTime INTEGER, "
                                     "Data BLOB)").arg(reportDataTableName));

    if (result)
        return reportDataTableName;
    else
        return QString();
}

/*
 * 功能：
 * 	 报表数据总表新记录添加
 * 参数：
 * 	  1.quint64 ID：记录主键ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::addNewRecordReportMain(quint64 ID)
{
    QSqlQuery query(*p_db);
    QByteArray blobData;
    QString tableName(REPORT_MAIN_TABLE);
    bool ret;

    //主表记录添加
    query.prepare(QString("INSERT INTO %1 (ID, FileFormat, FileInfo, BatchInfo, GroupInfo,"
                                "ReportInfo, SystemInfo, TimeTag, StartTime, EndTime, "
                                  "FileName, RecordStatus) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(tableName));
    /*ID*/
    query.addBindValue(ID);
    /*FileFormat*/
    blobData.clear();
    blobData.append((const char *)&m_fileFormat, sizeof(SQL_FILE_FORMAT));
    query.addBindValue(blobData);
     /*FileInfo*/
    blobData.clear();
    blobData.append((const char *)&m_fileInfo, sizeof(SQL_FILE_INFO));
    query.addBindValue(blobData);
    /*BatchInfo*/
    blobData.clear();
    blobData.append((const char *)&m_batchInfo, sizeof(SQL_BATCH_INFO));
    query.addBindValue(blobData);
     /*GroupInfo*/
    blobData.clear();
    blobData.append((const char *)&m_groupInfo, sizeof(SQL_GROUP_INFO));
    if (m_groupInfo.groupNum>0) {
        blobData.append((const char*)p_groupInfo, sizeof(GROUP_INFO)*m_groupInfo.groupNum);
    }
    query.addBindValue(blobData);
     /*ReportInfo*/
    blobData.clear();
    blobData.append((const char *)&m_reportInfo, sizeof(SQL_REPORT_INFO));
    query.addBindValue(blobData);
    /*SystemInfo*/
    blobData.clear();
    blobData.append((const char *)&m_sysConfig, sizeof(SQL_SYS_CONFIG));
    query.addBindValue(blobData);
    /*TimeTag*/
    query.addBindValue(m_timeTag);
     /*StartTime*/
    query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
     /*EndTime*/
     query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
    /*FileName*/
     query.addBindValue(m_fileName_event);
     /*RecordStatus*/
     if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
         query.addBindValue(SQL_Record_Sync_On_Unsaved);
     } else {
         query.addBindValue(SQL_Record_Sync_Off);
     }

     ret = query.exec();

     if (ret == false)
         qDebug()<<query.lastError().text();

    return ret;
}

/*
 * 功能：
 * 	  报表数据记录保存至报表数据子表
 * 参数：
 * 	  1.QString dispTableName ：报表数据子表名称
 *       2.EVENT_DATA_RECORD *manualData：报表数据，包含了所有通道
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addReportDataSub(QString reportTableName, REPORT_DATA_RECORD *reportData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;
    QByteArray blobData;
    qreal *pData;
    quint32 dataCount = 0;

    for (int i=0; i<REPORT_CHAN_NUM; ++i) {
        if(m_reportInfo.reportInfo.reportChannelType[i] != Channel_Type_Off)
            dataCount++;
    }

    if (dataCount && getTableMaxID(reportTableName, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, RecordTime, Data)"
                                    "VALUES(?, ?, ?)").arg(reportTableName));
        /*ID*/
        query.addBindValue(maxID);
        /*RecordTime*/
        query.addBindValue(QDateTime::currentDateTime().toMSecsSinceEpoch());
        /*Data*/
        blobData.clear();
        blobData.append((const char *)&m_channelInfoManual, sizeof(SQL_RECORD_CHAN_INFO));
        if (dataCount>0) {
            quint32 size = sizeof(qreal) * 5 * dataCount;
            pData = (qreal *)::malloc(size);
            getReportBlobData(reportData, pData);
            blobData.append((const char *)pData, size);
            free(pData);
        }
        query.addBindValue(blobData);

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	 根据配置，获取需要生成报表的通道数据保存至“pData”
 * 参数：
 * 	  1.REPORT_DATA_RECORD *reportData：报表数据对象指针
 *       2.void *pData：报表数据保存地址
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::getReportBlobData(REPORT_DATA_RECORD *reportData, qreal *pData)
{
    for (int i=0; i<REPORT_CHAN_NUM; ++i) {
        if(m_reportInfo.reportInfo.reportChannelType[i] != Channel_Type_Off) {
            for (int j=0; j<5; ++j){
                switch (m_reportInfo.reportInfo.reportDataType[j]) {
                case Report_Data_Type_AVG:
                    *pData++ = reportData->reportAve[i];
                    break;
                case Report_Data_Type_MAX:
                    *pData++ = reportData->reportMax[i];
                    break;
                case Report_Data_Type_MIN:
                    *pData++ = reportData->reportMin[i];
                    break;
                case Report_Data_Type_SUM:
                    *pData++ = reportData->reportSum[i];
                    break;
                case Report_Data_Type_INST:
                    *pData++ = reportData->reportReal[i];
                    break;
                }
            }
        }
    }
}

/*
 * 功能：
 * 	  报警数据记录
 * 参数：
 * 	  1.ALARM_DATA * alarmData ：报警数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::alarmDataRecord(ALARM_DATA * alarmData)
{
    //报警数据主表查询, 不存在则创建
    if (!isTableExist(ALARM_MAIN_TABLE) && !createAlarmDataMainTable()) {
        qDebug()<<QString("%1: Error---Alarm table not exist!").arg(__func__);
        return;
    }

    //数据记录保存
    addAlarmData(alarmData);
}

/*
 * 功能：
 * 	 报警数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createAlarmDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //报警数据主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "AlarmStatus  INTEGER, "
                                     "TagString VARCHAR(40), "
                                     "TagNo VARCHAR(40), "
                                     "ChanNO INTEGER, "
                                     "Level INTEGER, "
                                     "Type INTEGER, "
                                     "TimeTag INTEGER, "
                                     "Time INTEGER, "
                                     "RecordStatus INTEGER)").arg(ALARM_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  报警数据记录保存
 * 参数：
 * 	  1.ALARM_DATA * alarmData ：报警数据
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addAlarmData(ALARM_DATA * alarmData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;

    if (getTableMaxID(ALARM_MAIN_TABLE, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, AlarmStatus, TagString, TagNo, ChanNO, Level, Type, TimeTag, Time, RecordStatus)"
                                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(ALARM_MAIN_TABLE));
        /*ID*/
        query.addBindValue(maxID);
        /*AlarmStatus*/
        query.addBindValue(alarmData->alarmStatus);
        /*TagString*/
        query.addBindValue(QString((const char *)&alarmData->alarmTagChar));
        /*TagNo*/
        query.addBindValue(QString((const char *)&alarmData->alarmTagNo));
        /*ChanNO*/
        query.addBindValue(alarmData->alarmChanNum);
        /*Level*/
        query.addBindValue(alarmData->alarmLevelNo);
        /*Type*/
        query.addBindValue(alarmData->alarmType);
        /*TimeTag*/
        query.addBindValue(m_timeTag);
        /*Time*/
        query.addBindValue(alarmData->alarmTime);
        /*RecordStatus*/
        if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
            query.addBindValue(SQL_Record_Sync_On_Unsaved);
        } else {
            query.addBindValue(SQL_Record_Sync_Off);
        }

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	  消息数据记录
 * 参数：
 * 	  1.MSG_DATA *msgData ：消息数据
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::msgDataRecord(MSG_DATA *msgData)
{
    //手动采样数据主表查询, 不存在则创建
    if (!isTableExist(MESSAGE_MAIN_TABLE) && !createMsgDataMainTable()) {
        qDebug()<<QString("%1: Error---Message table not exist!").arg(__func__);
        return;
    }

    //数据记录保存
    addMsgData(msgData);
}

/*
 * 功能：
 * 	  消息数据总表创建
 * 参数：
 * 	  无
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::createMsgDataMainTable()
{
    QSqlQuery query(*p_db);
    bool ret;

    //消息数据主表创建
    ret = query.exec(QString("create table %1 (ID INTEGER primary key, "
                                     "Type  INTEGER, "
                                     "Group INTEGER, "
                                     "TimeTag INTEGER, "
                                     "Time INTEGER, "
                                     "MsgData BLOB, "
                                     "RecordStatus INTEGER)").arg(MESSAGE_MAIN_TABLE));

    if (ret == false)
        qDebug()<<query.lastError().text();

   return ret;
}

/*
 * 功能：
 * 	  消息数据记录保存
 * 参数：
 * 	  1.MSG_DATA *msgData ：消息数据
 * 返回值：
 * 	  成功：true, 失败：false
 */
bool ThreadDataRecord::addMsgData(MSG_DATA *msgData)
{
    QSqlQuery query(*p_db);
    bool ret;
    quint64 maxID;
    QByteArray blobData;

    if (getTableMaxID(MESSAGE_MAIN_TABLE, &maxID)) {
        maxID++;

        query.prepare(QString("INSERT INTO %1 (ID, Type, Group, TimeTag, Time, MsgData, RecordStatus)"
                                    "VALUES(?, ?, ?, ?, ?, ?, ?)").arg(MESSAGE_MAIN_TABLE));
        /*ID*/
        query.addBindValue(maxID);
        /*Type*/
        query.addBindValue(msgData->msgType);
        /*Group*/
        query.addBindValue(msgData->msgGrp);
        /*TimeTag*/
        query.addBindValue(m_timeTag);
        /*Time*/
        query.addBindValue(msgData->msgTime);
        /*MsgData*/
        blobData.clear();
        blobData.append((const char *)&msgData->pMsgData, msgData->msgSize);
        query.addBindValue(blobData);
        /*RecordStatus*/
        if (p_gDeviceCfg->dataSaveConfig.datasaveExtMediaAuto) {
            query.addBindValue(SQL_Record_Sync_On_Unsaved);
        } else {
            query.addBindValue(SQL_Record_Sync_Off);
        }

        ret = query.exec();

        if (ret == false)
            qDebug()<<query.lastError().text();

       return ret;
    }

    return false;
}

/*
 * 功能：
 * 	 查询表“tableName”是否存在
 * 参数：
 * 	  1.QString tableName：被查询的表名称
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::isTableExist(QString tableName)
{
    QSqlQuery query(*p_db);
    bool ret;

    ret = query.exec(QString("select COUNT(*) from sqlite_master where type='table' and name='%1'").arg(tableName));

    if (ret == false) {
        qDebug()<<query.lastError().text();
        return false;
    }

    if (query.next()) {
        int result = query.value(0).toInt();

        if (result)
            return true;
    }

    return false;
}

/*
 * 功能：
 * 	 查询表“tableName”记录数
 * 参数：
 * 	  1.QString tableName：被查询的表名称
 *       2.quint64 *pCount：表记录数存放指针
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::getTabelRecordNum(QString tableName, quint64 *pCount)
{
    QSqlQuery query(*p_db);
    bool ret;

    ret = query.exec(QString("select COUNT(*) from %1").arg(tableName));

    if (ret == false) {
        qDebug()<<query.lastError().text();
        return false;
    }

    if (query.next()) {
        qulonglong result = query.value(0).toULongLong();

            *pCount = result;
            return true;
    }

    return false;
}

/*
 * 功能：
 * 	 查询表“tableName”，获取其最大的ID号
 * NOTE！
 *       ****表“tableName”必须以ID作为主键****
 * 参数：
 * 	  1.QString tableName：被查询的表名称
 *       2.quint64 *pID：ID最大值存放指针
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::getTableMaxID(QString tableName, quint64 *pID)
{
   QSqlQuery query(*p_db);
   bool ret;

   ret = query.exec(QString("SELECT MAX(ID) FROM %1").arg(tableName));

   if (ret == false) {
       qDebug()<<query.lastError().text();
       return false;
   }

   if (query.next()) {
       qulonglong maxID = query.value(0).toULongLong();

       *pID = maxID;
       return true;
   }

   *pID = 0;
   return false;
}

/*
 * 功能：
 * 	 查询表“tableName”，获取其最小的ID号
 * NOTE！
 *       ****表“tableName”必须以ID作为主键****
 * 参数：
 * 	  1.QString tableName：被查询的表名称
 *       2.quint64 *pID：ID最小值存放指针
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::getTableMinID(QString tableName, quint64 *pID)
{
    QSqlQuery query(*p_db);
    bool ret;

    ret = query.exec(QString("SELECT MIN(ID) FROM %1").arg(tableName));

    if (ret == false) {
        qDebug()<<query.lastError().text();
        return false;
    }

    if (query.next()) {
        qulonglong minID = query.value(0).toULongLong();

        *pID = minID;
        return true;
    }

    *pID = 0;
    return false;
}

/*
 * 功能：
 * 	 删除表“tableName”中ID号为“ID”的记录
 * NOTE！
 *       ****表“tableName”必须以ID作为主键****
 * 参数：
 * 	  1.QString tableName：被查询的表名称
 *       2.quint64 ID：ID号
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::deleteTableRecord(QString tableName, quint64 ID)
{
    QSqlQuery query(*p_db);
    bool ret;

    ret = query.exec(QString("DELETE FROM %1 WHERE ID=%2").arg(tableName).arg(ID));

    if (ret == false) {
        qDebug()<<query.lastError().text();
    }

    return ret;
}

/*
 * 功能：
 * 	 删除表“tableName”
 * 参数：
 * 	  1.QString tableName：表名称
 * 返回值：
 * 	  成功：true
 *       失败：false
 */
bool ThreadDataRecord::dropTable(QString tableName)
{
    QSqlQuery query(*p_db);
    bool ret;

    ret = query.exec(QString("DROP TABLE %1").arg(tableName));

    if (ret == false) {
        qDebug()<<query.lastError().text();
    }

    return ret;
}

/*
 * 功能：
 * 	 根据配置，获取需要记录的通道数据保存至“pData”
 * 参数：
 * 	  1.DISPLAY_DATA_RECORD *dispData：显示数据
 *       2.void *pData：显示数据保存地址
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::getDispBlobData(DISPLAY_DATA_RECORD *dispData, DISPLAY_DATA *pData)
{
    CHAN_INFO *pDispChannelConfig = p_channelDisp;
    quint32 channelNum;
    quint16 chanType, uninNum, moduleIndex, number;

    for(quint32 i=0; i<m_channelInfoDisp.channelNum; ++i) {
        channelNum = pDispChannelConfig->chanNum;
        chanType = CHANNEL_TYPE(channelNum);           //通道类型
        uninNum = CHANNEL_UNIT(channelNum);           //单元号
        moduleIndex = CHANNEL_MODULE(channelNum);  //卡槽号
        number = CHANNEL_NUM(channelNum);              //通道号

        switch (chanType) {
        case Channel_Type_AI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
                if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                    //should never run here!
                    break;
                } else {
                    pData->Max = dispData->mainUnit_AI_Data[moduleIndex][number].Max;
                    pData->Min = dispData->mainUnit_AI_Data[moduleIndex][number].Min;
                }
            } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
                pData->Max = dispData->extUnit_AI_Data[uninNum][moduleIndex][number].Max;
                pData->Min = dispData->extUnit_AI_Data[uninNum][moduleIndex][number].Min;
            }
            break;
        case Channel_Type_DI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                pData->Max = dispData->mainUnit_DI_Data[moduleIndex][number].Max;
                pData->Min = dispData->mainUnit_DI_Data[moduleIndex][number].Min;
            }
            break;
        case Channel_Type_DO:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                pData->Max = dispData->mainUnit_DO_Data[moduleIndex][number].Max;
                pData->Min = dispData->mainUnit_DO_Data[moduleIndex][number].Min;
            }
            break;
        case Channel_Type_Comm:
            if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
                break;
            pData->Max = dispData->device_Comm_Data[number].Max;
            pData->Min = dispData->device_Comm_Data[number].Min;
            break;
        case Channel_Type_Math:
            if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
                break;
            pData->Max = dispData->device_Math_Data[number].Max;
            pData->Min = dispData->device_Math_Data[number].Min;
            break;
        default:
            break;
        }

        pData++;
        pDispChannelConfig++;
    }
}

/*
 * 功能：
 * 	 根据配置，获取需要记录的通道数据保存至“pData”
 * 参数：
 * 	  1.DISPLAY_DATA_RECORD *dispData：事件数据
 *       2.void *pData：事件数据保存地址
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::getEventBlobData(EVENT_DATA_RECORD *eventData, qreal *pData)
{
    CHAN_INFO *pEventChannelConfig = p_channelEvent;
    quint32 channelNum;
    quint16 chanType, uninNum, moduleIndex, number;

    for(quint32 i=0; i<m_channelInfoEvent.channelNum; ++i) {
        channelNum = pEventChannelConfig->chanNum;
        chanType = CHANNEL_TYPE(channelNum);           //通道类型
        uninNum = CHANNEL_UNIT(channelNum);           //单元号
        moduleIndex = CHANNEL_MODULE(channelNum);  //卡槽号
        number = CHANNEL_NUM(channelNum);              //通道号

        switch (chanType) {
        case Channel_Type_AI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
                if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                    //should never run here!
                    break;
                } else {
                    *pData = eventData->mainUnit_AI_Data[moduleIndex][number];
                }
            } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
               *pData = eventData->extUnit_AI_Data[uninNum][moduleIndex][number];
            }
            break;
        case Channel_Type_DI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                *pData = eventData->mainUnit_DI_Data[moduleIndex][number];
            }
            break;
        case Channel_Type_DO:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                *pData = eventData->mainUnit_DO_Data[moduleIndex][number];
            }
            break;
        case Channel_Type_Comm:
            if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
                break;
            *pData = eventData->device_Comm_Data[number];
            break;
        case Channel_Type_Math:
            if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
                break;
            *pData = eventData->device_Math_Data[number];
            break;
        default:
            break;
        }

        pData++;
        pEventChannelConfig++;
    }
}

void ThreadDataRecord::getManualBlobData(EVENT_DATA_RECORD *manualData, qreal *pData)
{
    CHAN_INFO *pManualChannelConfig = p_channelManual;
    quint32 channelNum;
    quint16 chanType, uninNum, moduleIndex, number;

    for(quint32 i=0; i<m_channelInfoManual.channelNum; ++i) {
        channelNum = pManualChannelConfig->chanNum;
        chanType = CHANNEL_TYPE(channelNum);           //通道类型
        uninNum = CHANNEL_UNIT(channelNum);           //单元号
        moduleIndex = CHANNEL_MODULE(channelNum);  //卡槽号
        number = CHANNEL_NUM(channelNum);              //通道号

        switch (chanType) {
        case Channel_Type_AI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
                if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                    //should never run here!
                    break;
                } else {
                    *pData = manualData->mainUnit_AI_Data[moduleIndex][number];
                }
            } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
               *pData = manualData->extUnit_AI_Data[uninNum][moduleIndex][number];
            }
            break;
        case Channel_Type_DI:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                *pData = manualData->mainUnit_DI_Data[moduleIndex][number];
            }
            break;
        case Channel_Type_DO:
            if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
                *pData = manualData->mainUnit_DO_Data[moduleIndex][number];
            }
            break;
        case Channel_Type_Comm:
            if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
                break;
            *pData = manualData->device_Comm_Data[number];
            break;
        case Channel_Type_Math:
            if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
                break;
            *pData = manualData->device_Math_Data[number];
            break;
        default:
            break;
        }

        pData++;
        pManualChannelConfig++;
    }
}

/*
 * 功能：
 * 	 数据存储处理
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::slotDataProcess()
{
    //显示数据处理
    p_db->transaction();
    m_dispLock.lock();
    while (m_dispDataList.count() > 0) {
        DISPLAY_DATA_RECORD *dataPtr;
        dataPtr = static_cast<DISPLAY_DATA_RECORD *>(m_dispDataList.dequeue());
        //显示数据保存
        dispDataRecord(dataPtr);
        //内存释放
        delete dataPtr;
    }
    m_dispLock.unlock();

    //事件数据处理
    m_eventLock.lock();
    while (m_eventDataList.count() > 0) {
        EVENT_DATA_RECORD *dataPtr;
        dataPtr = static_cast<EVENT_DATA_RECORD *>(m_eventDataList.dequeue());
        //事件数据保存
        eventDataRecord(dataPtr);

        //内存释放
        delete dataPtr;
    }
    m_eventLock.unlock();

    //手动采样数据处理
    m_manualLock.lock();
    while (m_manualDataList.count() > 0) {
        EVENT_DATA_RECORD *dataPtr;
        dataPtr = static_cast<EVENT_DATA_RECORD *>(m_manualDataList.dequeue());
        //手动采样数据保存
        manualDataRecord(dataPtr);

        //内存释放
        delete dataPtr;
    }
    m_manualLock.unlock();

    //报表数据处理
    m_reportLock.lock();
    while (m_reportDataList.count() > 0) {
        REPORT_DATA_RECORD *dataPtr;
        dataPtr = static_cast<REPORT_DATA_RECORD *>(m_reportDataList.dequeue());
        //报表数据保存
        reportDataRecord(dataPtr);

        //内存释放
        delete dataPtr;
    }
    m_reportLock.unlock();

    //报警数据处理
    m_alarmLock.lock();
    while (m_AlarmDataList.count() > 0) {
        ALARM_DATA *dataPtr;
        dataPtr = static_cast<ALARM_DATA *>(m_AlarmDataList.dequeue());
        //报表数据保存
        alarmDataRecord(dataPtr);

        //内存释放
        delete dataPtr;
    }
    m_alarmLock.unlock();


    //消息数据处理
    m_messageLock.lock();
    while (m_messageDataList.count() > 0) {
        MSG_DATA *dataPtr;
        dataPtr = static_cast<MSG_DATA *>(m_messageDataList.dequeue());
        //报表数据保存
        msgDataRecord(dataPtr);

        //内存释放
        free(dataPtr->pMsgData);
        free(dataPtr);
    }
    m_messageLock.unlock();

    p_db->commit();
}


void ThreadDataRecord::run()
{
    p_timer = new QTimer;

    p_timer->start(100);

    connect(p_timer, SIGNAL(timeout()), this, SLOT(slotDataProcess()));

    exec();
}

/*
 * 功能：
 * 	 显示数据保存对象添加
 * 参数：
 * 	  1.DISPLAY_DATA_RECORD *dispData: 显示数据对象指针
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newDispData(DISPLAY_DATA_RECORD *dispData)
{
    void *ptr;
    ptr = new DISPLAY_DATA_RECORD;

    if (ptr) {
        ::memcpy(ptr, dispData, sizeof(DISPLAY_DATA_RECORD));
        m_dispLock.lock();
        m_dispDataList.enqueue(ptr);
        m_dispLock.unlock();
    } else {
        qDebug()<<"memory alloc failed on disp data";
    }
}


/*
 * 功能：
 * 	 事件数据保存对象添加
 * 参数：
 * 	  1.EVENT_DATA_RECORD *eventData: 事件数据对象指针
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newEventData(EVENT_DATA_RECORD *eventData)
{
    void *ptr;
    ptr = new EVENT_DATA_RECORD;

    if (ptr) {
        ::memcpy(ptr, eventData, sizeof(EVENT_DATA_RECORD));
        m_eventLock.lock();
        m_eventDataList.enqueue(ptr);
        m_eventLock.unlock();
    } else {
        qDebug()<<"memory alloc failed on event data";
    }
}


/*
 * 功能：
 * 	 手动采样数据保存对象添加
 * 参数：
 * 	  1.EVENT_DATA_RECORD *manualData: 手动采数据对象指针
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newManualData(EVENT_DATA_RECORD *manualData)
{
    void *ptr;
    ptr = new EVENT_DATA_RECORD;

    if (ptr) {
        ::memcpy(ptr, manualData, sizeof(EVENT_DATA_RECORD));
        m_manualLock.lock();
        m_manualDataList.enqueue(ptr);
        m_manualLock.unlock();
    } else {
        qDebug()<<"memory alloc failed on manual data";
    }
}

/*
 * 功能：
 * 	 报表数据保存对象添加
 * 参数：
 * 	  1.REPORT_DATA_RECORD *reportData: 报表数据对象指针
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newReportData(REPORT_DATA_RECORD *reportData)
{
    void *ptr;
    ptr = new REPORT_DATA_RECORD;

    if (ptr) {
        ::memcpy(ptr, reportData, sizeof(REPORT_DATA_RECORD));
        m_reportLock.lock();
        m_reportDataList.enqueue(ptr);
        m_reportLock.unlock();
    } else {
        qDebug()<<"memory alloc failed on report data";
    }
}

/*
 * 功能：
 * 	 报警数据记录添加
 * 参数：
 * 	  1.ALARM_DATA *alarmData: 报警数据对象指针
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newAlarmData(ALARM_DATA *alarmData)
{
    void *ptr;
    ptr = new ALARM_DATA;

    if (ptr) {
        ::memcpy(ptr, alarmData, sizeof(ALARM_DATA));
        m_alarmLock.lock();
        m_AlarmDataList.enqueue(ptr);
        m_alarmLock.unlock();
    } else {
        qDebug()<<"memory alloc failed on alarm data";
    }
}

/*
 * 功能：
 * 	 消息数据保存, 消息一览数据表
 * 参数：
 * 	  1.MSG_DATA *msgData : 消息数据结构体
 * 返回值：
 * 	  无
 */
void ThreadDataRecord::newMessageData(MSG_DATA *msgData)
{
    void *ptr, *ptrData;

    ptr = ::malloc(sizeof(MSG_DATA));

    if (ptr) {
        if (msgData->msgSize > 0) {
            ptrData = ::malloc(msgData->msgSize);
            if (ptrData) {
                ::memcpy(ptr, msgData, sizeof(MSG_DATA));
                ::memcpy(ptrData, msgData->pMsgData, msgData->msgSize);
                ((MSG_DATA*)ptr)->pMsgData = ptrData;
                m_messageLock.lock();
                m_messageDataList.enqueue(ptr);
                m_messageLock.unlock();
            } else {
                goto ERROR;
            }
        } else {
            qDebug("Error--No message data!");
        }
    } else {
        qDebug()<<"memory alloc failed on message data-0";
        return;
    }

ERROR:
    qDebug()<<"memory alloc failed on message data-1";
    free(ptr);
}
