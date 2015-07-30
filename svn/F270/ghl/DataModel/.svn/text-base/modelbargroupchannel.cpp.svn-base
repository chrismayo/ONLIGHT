#include "modelbargroupchannel.h"
#include "./GlobalData/cfgGlobalDef.h"
#include "../GlobalData/cfgchannel.h"

#include <QDebug>
#include <QColor>
#include <QDateTime>

extern DEVICE_CONFIG                   *p_gDeviceCfg;        //全局变量指针，指向LPSRAM中的设备配置结构

ModelBarGroupChannel::ModelBarGroupChannel(quint32 grpIndex, QObject *parent) :
    m_grpIndex(grpIndex),
    QAbstractTableModel(parent)
{
    init();
}
int ModelBarGroupChannel::rowCount(const QModelIndex &) const
{
    //qDebug()<<"row"<<m_list_channel.size();
    switch (m_list_channel.size()) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return 1;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        return 2;
    default:
        return 0;
    }
}
int ModelBarGroupChannel::columnCount(const QModelIndex &) const
{
    //qDebug()<<"column"<<m_list_channel.size();
    switch (m_list_channel.size()) {
    case 1:
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
    case 12:
        return 6;
    case 13:
    case 14:
        return 7;
    case 15:
    case 16:
        return 8;
    case 17:
    case 18:
        return 9;
    case 19:
    case 20:
        return 10;
    default:
        return 0;
    }
}

/*
 * 功能：
 * 	 根据模型索引以及数据角色提供相应的数据
 * 参数：
 * 	  1.QModelIndex &index: 模型索引
 *       2.int role: 角色
 * 返回值：
 * 	  QVariant
 */
QVariant ModelBarGroupChannel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role)
    {
    case ChannelData:
        return getChData(row,col);
    case ChannelType:
        return getChType(row, col);
    case ChannelTag:
        return getChTag(row, col);
    case ChannelColor:
        return getChColor(row, col);
    case ChannelUnit:
        return getChUnit(row, col);
    case ChannelRangeUpper:
        return getChRangeUpper(row, col);
    case ChannelRangeDowner:
        return getChRangeDowner(row, col);
    case ChannelDispUpper:
        return getChDispUpper(row, col);
    case ChannelDispDowner:
        return getChDispDowner(row, col);
    case ChannelScalePos:
        return getChScalePos(row, col);
    case ChannelSacleDiv:
        return getChScaleDiv(row, col);
    case ChannelBarBase:
        return getChBarBase(row, col);
    case ChannelBarDiv:
        return getChBarDiv(row, col);
//    case ChannelPartScaleOnOff:
//        return getChPartScaleOnOff(row, col);
//    case ChannelPartScalePos:
//        return getChPartScalePos(row, col);
//    case ChannelPartScaleBound:
//        return getChPartScaleBound(row, col);
//    case ChannelColorScalePos:
//        return getChColorScalePos(row, col);
//    case ChannelColorScaleColor:
//        return getChColorScaleColor(row, col);
//    case ChannelColorScaleUpper:
//        return getChColorScaleUpper(row, col);
//    case ChannelColorScaleDowner:
//        return getChColorScaleDowner(row, col);
    case ChannelAlarmOnOff:
        return getChAlarmOnOff(row, col);
    case ChannelAlarmType:
        return getChAlarmType(row, col);
    case ChannelAlarm1Type:
        return getChAlarm1Type(row, col);
    case ChannelAlarm1Status:
        return getChAlarm1Status(row, col);
    case ChannelAlarm1Value:
        return getChAlarm1Value(row, col);
    case ChannelAlarm1Color:
        return getChAlarm1Color(row, col);
    case ChannelAlarm2Type:
        return getChAlarm2Type(row, col);
    case ChannelAlarm2Status:
        return getChAlarm2Status(row, col);
    case ChannelAlarm2Value:
        return getChAlarm2Value(row, col);
    case ChannelAlarm2Color:
        return getChAlarm2Color(row, col);
    case ChannelAlarm3Type:
        return getChAlarm3Type(row, col);
    case ChannelAlarm3Status:
        return getChAlarm3Status(row, col);
    case ChannelAlarm3Value:
        return getChAlarm3Value(row, col);
    case ChannelAlarm3Color:
        return getChAlarm3Color(row, col);
    case ChannelAlarm4Type:
        return getChAlarm4Type(row, col);
    case ChannelAlarm4Status:
        return getChAlarm4Status(row, col);
    case ChannelAlarm4Value:
        return getChAlarm4Value(row, col);
    case ChannelAlarm4Color:
        return getChAlarm4Color(row, col);
    default:
        return QVariant();
    }
}

