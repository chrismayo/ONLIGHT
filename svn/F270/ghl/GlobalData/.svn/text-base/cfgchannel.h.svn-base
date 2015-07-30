/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：CfgChannel.h
 * 概   要：CfgChannel是有效通道配置类，根据LPSRAM系统配置的“系统状态”，添加
 * 有效的通道号至相应的通道号链表中, 并提供通道相应的访问函数
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-6-10
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#ifndef CFGCHANNEL_H
#define CFGCHANNEL_H

#include <QObject>
#include <QList>

/*通道号编码32bit（4-8-8-12）分别为：通道类型--单元号--卡槽号--通道号*/
#define CHANNEL_TYPE_BITOFF 28              //通道类型bit偏移
#define CHANNEL_UNIN_BITOFF 20             //单元号bit偏移
#define CHANNEL_MODULE_BITOFF 12       //卡槽号bit偏移
#define CHANNEL_NUM_BITOFF 0                //通道号bit偏移

#define CHANNEL_UNIN_MAIN   0   //本机
#define CHANNEL_UNIN_EXT1   1    //扩展单元1
#define CHANNEL_UNIN_EXT2   2    //扩展单元2
#define CHANNEL_UNIN_EXT3   3    //扩展单元3
#define CHANNEL_UNIN_EXT4   4    //扩展单元4
#define CHANNEL_UNIN_EXT5   5    //扩展单元5
#define CHANNEL_UNIN_EXT6   6    //扩展单元6


#define CHANNEL_TYPE(x) ((x)>>28 & 0x0F)    //从通道号编码中获取通道类型
#define CHANNEL_UNIT(x) ((x)>>20 & 0xFF)    //从通道号编码中获取单元号，0：本机，1-6:扩展单元
#define CHANNEL_MODULE(x) ((x)>>12 & 0xFF)   //从通道号编码中获取卡槽(模块)号，本机：0-9; 扩展单元：0-5
#define CHANNEL_NUM(x) ((x) & 0x3FF)             //从通道号编码中获取通道号

class CfgChannel : public QObject
{
    Q_OBJECT
public:
    static CfgChannel *instance();
    QVariant getChannelData(quint32 chanNum);
    QVariant getChannelTag(quint32 chanNum);
    QVariant getChannelColor(quint32 chanNum);
    QVariant getChannelUnit(quint32 chanNum);
    QVariant getChannelRangeUpper(quint32 chanNum);
    QVariant getChannelRangeDowner(quint32 chanNum);

    QVariant getChannelDispUpper(quint32 chanNum);
    QVariant getChannelDispDowner(quint32 chanNum);

    QVariant getChannelScalePos(quint32 chanNum);
    QVariant getChannelScaleDiv(quint32 chanNum);

    QVariant getChannelBarBase(quint32 chanNum);
    QVariant getChannelBarDiv(quint32 chanNum);

    QVariant getChannelPartScaleOnOff(quint32 chanNum);
    QVariant getChannelPartScalePos(quint32 chanNum);
    QVariant getChannelPartScaleBound(quint32 chanNum);

    QVariant getChannelColorScalePos(quint32 chanNum);
    QVariant getChannelColorScaleColor(quint32 chanNum);
    QVariant getChannelColorScaleUpper(quint32 chanNum);
    QVariant getChannelColorScaleDowner(quint32 chanNum);

    QVariant getChannelAlarmOnOff(quint32 chanNum);
    QVariant getChannelAlarmType(quint32 chanNum);
    QVariant getChannelAlarm1Type(quint32 chanNum);
    QVariant getChannelAlarm1Status(quint32 chanNum);
    QVariant getChannelAlarm1Value(quint32 chanNum);
    QVariant getChannelAlarm1Color(quint32 chanNum);
    QVariant getChannelAlarm2Type(quint32 chanNum);
    QVariant getChannelAlarm2Status(quint32 chanNum);
    QVariant getChannelAlarm2Value(quint32 chanNum);
    QVariant getChannelAlarm2Color(quint32 chanNum);
    QVariant getChannelAlarm3Type(quint32 chanNum);
    QVariant getChannelAlarm3Status(quint32 chanNum);
    QVariant getChannelAlarm3Value(quint32 chanNum);
    QVariant getChannelAlarm3Color(quint32 chanNum);
    QVariant getChannelAlarm4Type(quint32 chanNum);
    QVariant getChannelAlarm4Status(quint32 chanNum);
    QVariant getChannelAlarm4Value(quint32 chanNum);
    QVariant getChannelAlarm4Color(quint32 chanNum);

private:
    explicit CfgChannel(QObject *parent = 0);

signals:
    void sigBasicChannelChanged();  //基础通道变更信号

public slots:
    void slotBasicChannelChanged(); //基础通道变更处理槽函数

private:
    QList<quint32>  m_list_AI;      //有效AI通道通道号链表
    QList<quint32>  m_list_DI;      //有效DI通道通道号链表
    QList<quint32>  m_list_DO;    //有效DO通道通道号链表
};

#endif // CFGCHANNEL_H
