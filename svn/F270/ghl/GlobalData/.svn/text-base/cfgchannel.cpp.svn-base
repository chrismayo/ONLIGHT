/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：CfgChannel.cpp
 * 概   要：CfgChannel是有效通道配置类，根据LPSRAM系统配置的“系统状态”，添加
 * 有效的通道号至相应的通道号链表中, 并提供通道相应的访问函数
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-6-29
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "cfgchannel.h"
#include "./GlobalData/cfgGlobalDef.h"
#include "./GlobalData/dataGlobalDef_ModbusReg.h"

#include <QSharedMemory>
#include <QVariant>
#include <QColor>

extern DEVICE_CONFIG                   *p_gDeviceCfg;        //全局变量指针，指向LPSRAM中的设备配置结构
extern QSharedMemory   g_sharedDataTable;


CfgChannel * CfgChannel::instance()
{
        static CfgChannel data;
        return &data;
}

CfgChannel::CfgChannel(QObject *parent) :
    QObject(parent)
{
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的测量数据
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道数据
 */
QVariant CfgChannel::getChannelData(quint32 chanNum)
{
    MODBUS_REGISTER_MAP *pModbusRegMap;
    float * pData;
    quint8 *pDataDIO;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    g_sharedDataTable.lock();
    pModbusRegMap = const_cast<MODBUS_REGISTER_MAP*>(static_cast<MODBUS_REGISTER_MAP const *>(g_sharedDataTable.constData()));

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
        g_sharedDataTable.unlock();
        return *pData;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pData = (float *)&pModbusRegMap->inputReg_MainUnit_IO_Data_Float32[moduleIndex*UNIT_CHAN_NUM_PRE + number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }
        g_sharedDataTable.unlock();
        return *pData;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDataDIO = &pModbusRegMap->relay_MainUnit_IO_Data_Bit[moduleIndex*UNIT_CHAN_NUM_PRE + number];
        } else {    //DO不支持扩展单元
            goto ERR;
        }
        g_sharedDataTable.unlock();
        return *pDataDIO;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;

        pData = (float *)&pModbusRegMap->inputReg_MainUnit_Math_Data_Float32[number<<1];
        g_sharedDataTable.unlock();
        return *pData;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;

        pData = (float *)&pModbusRegMap->holdReg_MainUnit_Comm_Data_Float32[number<<1];
        g_sharedDataTable.unlock();
        return *pData;
    default:
        goto ERR;
    }

ERR:
    g_sharedDataTable.unlock();
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的通道标记
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道标记
 */
QVariant CfgChannel::getChannelTag(quint32 chanNum)
{
    QString channelTag;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                if (p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagChar[0] == '\n' ||
                    p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagNo[0] == '\n') {
                    channelTag =  QString("0")+QString::number(moduleIndex*100+number);
                } else if(p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagNo[0] != '\n'){
                    channelTag =  QString((const char *)p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagNo) +\
                            QString((const char *)p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagChar);
                } else {
                    channelTag =  QString((const char *)p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayTagChar);
                }
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagChar[0] == '\n' ||
                p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagNo[0] == '\n' ) {
                channelTag =  QString::number(uninNum*1000 + moduleIndex*100+number);
            } else if(p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagNo[0] != '\n'){
                channelTag =  QString((const char *)p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagNo) +\
                        QString((const char *)p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagChar);
            } else {
                channelTag = QString((const char *)p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayTagChar);
            }
        } else {
            goto ERR;
        }
        return channelTag;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            if (p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagChar[0] == '\n' ||
                p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagNo[0] == '\n') {
                channelTag =  QString("0")+QString::number(moduleIndex*100+number);
            } else if (p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagNo[0] != '\n') {
                channelTag = QString((const char *)p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagNo) +\
                        QString((const char *)p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagChar);
            } else {
                channelTag = QString((const char *)p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayTagChar);
            }
        } else {    //DI不支持扩展单元
            goto ERR;
        }
        return channelTag;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            if (p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagChar[0] == '\n' ||
                p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagNo[0] == '\n') {
                channelTag =  QString("0")+QString::number(moduleIndex*100+number);
            } else if (p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagNo[0] != '\n') {
                channelTag = QString((const char *)p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagNo) +\
                        QString((const char *)p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagChar);
            } else {
                channelTag = QString((const char *)p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayTagChar);
            }
        } else {    //DO不支持扩展单元
            goto ERR;
        }
        return channelTag;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;

        if (p_gDeviceCfg->chanMath[number].displayConfig.displayTagChar[0] == '\n' ||
            p_gDeviceCfg->chanMath[number].displayConfig.displayTagNo[0] == '\n') {
            channelTag = QString::number(1000+number);
            channelTag.replace(0,1,QString("A"));
        } else if (p_gDeviceCfg->chanMath[number].displayConfig.displayTagNo[0] != '\n') {
            channelTag = QString((const char *)p_gDeviceCfg->chanMath[number].displayConfig.displayTagNo) +\
                    QString((const char *)p_gDeviceCfg->chanMath[number].displayConfig.displayTagChar);
        } else {
            channelTag = QString((const char *)p_gDeviceCfg->chanMath[number].displayConfig.displayTagChar);
        }
        return channelTag;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;

        if (p_gDeviceCfg->chanComm[number].displayConfig.displayTagChar[0] == '\n' ||
            p_gDeviceCfg->chanComm[number].displayConfig.displayTagNo[0] == '\n') {
            channelTag = QString::number(1000+number);
            channelTag.replace(0,1,QString("C"));
        } else if (p_gDeviceCfg->chanComm[number].displayConfig.displayTagNo[0] != '\n') {
            channelTag = QString((const char *)p_gDeviceCfg->chanComm[number].displayConfig.displayTagNo) +\
                    QString((const char *)p_gDeviceCfg->chanComm[number].displayConfig.displayTagChar);
        } else {
            channelTag = QString((const char *)p_gDeviceCfg->chanComm[number].displayConfig.displayTagChar);
        }
        return channelTag;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的通道颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道颜色
 */
