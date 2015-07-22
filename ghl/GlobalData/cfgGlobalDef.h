/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：CfgGlobbalDef.h
 * 概   要：设备配置结构体、宏、枚举值定义
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
#include <QtGlobal>

#include "cfgGlobalDef_Measure.h"
#include "cfgGlobalDef_Record.h"
#include "cfgGlobalDef_Display.h"
#include "cfgGlobalDef_DataSave.h"
#include "cfgGlobalDef_Batch.h"
#include "cfgGlobalDef_Report.h"
#include "cfgGlobalDef_Timer.h"
#include "cfgGlobalDef_EventAction.h"
#include "cfgGlobalDef_Network_Basic.h"
#include "cfgGlobalDef_Network_FTPClient.h"
#include "cfgGlobalDef_Network_SMTPClient.h"
#include "cfgGlobalDef_Network_Email.h"
#include "cfgGlobalDef_Network_SNTPClient.h"
#include "cfgGlobalDef_Network_ModbusClient.h"
#include "cfgGlobalDef_Network_Server.h"
#include "cfgGlobalDef_SerialClient.h"
#include "cfgGlobalDef_SysEnvironment.h"

#include "dataGlobalDef_SysStatus.h"
#include "dataGlobalDef_Record.h"

#include "cfgGlobalDef_AI.h"
#include "cfgGlobalDef_DI.h"
#include "cfgGlobalDef_DO.h"
#include "cfgGlobalDef_Math.h"
#include "cfgGlobalDef_Comm.h"

#ifndef CFGGLOBALDEF_H
#define CFGGLOBALDEF_H

#define AI_CHANNEL_NUM_MAX  500                 //输入输出通道数上限
#define DI_CHANNEL_NUM_MAX  500                 //数字输入通道数上限
#define DO_CHANNEL_NUM_MAX  500                //数字输出通道数上限
#define MATH_CHANNEL_NUM_MAX    100         //运算通道数上限
#define COMM_CHANNEL_NUM_MAX   300        //通信通道数上限

typedef struct DEVICE_CONFIG_STRUCT{
    /***********************测量配置**********************/
    Measure_Interval                  measureInterval_ms;             //测量周期
    Measure_OverRange             measureOverRange;       //量程溢出判定

    /*********************记录配置************************/
    Record_Mode                         recordMode;                     //数据记录模式
    bool                                        recordConfirm;                //记录画面确认，false-off, true-on
    //事件数据相关
    Event_Record_Interval           eventRecordInterval_ms;      //事件记录周期
    Event_Record_Mode               eventRecordMode;         //事件记录模式
    Event_Record_DataLength     eventRecordLength;       //事件记录数据长度
    quint32                                    eventRecordPreTrigger; //事件前置触发(%),范围:0/5/25/50/75/95/10, 【自由】模式外有效
    bool                                         eventRecordTriggerSrc;  //触发源操作，false-off, true-on， 通过画面操作触发，【自由】模式外有效
    quint32                                    eventRecordChNum;      //事件记录通道数，Max:500
    quint32                                    eventRecordChItem[500];       //事件记录通道号
    //显示数据相关
    Display_Record_DataLength  displayRecordLength;     //显示记录数据长度
    quint32                                    displayRecordChNum;    //显示记录通道数，Max:500
    quint32                                    displayRecordChItem[500];     //显示记录通道号
    //手动采样
    quint32                                    manualSampleChNum;   //手动采样通道数，Max:50
    quint32                                    manualSampleChItem[50];      //手动采样通道号

    /***********************显示设置***********************/
    DISPLAY_GONFIG_TREND      displayTrend;                   //显示配置之趋势周期设置
    DISPLAY_GONFIG_GROUP     displayGroup[50];                  //显示配置之组设置
    DISPLAY_GONFIG_PRE_MESSAGE  displayMessage;     //显示配置之预定义信息
    DISPLAY_GONFIG_BASIC       displayBasic;                    //显示配置之画面基本设定

    /********************数据保存设置***********************/
    DATASAVE_CONFIG                dataSaveConfig;                   //数据保存设置

    /********************批处理设置***********************/
    BATCH_CONFIG                      batchConfig;                        //批处理相关设置

    /********************报表设置***********************/
    REPORT_CONFIG                   reportConfig;                        //报表设置

    /********************计时器设置*********************/
    TIMER_CONFIG                     timerConfig;                          //计时器设置

    /********************事件动作设置*********************/
    EVENT_ACTION_CONFIG      eventActiveConfig;                //事件动作配置

    /**********************网络设置*********************/
    NETWORK_CONFIG_BASIC                    networkBasic;               //网络基本设置
    NETWORK_CONFIG_FTPCLIENT            networkFTP;                  //网络FTP客户端设置
    NETWORK_CONFIG_SMTPCLIENT        networkSTMP;               //SMTP客户端设置
    NETWORK_CONFIG_EMAIL                   networkEmail;               //邮件相关设置
    NETWORK_CONFIG_SNTPCLIENT         networkSNTP;                //SNTP设定
    NETWORK_CONFIG_MODBUSCLIENT  networkModbus;           //Modbus客户端设定
    NETWORK_CONFIG_SERVER                 networkServer;              //网络服务器相关设定

    /**********************串口设置*********************/
    SERIAL_CONFIG_MODBUSCLIENT       serialConfig;                  //串口配置

    /*****************系统整体环境配置******************/
    SYS_CONFIG_ENVRIONMENT               systemConfig;              //系统整体配置

    /********************* 通道配置*********************/
    AI_CONFIG                           mainUnitAI[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    AI_CONFIG                           extUnitAI[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    DI_CONFIG                           mainUnitDI[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
//    DI_CONFIG                           extUnitDI[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    DO_CONFIG                          mainUnitDO[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
//    DO_CONFIG                          extUnitDO[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    MATH_CONFIG                     chanMath[MATH_CHANNEL_NUM_MAX];
    COMM_CONFIG                   chanComm[COMM_CHANNEL_NUM_MAX];

    //运算通道相关配置
    qreal                                     mathConstK[100];                          //运算式常数
    Math_Error_Value_Enum    mathErrorVal;                                //运算错误显示值
    Math_Key_Action                 mathKeyAction;                             //START/STOP键动作设定
    Math_Over_Range               mathSumAve;                                //SUM, AVE计算溢出处理
    Math_Over_Range               mathMaxMinPP;                           //MAX, MIN, P-P计算溢出处理

    /********************系统状态**********************/
    SYSTEM_STATUS                  sysStatus;                                       //设备状态
}DEVICE_CONFIG;

#endif // CFGGLOBALDEF_H