/*
 * 功能：
 *      根据当前对应组的配置信息，添加相应的通道编码号到m_list_channel
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ModelBarGroupChannel::init()
{
    m_list_channel.clear();

    if (m_grpIndex<GROUP_NUM_MAX && p_gDeviceCfg->displayGroup[m_grpIndex].groupSwitch) {
        m_grpValid = true;
        for (int i=0; i<p_gDeviceCfg->displayGroup[m_grpIndex].groupChannelNum && i<GROUP_CHANNEL_NUM_MAX; ++i){
            m_list_channel.append(p_gDeviceCfg->displayGroup[m_grpIndex].groupChannelItem[i]);
        }
    } else {
        m_grpValid = false;
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的测量数据
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道测量数据
 */
QVariant ModelBarGroupChannel::getChData(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;
    if (index<m_list_channel.size()){
        //quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelData(channelNumber);
        qsrand(QDateTime::currentDateTime().time().msec());
        qint32 rand = qrand()%20000  ;
        rand *= (rand%2?-1:1);
        return rand* 0.0001; //test
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道测量数据
 */
QVariant ModelBarGroupChannel::getChType(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CHANNEL_TYPE(channelNumber);           //通道类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的标记
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道测量数据
 */
QVariant ModelBarGroupChannel::getChTag(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelTag(channelNumber);           //通道标记
        return QString::number(index).rightJustified(4,'0');
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的颜色
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道测量数据
 */
QVariant ModelBarGroupChannel::getChColor(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelColor(channelNumber);           //通道颜色
        return QColor(255,97,0);
        //return QColor(255,0,0);
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的单位
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道测量单位
 */
QVariant ModelBarGroupChannel::getChUnit(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelUnit(channelNumber);           //通道单位
        return QString::fromUtf8("℃");
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警标记开关
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警标记开关
 */
QVariant ModelBarGroupChannel::getChAlarmOnOff(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarmOnOff(channelNumber);           //通道报警标记开关
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警标记类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警标记类型
 */
QVariant ModelBarGroupChannel::getChAlarmType(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarmType(channelNumber);           //通道报警标记类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警1类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警1类型
 */
QVariant ModelBarGroupChannel::getChAlarm1Type(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm1Type(channelNumber);           //通道报警1类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警1状态
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警1状态
 */
QVariant ModelBarGroupChannel::getChAlarm1Status(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm1Status(channelNumber);           //通道报警1状态
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警1报警值
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警1报警值
 */
QVariant ModelBarGroupChannel::getChAlarm1Value(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm1Value(channelNumber);           //通道报警1报警值
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警1颜色
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警1颜色
 */
QVariant ModelBarGroupChannel::getChAlarm1Color(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm1Color(channelNumber);           //通道报警1颜色
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警2类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警1类型
 */
QVariant ModelBarGroupChannel::getChAlarm2Type(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm2Type(channelNumber);           //通道报警1类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警2状态
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警2状态
 */
QVariant ModelBarGroupChannel::getChAlarm2Status(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm2Status(channelNumber);           //通道报警1状态
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警2报警值
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警2报警值
 */
QVariant ModelBarGroupChannel::getChAlarm2Value(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm2Value(channelNumber);           //通道报警1报警值
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警2颜色
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警2颜色
 */
QVariant ModelBarGroupChannel::getChAlarm2Color(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm2Color(channelNumber);           //通道报警1颜色
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警3类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警13类型
 */
QVariant ModelBarGroupChannel::getChAlarm3Type(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm3Type(channelNumber);           //通道报警3类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警3状态
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警3状态
 */
QVariant ModelBarGroupChannel::getChAlarm3Status(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm3Status(channelNumber);           //通道报警3状态
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警3报警值
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警3报警值
 */
QVariant ModelBarGroupChannel::getChAlarm3Value(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm3Value(channelNumber);           //通道报警3报警值
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警3颜色
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警3颜色
 */
QVariant ModelBarGroupChannel::getChAlarm3Color(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm3Color(channelNumber);           //通道报警3颜色
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警4类型
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警4类型
 */
QVariant ModelBarGroupChannel::getChAlarm4Type(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm4Type(channelNumber);           //通道报警4类型
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警4状态
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警4状态
 */
QVariant ModelBarGroupChannel::getChAlarm4Status(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm4Status(channelNumber);           //通道报警4状态
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警4报警值
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警4报警值
 */
QVariant ModelBarGroupChannel::getChAlarm4Value(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm4Value(channelNumber);           //通道报警4报警值
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的报警4颜色
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道报警4颜色
 */
QVariant ModelBarGroupChannel::getChAlarm4Color(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelAlarm4Color(channelNumber);           //通道报警4颜色
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的量程上限
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道量程上限
 */
QVariant ModelBarGroupChannel::getChRangeUpper(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelRangeUpper(channelNumber);           //量程上限
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的量程下限
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道量程下限
 */
QVariant ModelBarGroupChannel::getChRangeDowner(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelRangeDowner(channelNumber);           //量程下限
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的显示区域上限
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示区域上限
 */
QVariant ModelBarGroupChannel::getChDispUpper(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelDispUpper(channelNumber);           //显示区域上限
        return 2.0;
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的显示区域下限
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示区域下限
 */
QVariant ModelBarGroupChannel::getChDispDowner(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelDispDowner(channelNumber);           //显示区域下限
        return -2.0;
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的标尺位置
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示标尺位置
 */
QVariant ModelBarGroupChannel::getChScalePos(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelScalePos(channelNumber);           //显示标尺位置
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的标尺分割数
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示标尺标尺分割数
 */
QVariant ModelBarGroupChannel::getChScaleDiv(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        return CfgChannel::instance()->getChannelScaleDiv(channelNumber);           //显示标尺标尺分割数
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的棒图基准点
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示棒图基准点
 */
QVariant ModelBarGroupChannel::getChBarBase(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelBarBase(channelNumber);           //显示棒图基准点
        return 0;
    } else {
        return QVariant();
    }
}

/*
 * 功能：
 *      根据行、列号，获取对应通道的棒图标尺分割数
 * 参数：
 * 	  1.const int row：行号
 *       2.const int col：列号
 * 返回值：
 * 	  QVariant：通道显示棒图标尺分割数
 */
QVariant ModelBarGroupChannel::getChBarDiv(const int row, const int col) const
{
    int colcount = columnCount();
    int index = row*colcount + col;

    if (index<m_list_channel.size()){
        quint32 channelNumber = m_list_channel.at(index);
        //return CfgChannel::instance()->getChannelBarDiv(channelNumber);           //显示棒图标尺分割数
        return 10;
    } else {
        return QVariant();
    }
}

//QVariant ModelBarGroupChannel::getChPartScaleOnOff(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChPartScalePos(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChPartScaleBound(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChColorScalePos(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChColorScaleColor(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChColorScaleUpper(const int row, const int col) const
//{
//    return QVariant();
//}

//QVariant ModelBarGroupChannel::getChColorScaleDowner(const int row, const int col) const
//{
//    return QVariant();
//}

/*
 * 功能：
 *      组配置修改处理槽函数
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void ModelBarGroupChannel::slotGroupChannelChanged(quint8 grpIndex)
{
    if (grpIndex == m_grpIndex){
        beginResetModel();
        init();
        endResetModel();
    }
}