QVariant CfgChannel::getChannelColor(quint32 chanNum)
{
    quint32 color;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                color = p_gDeviceCfg->mainUnitAI[moduleIndex][number].displayConfig.displayColor;
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            color = p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].displayConfig.displayColor;
        } else {
            goto ERR;
        }
        return color;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            color = p_gDeviceCfg->mainUnitDI[moduleIndex][number].displayConfig.displayColor;
        } else {    //DI不支持扩展单元
            goto ERR;
        }
        return color;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            color = p_gDeviceCfg->mainUnitDO[moduleIndex][number].displayConfig.displayColor;
        } else {    //DO不支持扩展单元
            goto ERR;
        }
        return color;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;

        color = p_gDeviceCfg->chanMath[number].displayConfig.displayColor;
        return color;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;

        color = p_gDeviceCfg->chanComm[number].displayConfig.displayColor;
        return color;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的通道单位
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道单位
 */
QVariant CfgChannel::getChannelUnit(quint32 chanNum)
{
    QString channelUnit;
    AI_CONFIG_RANGE *pConfigRange;
    DI_CONFIG_RANGE *pDIConfigRange;
    DO_CONFIG_RANGE *pDOConfigRange;
    MATH_CONFIG_EXP *pMathConfigRange;
    COMM_CONFIG_RANGE *pCommConfigRange;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->mainUnitAI[moduleIndex][number].rangeConfig;
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].rangeConfig;
            }
        } else {
            goto ERR;
        }

        if (pConfigRange->rangeType == AI_RANGE_Type_Disabled) {
            return QString();
        } else if (pConfigRange->rangeCalculateType == AI_Range_Calculate_Linear ||
             pConfigRange->rangeCalculateType == AI_Range_Calculate_Sqrt) {
            channelUnit = QString((char *)pConfigRange->rangeScale.scaleUnit);
        } else {
            switch (pConfigRange->rangeType) {
            case AI_RANGE_Type_Vlot:
                if(pConfigRange->config.rangeVolt<=AI_Range_Volt_200mV)
                    channelUnit = QString("mV");
                else
                    channelUnit =  QString("V");
                break;
            case AI_RANGE_Type_GS:
                channelUnit =  QString("V");
                break;
            case AI_RANGE_Type_TC:
                if (pConfigRange->config.rangeTC == AI_Range_TC_KpvsAu7Fe)
                    channelUnit =  QString("K");
                else
                    channelUnit = QString("°C");
                break;
            case AI_RANGE_Type_RTD:
                if (pConfigRange->config.rangeRTD == AI_Range_RTD_J263B)
                    channelUnit = QString("K");
                else
                    channelUnit = QString("°C");
                break;
            case AI_RANGE_Type_DI:
                channelUnit =  QString();
                break;
            case AI_RANGE_Type_Cur0_20mA:
            case AI_RANGE_Type_GS4_20mA:
                channelUnit = QString("mA");
                break;
            default:
                break;
            }
        }

        return channelUnit;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfigRange = &p_gDeviceCfg->mainUnitDI[moduleIndex][number].rangeConfig;
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfigRange->type == DI_Range_Type_Disabled) {
            channelUnit = QString();
        } else if (pDIConfigRange->calculateType == DI_Range_Calculate_Linear) {
            channelUnit = QString((char *)pDIConfigRange->scale.scaleUnit);
        } else {
            channelUnit = QString();
        }
        return channelUnit;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfigRange = &p_gDeviceCfg->mainUnitDO[moduleIndex][number].rangeConfig;
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        channelUnit = QString((char *)pDOConfigRange->rangeUnit);
        return channelUnit;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfigRange = &p_gDeviceCfg->chanMath[number].expressConfig;

        channelUnit = QString((char *)pMathConfigRange->expUnit);
        return channelUnit;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfigRange =&p_gDeviceCfg->chanComm[number].rangeConfig;

        channelUnit = QString((char *)pCommConfigRange->rangeUnit);
        return channelUnit;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  基础通道变更处理函数----板卡热插拔功能支持
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的量程上限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道量程上限，qreal
 */
