/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：dataGlobbalDef_SysStatus.h
 * 概   要：系统状态结构体定义
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

#ifndef DATAGLOBALDEF_SYSSTATUS_H
#define DATAGLOBALDEF_SYSSTATUS_H

#include "cfgGlobalDef_Type.h"

#define STATUS_BOARD_STATUS(x)    (x & 0x0001)                  //板卡状态
#define STATUS_BOARD_CHAN1_NUM(x)   (((x)>>1) & 0x3f)   //DIO板卡类型DO通道数
#define STATUS_BOARD_CHAN0_NUM(x)   (((x)>>7) & 0x3f)   //DIO板卡类型DI通道数
#define STATUS_BOARD_EXT_STATUS(x)   (((x)>>7) & 0x3f)      //本机扩展子板卡外扩有效单元标记
#define STATUS_BOARD_TYPE(x)    ((x)>>13 & 0x07)                //板卡类型

//板卡类型定义
#define STATUS_BOARD_TYPE_NONE  0       //无板卡，使用默认定义
#define STATUS_BOARD_TYPE_AI  1             //AI板卡
#define STATUS_BOARD_TYPE_DI  2             //DI板卡
#define STATUS_BOARD_TYPE_DO  3            //DO板卡
#define STATUS_BOARD_TYPE_DIO  4          //DIO板卡
#define STATUS_BOARD_TYPE_EXT  5           //扩展板卡

/*
 * quint16状态说明：
 *  bit0    :   子板卡状态，0-Not Ready;  1- Ready
 *  bit1-6 :   DIO板卡DO通道数，最多支持50个通道
 *  bit7-12:  子板卡通道数，最多支持50个通道，各类型板卡通道数，DIO对应DI通道数
 *  bit13-15: 子板卡类型， 0-None, 1-AI， 2-DI,  3-DO， 4-DIO， 5-Extern
 */
typedef struct SYSTEM_STATUS_STRUCT{
    quint16 mainUnit_ModuleStatus[MAIN_UNIT_MODULE_NUM];                            //本机板卡（模块）状态
    quint16 extUnit_ModuleStatus[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM];      //扩展单元板卡（模块）状态
}SYSTEM_STATUS;

#endif // DATAGLOBALDEF_SYSSTATUS_H
