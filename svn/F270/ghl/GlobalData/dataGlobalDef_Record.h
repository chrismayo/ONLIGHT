#ifndef DATAGLOBALDEF_RECORD_H
#define DATAGLOBALDEF_RECORD_H

#include <QtGlobal>

#include "cfgGlobalDef_Type.h"

//显示数据单点数据结构
typedef struct DISPLAY_DATA_STRUCT {
    qreal   Max;
    qreal   Min;
}DISPLAY_DATA;

typedef struct DISPLAY_DATA_DIO_STRUCT {
    quint8 Max;
    quint8 Min;
}DISPLAY_DATA_DIO;

//所有通道显示数据结构体
typedef struct DISPLAY_DATA_RECORD_STRUCT {
    //本机AI类型通道数据
    DISPLAY_DATA mainUnit_AI_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //扩展AI类型通道数据
    DISPLAY_DATA extUnit_AI_Data[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //本机DI类型通道数据
    DISPLAY_DATA mainUnit_DI_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //本机DO类型通道数据
    DISPLAY_DATA mainUnit_DO_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //MATH通道数据
    DISPLAY_DATA device_Math_Data[MAIN_UNIT_MATH_CHAN_NUM_PRE];
    //COMM通道数据
    DISPLAY_DATA device_Comm_Data[MAIN_UNIT_COMM_CHAN_NUM_PRE];
}DISPLAY_DATA_RECORD;

//所有通道事件数据结构体
typedef struct EVENT_DATA_RECORD_STRUCT {
    //本机AI类型通道数据
    qreal mainUnit_AI_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //扩展AI类型通道数据
    qreal extUnit_AI_Data[EXT_UNIT_NUM][EXT_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //本机DI类型通道数据
    qreal mainUnit_DI_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //本机DO类型通道数据
    qreal mainUnit_DO_Data[MAIN_UNIT_MODULE_NUM][UNIT_CHAN_NUM_PRE];
    //MATH通道数据
    qreal device_Math_Data[MAIN_UNIT_MATH_CHAN_NUM_PRE];
    //COMM通道数据
    qreal device_Comm_Data[MAIN_UNIT_COMM_CHAN_NUM_PRE];
}EVENT_DATA_RECORD;

#endif // DATAGLOBALDEF_RECORD_H