QVariant CfgChannel::getChannelRangeUpper(quint32 chanNum)
{
    qreal channelRangeUpper;
    qint32 channelDIORagneUpper;
    AI_CONFIG_RANGE *pConfigRange;
    DI_CONFIG_RANGE *pDIConfigRange;
    DO_CONFIG_RANGE *pDOConfigRange;
    MATH_CONFIG_EXP *pMathConfigRange;
    COMM_CONFIG_RANGE *pCommConfigRange;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->mainUnitAI[moduleIndex][number].rangeConfig;
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].rangeConfig;
            }
        } else {
            goto ERR;
        }

        if (pConfigRange->rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else if (pConfigRange->rangeCalculateType == AI_Range_Calculate_Linear ||
             pConfigRange->rangeCalculateType == AI_Range_Calculate_Sqrt) {
            channelRangeUpper = (qreal)pConfigRange->rangeScale.scaleMax/::pow10(pConfigRange->rangeScale.scalePosition);
        } else {
            channelRangeUpper = (qreal)pConfigRange->rangeMax;
        }
        return channelRangeUpper;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfigRange = &p_gDeviceCfg->mainUnitDI[moduleIndex][number].rangeConfig;
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfigRange->type == DI_Range_Type_Disabled) {
            goto ERR;
        } else if (pDIConfigRange->calculateType == DI_Range_Calculate_Linear) {
            channelDIORagneUpper = pDIConfigRange->scale.scaleMax/::pow10(pDIConfigRange->scale.scalePosition);
        } else {
            channelDIORagneUpper = pDIConfigRange->rangeMax;
        }
        return channelDIORagneUpper;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfigRange = &p_gDeviceCfg->mainUnitDO[moduleIndex][number].rangeConfig;
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        channelDIORagneUpper = pDOConfigRange->rangeMax;
        return channelDIORagneUpper;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfigRange = &p_gDeviceCfg->chanMath[number].expressConfig;

        if (pMathConfigRange->expSwtich == 0) {
            goto ERR;
        } else {
            channelRangeUpper = (qreal)pMathConfigRange->expMax/::pow10(pMathConfigRange->expPos);
        }
        return channelRangeUpper;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfigRange = &p_gDeviceCfg->chanComm[number].rangeConfig;

        if (pCommConfigRange->rangeSwtich == 0) {
            goto ERR;
        } else {
            channelRangeUpper = (qreal)pCommConfigRange->rangeMax/::pow10(pCommConfigRange->rangePos);
        }
        return channelRangeUpper;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的量程下限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道量程下限
 */
QVariant CfgChannel::getChannelRangeDowner(quint32 chanNum)
{
    qreal channelRangeUpper;
    qint32 channelDIORagneUpper;
    AI_CONFIG_RANGE *pConfigRange;
    DI_CONFIG_RANGE *pDIConfigRange;
    DO_CONFIG_RANGE *pDOConfigRange;
    MATH_CONFIG_EXP *pMathConfigRange;
    COMM_CONFIG_RANGE *pCommConfigRange;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->mainUnitAI[moduleIndex][number].rangeConfig;
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pConfigRange = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number].rangeConfig;
            }
        } else {
            goto ERR;
        }

        if (pConfigRange->rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else if (pConfigRange->rangeCalculateType == AI_Range_Calculate_Linear ||
             pConfigRange->rangeCalculateType == AI_Range_Calculate_Sqrt) {
            channelRangeUpper = (qreal)pConfigRange->rangeScale.scaleMin/::pow10(pConfigRange->rangeScale.scalePosition);
        } else {
            channelRangeUpper = (qreal)pConfigRange->rangeMin;
        }
        return channelRangeUpper;
    case Channel_Type_DI:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfigRange = &p_gDeviceCfg->mainUnitDI[moduleIndex][number].rangeConfig;
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfigRange->type == DI_Range_Type_Disabled) {
            goto ERR;
        } else if (pDIConfigRange->calculateType == DI_Range_Calculate_Linear) {
            channelDIORagneUpper = pDIConfigRange->scale.scaleMin/::pow10(pDIConfigRange->scale.scalePosition);
        } else {
            channelDIORagneUpper = pDIConfigRange->rangeMin;
        }
        return channelDIORagneUpper;
    case Channel_Type_DO:
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfigRange = &p_gDeviceCfg->mainUnitDO[moduleIndex][number].rangeConfig;
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        channelDIORagneUpper = pDOConfigRange->rangeMin;
        return channelDIORagneUpper;
    case Channel_Type_Math:
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfigRange = &p_gDeviceCfg->chanMath[number].expressConfig;

        if (pMathConfigRange->expSwtich == 0) {
            goto ERR;
        } else {
            channelRangeUpper = (qreal)pMathConfigRange->expMin/::pow10(pMathConfigRange->expPos);
        }
        return channelRangeUpper;
    case Channel_Type_Comm:
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfigRange = &p_gDeviceCfg->chanComm[number].rangeConfig;

        if (pCommConfigRange->rangeSwtich == 0) {
            goto ERR;
        } else {
            channelRangeUpper = (qreal)pCommConfigRange->rangeMin/::pow10(pCommConfigRange->rangePos);
        }
        return channelRangeUpper;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的显示区域上限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道显示区域上限
 */
QVariant CfgChannel::getChannelDispUpper(quint32 chanNum)
{
    quint8 dispZone;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    DO_CONFIG *pDOConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            dispZone = pAIConfig->displayConfig.displayZoneUpper;
        return dispZone;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispZone = pDIConfig->displayConfig.displayZoneUpper;
        }
        return dispZone;
    case Channel_Type_DO:   //DO类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfig = &p_gDeviceCfg->mainUnitDO[moduleIndex][number];
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        dispZone = pDOConfig->displayConfig.displayZoneUpper;
        return dispZone;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispZone = pMathConfig->displayConfig.displayZoneUpper;
        }
        return dispZone;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispZone = pCommConfig->displayConfig.displayZoneUpper;
        }
        return dispZone;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的显示区域下限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道显示区域下限
 */
QVariant CfgChannel::getChannelDispDowner(quint32 chanNum)
{
    quint8 dispZone;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    DO_CONFIG *pDOConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            dispZone = pAIConfig->displayConfig.dispalyZoneLower;
        }
        return dispZone;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispZone = pDIConfig->displayConfig.dispalyZoneLower;
        }
        return dispZone;
    case Channel_Type_DO:   //DO类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfig = &p_gDeviceCfg->mainUnitDO[moduleIndex][number];
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        dispZone = pDOConfig->displayConfig.dispalyZoneLower;
        return dispZone;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispZone = pMathConfig->displayConfig.dispalyZoneLower;
        }
        return dispZone;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispZone = pCommConfig->displayConfig.dispalyZoneLower;
        }
        return dispZone;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的标尺位置
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道标尺位置
 */
QVariant CfgChannel::getChannelScalePos(quint32 chanNum)
{
    quint8 dispScalePos;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    DO_CONFIG *pDOConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            dispScalePos = pAIConfig->displayConfig.displayScalePos;
        }
        return dispScalePos;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispScalePos = pDIConfig->displayConfig.displayScalePos;
        }
        return dispScalePos;
    case Channel_Type_DO:   //DO类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfig = &p_gDeviceCfg->mainUnitDO[moduleIndex][number];
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        dispScalePos = pDOConfig->displayConfig.displayScalePos;
        return dispScalePos;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispScalePos = pMathConfig->displayConfig.displayScalePos;
        }
        return dispScalePos;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispScalePos = pCommConfig->displayConfig.displayScalePos;
        }
        return dispScalePos;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的标尺分割数
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的标尺分割数
 */
QVariant CfgChannel::getChannelScaleDiv(quint32 chanNum)
{
    quint8 dispScaleDiv;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            dispScaleDiv = pAIConfig->displayConfig.displayScaleDiv;
        }
        return dispScaleDiv;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispScaleDiv = pDIConfig->displayConfig.displayScaleDiv;
        }
        return dispScaleDiv;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispScaleDiv = pMathConfig->displayConfig.displayScaleDiv;
        }
        return dispScaleDiv;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispScaleDiv = pCommConfig->displayConfig.displayScaleDiv;
        }
        return dispScaleDiv;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的棒图基准位置
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的棒图基准位置
 */
QVariant CfgChannel::getChannelBarBase(quint32 chanNum)
{
    quint8 dispBarPos;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    DO_CONFIG *pDOConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            dispBarPos = pAIConfig->displayConfig.displayBarPos;
        }
        return dispBarPos;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispBarPos = pDIConfig->displayConfig.displayBarPos;
        }
        return dispBarPos;
    case Channel_Type_DO:   //DO类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DO通道
            pDOConfig = &p_gDeviceCfg->mainUnitDO[moduleIndex][number];
        } else {    //DO不支持扩展单元
            goto ERR;
        }

        dispBarPos = pDOConfig->displayConfig.displayBarPos;
        return dispBarPos;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispBarPos = pMathConfig->displayConfig.displayBarPos;
        }
        return dispBarPos;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispBarPos = pCommConfig->displayConfig.displayBarPos;
        }
        return dispBarPos;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的棒图分割数
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的棒图分割数
 */
QVariant CfgChannel::getChannelBarDiv(quint32 chanNum)
{
    quint8 dispBarDiv;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            dispBarDiv = pAIConfig->displayConfig.displayBarDiv;
        }
        return dispBarDiv;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            dispBarDiv = pDIConfig->displayConfig.displayBarDiv;
        }
        return dispBarDiv;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            dispBarDiv = pMathConfig->displayConfig.displayBarDiv;
        }
        return dispBarDiv;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            dispBarDiv = pCommConfig->displayConfig.displayBarDiv;
        }
        return dispBarDiv;
    default:
        break;
    }

ERR:
    return QVariant();
}


/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的部分压缩放大开关
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的部分压缩放大开关
 */
QVariant CfgChannel::getChannelPartScaleOnOff(quint32 chanNum)
{
    bool partScaleOnOff;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            partScaleOnOff = pAIConfig->displayConfig.displayPartialOnOff;
        }
        return partScaleOnOff;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            partScaleOnOff = pMathConfig->displayConfig.displayPartialOnOff;
        }
        return partScaleOnOff;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            partScaleOnOff = pCommConfig->displayConfig.displayPartialOnOff;
        }
        return partScaleOnOff;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的部分压缩放大位置
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的部分压缩放大位置
 */
QVariant CfgChannel::getChannelPartScalePos(quint32 chanNum)
{
    quint8 partScalePos;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            partScalePos = pAIConfig->displayConfig.displayPartialPos;
        }
        return partScalePos;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            partScalePos = pMathConfig->displayConfig.displayPartialPos;
        }
        return partScalePos;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            partScalePos = pCommConfig->displayConfig.displayPartialPos;
        }
        return partScalePos;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的部分压缩放大边界值
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的部分压缩放大边界值
 */
QVariant CfgChannel::getChannelPartScaleBound(quint32 chanNum)
{
    quint8 partScaleBound;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            partScaleBound = pAIConfig->displayConfig.displayPartialBoundary;
        }
        return partScaleBound;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            partScaleBound = pMathConfig->displayConfig.displayPartialBoundary;
        }
        return partScaleBound;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            partScaleBound = pCommConfig->displayConfig.displayPartialBoundary;
        }
        return partScaleBound;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的彩色标尺带显示位置
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的彩色标尺带显示位置
 */
QVariant CfgChannel::getChannelColorScalePos(quint32 chanNum)
{
    quint8 colorBandPos;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            colorBandPos = pAIConfig->displayConfig.displayColorbandMode;
        }
        return colorBandPos;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            colorBandPos = pMathConfig->displayConfig.displayColorbandMode;
        }
        return colorBandPos;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            colorBandPos = pCommConfig->displayConfig.displayColorbandMode;
        }
        return colorBandPos;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的彩色标尺带显示颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的彩色标尺带显示颜色
 */
QVariant CfgChannel::getChannelColorScaleColor(quint32 chanNum)
{
    quint32 colorBandColor;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            colorBandColor = pAIConfig->displayConfig.displayColorbandColor;
        }
        return colorBandColor;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            colorBandColor = pMathConfig->displayConfig.displayColorbandColor;
        }
        return colorBandColor;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            colorBandColor = pCommConfig->displayConfig.displayColorbandColor;
        }
        return colorBandColor;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的彩色标尺带显示位置上限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的彩色标尺带显示位置上限
 */
QVariant CfgChannel::getChannelColorScaleUpper(quint32 chanNum)
{
    qreal colorBandUpper;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            colorBandUpper = pAIConfig->displayConfig.displayColorbandPosUpper;
        }
        return colorBandUpper;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            colorBandUpper = pMathConfig->displayConfig.displayColorbandPosUpper;
        }
        return colorBandUpper;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            colorBandUpper = pCommConfig->displayConfig.displayColorbandPosUpper;
        }
        return colorBandUpper;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的彩色标尺带显示位置下限
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的彩色标尺带显示位置下限
 */
QVariant CfgChannel::getChannelColorScaleDowner(quint32 chanNum)
{
    qreal colorBandUpper;
    AI_CONFIG *pAIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            colorBandUpper = pAIConfig->displayConfig.displayColorbandPosLower;
        }
        return colorBandUpper;
    case Channel_Type_DI:   //DI类型通道
        goto ERR;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            colorBandUpper = pMathConfig->displayConfig.displayColorbandPosLower;
        }
        return colorBandUpper;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            colorBandUpper = pCommConfig->displayConfig.displayColorbandPosLower;
        }
        return colorBandUpper;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警点标记开关
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点标记开关， bool
 */
QVariant CfgChannel::getChannelAlarmOnOff(quint32 chanNum)
{
    bool alarmOnOff;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmOnOff = pAIConfig->displayConfig.displayAlarmMarkOnOff;
        return alarmOnOff;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmOnOff = pDIConfig->displayConfig.displayAlarmMarkOnOff;
        }
        return alarmOnOff;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmOnOff = pMathConfig->displayConfig.displayAlarmMarkOnOff;
        }
        return alarmOnOff;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmOnOff = pCommConfig->displayConfig.displayAlarmMarkOnOff;
        }
        return alarmOnOff;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警点标记类型
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点标记类型，uint
 */
QVariant CfgChannel::getChannelAlarmType(quint32 chanNum)
{
    quint8 alarmType;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmType = pAIConfig->displayConfig.displayAlarmMarkType;
        return alarmType;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pDIConfig->displayConfig.displayAlarmMarkType;
        }
        return alarmType;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pMathConfig->displayConfig.displayAlarmMarkType;
        }
        return alarmType;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pCommConfig->displayConfig.displayAlarmMarkType;
        }
        return alarmType;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警1类型
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警1类型，uint
 */
QVariant CfgChannel::getChannelAlarm1Type(quint32 chanNum)
{
    quint8 alarmType;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pAIConfig->alarmConfig.alarmType[0];
        }
        return alarmType;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pDIConfig->alarmConfig.alarmType[0];
        }
        return alarmType;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pMathConfig->alarmConfig.alarmType[0];
        }
        return alarmType;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pCommConfig->alarmConfig.alarmType[0];
        }
        return alarmType;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警1状态
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警1状态
 */
QVariant CfgChannel::getChannelAlarm1Status(quint32 chanNum)
{

}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警1报警值
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警1报警值
 */
QVariant CfgChannel::getChannelAlarm1Value(quint32 chanNum)
{
    qreal alarmValue;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pAIConfig->alarmConfig.alarmValue[0];
        }
        return alarmValue;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pDIConfig->alarmConfig.alarmValue[0];
        }
        return alarmValue;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pMathConfig->alarmConfig.alarmValue[0];
        }
        return alarmValue;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pCommConfig->alarmConfig.alarmValue[0];
        }
        return alarmValue;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警2颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警2颜色
 */
QVariant CfgChannel::getChannelAlarm1Color(quint32 chanNum)
{
    quint32 alarmColor;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmColor = pAIConfig->displayConfig.displayAlarmMarkColor[0];
        return alarmColor;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmColor = pDIConfig->displayConfig.displayAlarmMarkColor[0];
        }
        return alarmColor;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pMathConfig->displayConfig.displayAlarmMarkColor[0];
        }
        return alarmColor;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pCommConfig->displayConfig.displayAlarmMarkColor[0];
        }
        return alarmColor;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警2类型
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警2类型，uint
 */
QVariant CfgChannel::getChannelAlarm2Type(quint32 chanNum)
{
    quint8 alarmType;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pAIConfig->alarmConfig.alarmType[1];
        }
        return alarmType;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pDIConfig->alarmConfig.alarmType[1];
        }
        return alarmType;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pMathConfig->alarmConfig.alarmType[1];
        }
        return alarmType;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pCommConfig->alarmConfig.alarmType[1];
        }
        return alarmType;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警2状态
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警2状态
 */
QVariant CfgChannel::getChannelAlarm2Status(quint32 chanNum)
{

}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警2报警值
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警2报警值
 */
QVariant CfgChannel::getChannelAlarm2Value(quint32 chanNum)
{
    qreal alarmValue;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pAIConfig->alarmConfig.alarmValue[1];
        }
        return alarmValue;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pDIConfig->alarmConfig.alarmValue[1];
        }
        return alarmValue;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pMathConfig->alarmConfig.alarmValue[1];
        }
        return alarmValue;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pCommConfig->alarmConfig.alarmValue[1];
        }
        return alarmValue;
    default:
        break;
    }

ERR:
    return QVariant();
}
/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警2颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警2颜色
 */
QVariant CfgChannel::getChannelAlarm2Color(quint32 chanNum)
{
    quint32 alarmColor;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmColor = pAIConfig->displayConfig.displayAlarmMarkColor[1];
        return alarmColor;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmColor = pDIConfig->displayConfig.displayAlarmMarkColor[1];
        }
        return alarmColor;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pMathConfig->displayConfig.displayAlarmMarkColor[1];
        }
        return alarmColor;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pCommConfig->displayConfig.displayAlarmMarkColor[1];
        }
        return alarmColor;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警3类型
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警3类型，uint
 */
QVariant CfgChannel::getChannelAlarm3Type(quint32 chanNum)
{
    quint8 alarmType;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pAIConfig->alarmConfig.alarmType[2];
        }
        return alarmType;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pDIConfig->alarmConfig.alarmType[2];
        }
        return alarmType;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pMathConfig->alarmConfig.alarmType[2];
        }
        return alarmType;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pCommConfig->alarmConfig.alarmType[2];
        }
        return alarmType;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警3状态
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警3状态
 */
QVariant CfgChannel::getChannelAlarm3Status(quint32 chanNum)
{

}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警3报警值
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警3报警值
 */
QVariant CfgChannel::getChannelAlarm3Value(quint32 chanNum)
{
    qreal alarmValue;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pAIConfig->alarmConfig.alarmValue[2];
        }
        return alarmValue;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pDIConfig->alarmConfig.alarmValue[2];
        }
        return alarmValue;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pMathConfig->alarmConfig.alarmValue[2];
        }
        return alarmValue;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pCommConfig->alarmConfig.alarmValue[2];
        }
        return alarmValue;
    default:
        break;
    }

ERR:
    return QVariant();
}
/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警3颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警3颜色
 */
QVariant CfgChannel::getChannelAlarm3Color(quint32 chanNum)
{
    quint32 alarmColor;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmColor = pAIConfig->displayConfig.displayAlarmMarkColor[2];
        return alarmColor;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmColor = pDIConfig->displayConfig.displayAlarmMarkColor[2];
        }
        return alarmColor;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pMathConfig->displayConfig.displayAlarmMarkColor[2];
        }
        return alarmColor;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pCommConfig->displayConfig.displayAlarmMarkColor[2];
        }
        return alarmColor;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警4类型
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警4类型，uint
 */
QVariant CfgChannel::getChannelAlarm4Type(quint32 chanNum)
{
    quint8 alarmType;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pAIConfig->alarmConfig.alarmType[3];
        }
        return alarmType;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmType = pDIConfig->alarmConfig.alarmType[3];
        }
        return alarmType;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pMathConfig->alarmConfig.alarmType[3];
        }
        return alarmType;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmType = pCommConfig->alarmConfig.alarmType[3];
        }
        return alarmType;
    default:
        break;
    }

ERR:
    return QVariant();
}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警4状态
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警4状态
 */
QVariant CfgChannel::getChannelAlarm4Status(quint32 chanNum)
{

}

/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警4报警值
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警4报警值
 */
QVariant CfgChannel::getChannelAlarm4Value(quint32 chanNum)
{
    qreal alarmValue;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pAIConfig->alarmConfig.alarmValue[3];
        }
        return alarmValue;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmValue = pDIConfig->alarmConfig.alarmValue[3];
        }
        return alarmValue;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pMathConfig->alarmConfig.alarmValue[3];
        }
        return alarmValue;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmValue = pCommConfig->alarmConfig.alarmValue[3];
        }
        return alarmValue;
    default:
        break;
    }

ERR:
    return QVariant();
}
/*
 * 功能：
 * 	  根据通道号，查询并返回对应通道的报警4颜色
 * 参数：
 * 	  1.quint32 chanNum: 通道号编码
 * 返回值：
 * 	  QVariant：通道的报警点报警4颜色
 */
QVariant CfgChannel::getChannelAlarm4Color(quint32 chanNum)
{
    quint32 alarmColor;
    AI_CONFIG *pAIConfig;
    DI_CONFIG *pDIConfig;
    MATH_CONFIG *pMathConfig;
    COMM_CONFIG *pCommConfig;
    quint16 chanType, uninNum, moduleIndex, number;
    chanType = CHANNEL_TYPE(chanNum);           //通道类型
    uninNum = CHANNEL_UNIT(chanNum);           //单元号
    moduleIndex = CHANNEL_MODULE(chanNum);  //卡槽号
    number = CHANNEL_NUM(chanNum);              //通道号

    switch(chanType){
    case Channel_Type_AI:   //AI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机AI通道
            if(moduleIndex>=MAIN_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->mainUnitAI[moduleIndex][number];
            }
        } else if (uninNum<=CHANNEL_UNIN_EXT6) { //扩展AI通道
            if (moduleIndex>=EXT_UNIT_MODULE_NUM || number>=UNIT_CHAN_NUM_PRE){
                goto ERR;
            } else {
                pAIConfig = &p_gDeviceCfg->extUnitAI[uninNum][moduleIndex][number];
            }
        } else {
            goto ERR;
        }

        if (pAIConfig->rangeConfig.rangeType == AI_RANGE_Type_Disabled)
            goto ERR;
        else
            alarmColor = pAIConfig->displayConfig.displayAlarmMarkColor[3];
        return alarmColor;
    case Channel_Type_DI:   //DI类型通道
        if (uninNum == CHANNEL_UNIN_MAIN) { //本机DI通道
            pDIConfig = &p_gDeviceCfg->mainUnitDI[moduleIndex][number];
        } else {    //DI不支持扩展单元
            goto ERR;
        }

        if (pDIConfig->rangeConfig.type == DI_Range_Type_Disabled) {
            goto ERR;
        } else {
            alarmColor = pDIConfig->displayConfig.displayAlarmMarkColor[3];
        }
        return alarmColor;
    case Channel_Type_DO:   //DO类型通道
        goto ERR;
    case Channel_Type_Math: //运算类型通道
        if (number>MAIN_UNIT_MATH_CHAN_NUM_PRE)
            goto ERR;
        else
            pMathConfig = &p_gDeviceCfg->chanMath[number];

        if (pMathConfig->expressConfig.expSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pMathConfig->displayConfig.displayAlarmMarkColor[3];
        }
        return alarmColor;
    case Channel_Type_Comm: //通信类型通道
        if (number>MAIN_UNIT_COMM_CHAN_NUM_USE)
            goto ERR;
        else
            pCommConfig = &p_gDeviceCfg->chanComm[number];

        if (pCommConfig->rangeConfig.rangeSwtich == 0) {
            goto ERR;
        } else {
            alarmColor = pCommConfig->displayConfig.displayAlarmMarkColor[3];
        }
        return alarmColor;
    default:
        break;
    }

ERR:
    return QVariant();
}

void CfgChannel::slotBasicChannelChanged()
{
    bool extValidFlag = false;

    m_list_AI.clear();
    m_list_DI.clear();
    m_list_DO.clear();

    //本机基础通道添加
    for (int i=0; i<MAIN_UNIT_MODULE_NUM; ++i){
        quint16 boardStatus = p_gDeviceCfg->sysStatus.mainUnit_ModuleStatus[i];
        if (STATUS_BOARD_STATUS(boardStatus)) {
            switch (STATUS_BOARD_TYPE(boardStatus)) {
            case STATUS_BOARD_TYPE_AI:
                for (int j=0; j<STATUS_BOARD_CHAN0_NUM(boardStatus); ++j){
                    quint32 channelNum = Channel_Type_AI<<CHANNEL_TYPE_BITOFF;
                    channelNum |= CHANNEL_UNIN_MAIN<<CHANNEL_UNIN_BITOFF;
                    channelNum |= i<<CHANNEL_MODULE_BITOFF;
                    channelNum |= j+1;
                    m_list_AI.append(channelNum);
                }
                break;
            case STATUS_BOARD_TYPE_DI:
                for (int j=0; j<STATUS_BOARD_CHAN0_NUM(boardStatus); ++j){
                    quint32 channelNum = Channel_Type_DI<<CHANNEL_TYPE_BITOFF;
                    channelNum |= CHANNEL_UNIN_MAIN<<CHANNEL_UNIN_BITOFF;
                    channelNum |= i<<CHANNEL_MODULE_BITOFF;
                    channelNum |= j+1;
                    m_list_DI.append(channelNum);
                }
                break;
            case STATUS_BOARD_TYPE_DO:
                for (int j=0; j<STATUS_BOARD_CHAN0_NUM(boardStatus); ++j){
                    quint32 channelNum = Channel_Type_DO<<CHANNEL_TYPE_BITOFF;
                    channelNum |= CHANNEL_UNIN_MAIN<<CHANNEL_UNIN_BITOFF;
                    channelNum |= i<<CHANNEL_MODULE_BITOFF;
                    channelNum |= j+1;
                    m_list_DO.append(channelNum);
                }
                break;
            case STATUS_BOARD_TYPE_DIO:
                for (int j=0; j<STATUS_BOARD_CHAN0_NUM(boardStatus); ++j){
                    quint32 channelNum = Channel_Type_DI<<CHANNEL_TYPE_BITOFF;
                    channelNum |= CHANNEL_UNIN_MAIN<<CHANNEL_UNIN_BITOFF;
                    channelNum |= i<<CHANNEL_MODULE_BITOFF;
                    channelNum |= j+1;
                    m_list_DI.append(channelNum);
                }
                for (int k=0; k<STATUS_BOARD_CHAN1_NUM(boardStatus); ++k){
                    quint32 channelNum = Channel_Type_DO<<CHANNEL_TYPE_BITOFF;
                    channelNum |= CHANNEL_UNIN_MAIN<<CHANNEL_UNIN_BITOFF;
                    channelNum |= i<<CHANNEL_MODULE_BITOFF;
                    channelNum |= k+1;
                    m_list_DO.append(channelNum);
                }
                break;
            case STATUS_BOARD_TYPE_EXT:
                extValidFlag = true;
                break;
            default:
                break;
            }
        }
    }

    //扩展单元基础通道添加
    if (extValidFlag) {
        for (int i=0; i<EXT_UNIT_NUM; ++i){
            for (int j=0; j<EXT_UNIT_MODULE_NUM; ++j){
                quint16 boardStatus = p_gDeviceCfg->sysStatus.extUnit_ModuleStatus[i][j];
                if (STATUS_BOARD_TYPE(boardStatus) == STATUS_BOARD_TYPE_AI && STATUS_BOARD_STATUS(boardStatus)){
                    for (int k=0; j<STATUS_BOARD_CHAN0_NUM(boardStatus); ++k){
                        quint32 channelNum = Channel_Type_AI<<CHANNEL_TYPE_BITOFF;
                        channelNum |= (i+1)<<CHANNEL_UNIN_BITOFF;
                        channelNum |= j<<CHANNEL_MODULE_BITOFF;
                        channelNum |= k+1;
                        m_list_AI.append(channelNum);
                    }
                }
            }
        }
    }
}
