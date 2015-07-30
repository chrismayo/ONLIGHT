#ifndef CFGGLOBALDEF_TYPE_H
#define CFGGLOBALDEF_TYPE_H


#define GROUP_NUM_MAX   50      //有效组最大数
#define GROUP_CHANNEL_NUM_MAX 20    //组包含的最大通道数

#define MAIN_UNIT_MODULE_NUM    10          //本机最大模块数（子板/卡槽）
#define EXT_UNIT_MODULE_CHAN_NUM    10  //扩展单元每个模块AI通道数, 扩展单元只支持AI类型板卡
#define EXT_UNIT_MODULE_NUM     6              //每个扩展单元最大模块数（子板/卡槽）
#define EXT_UNIT_NUM        6                            //最大扩展单元数

#define UNIT_CHAN_NUM_PRE   50                  //AI/DI/DO/DIO各通道预留分配通数

#define AI_UNIT_CHAN_NUM_USE    10              //AI通道实际通道数
#define DIO_UNIT_CHAN_NUM_USE_MAX   16    //DI/DO/DIO模块实际使用通道最大数
#define UNIT_CHAN_NUM_USE_MAX    16           //AI/DI/DO/DIO模块实际使用最大通道数,即AI_UNIT_CHAN_NUM_USE与DIO_UNIT_CHAN_NUM_USE_MAX最大值

#define MAIN_UNIT_IO_CHAN_NUM_PRE  500         //本机预留IO最大通道数： 10(卡槽数) * 50(每板卡预留50个通道) = 500(本机通道数)
#define MAIN_UNIT_IO_CHAN_NUM_USE  100         //本机实际IO最大通道数：10(卡槽数) * 10(每板卡实际最多) = 100(本机通道数)

#define EXT_UNIT_IO_CHAN_NUM_PRE    300           //扩展单元预留IO最大通道数：6(卡槽数) * 50(每板卡预留50个通道) = 300(通道数)

#define MAIN_UNIT_MATH_CHAN_NUM_PRE 100    //本机运算预留通道数：最多100个运算通道

#define MAIN_UNIT_COMM_CHAN_NUM_PRE 500   //本机通信预留通道数：最多500个通信通道
#define MAIN_UNIT_COMM_CHAN_NUM_USE 300   //本机通信实际通道数：最多300个通信通道

#define MAIN_UNIT_INTERNAL_SWITCH   100           //本机内部开关

#ifndef OFF
#define OFF 0
#endif

#ifndef ON
#define ON 1
#endif

//通道错误代码
#define DATA_ERROR_NORMAL   0                             //无错误
#define DATA_ERROR_OFF            1                             //不使用
#define DATA_ERROR_OVER_POSITIVE  2                   //正溢出
#define DATA_ERROR_OVER_NEGATIVE  3                  //负溢出
#define DATA_ERROR_BURNOUT_POSITIVE   4          //正断偶
#define DATA_ERROR_BURNOUT_NEGATIVE   5         //负断偶
#define DATA_ERROR_AD_ERROR   6                           //AD异常
#define DATA_ERROR_INVALID    7                              //无效数据
#define DATA_ERROR_MATH_ERROR 16                      //运算错误
#define DATA_ERROR_COMM_ERROR 17                    //通信错误
#define DATA_ERROR_MASK     0x1F                           //错误掩码

#define DATA_STATUS_ERROR_BITSOFF 8                   //通道错误代码位偏移
#define DATA_STATUS_ALARM1_BITSOFF  0                //通道状态报警电平1位偏移
#define DATA_STATUS_ALARM2_BITSOFF  1                //通道状态报警电平2位偏移
#define DATA_STATUS_ALARM3_BITSOFF  2                //通道状态报警电平3位偏移
#define DATA_STATUS_ALARM4_BITSOFF  3                //通道状态报警电平4位偏移

#define IS_DATA_NORMAL(x)                      (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_NORMAL ? 1 : 0)
#define IS_DATA_OFF(x)                               (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_OFF ? 1 : 0)
#define IS_DATA_OVER_POSITIVE(x)           (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_OVER_POSITIVE ? 1 : 0)
#define IS_DATA_OVER_NEGATIVE(x)          (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_OVER_NEGATIVE ? 1 : 0)
#define IS_DATA_BURNOUT_POSITIVE(x)   (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_BURNOUT_POSITIVE ? 1 : 0)
#define IS_DATA_BURNOUT_NEGATIVE(x)   (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_BURNOUT_NEGATIVE ? 1 : 0)
#define IS_DATA_AD_ERROR(x)                     (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_AD_ERROR ? 1 : 0)
#define IS_DATA_INVALID(x)                        (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_INVALID ? 1 : 0)
#define IS_DATA_MATH_ERROR(x)               (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_MATH_ERROR ? 1 : 0)
#define IS_DATA_COMM_ERROR(x)             (((x)>>DATA_STATUS_ERROR_BITSOFF)==DATA_ERROR_COMM_ERROR ? 1 : 0)

#define MODBUS_MAP_KEY      "ModbusRegMap"

/* 数据模型角色定义*/
typedef enum ChannelItemRole_Enum {
    ChannelData = 0,            //测量数据 QString
    ChannelType,                  //通道类型，0/1/2/3/4/5: AI/DI/DO/MATH/COMM， uint
    ChannelTag,                    //通道标记  QString
    ChannelColor,                //通道颜色  QColor,Byte2-Red, Byte1-Green, Byte0-Blue
    ChannelUnit,                 //通道单位  QString
    ChannelRangeUpper,    //通道量程上限 qreal
    ChannelRangeDowner, //通道量程下限 qreal

    ChannelDispUpper,       //显示区域上限（%），趋势窗体    uint
    ChannelDispDowner,    //显示区域下限（%），趋势窗体    uint

    ChannelScalePos,          //标尺位置1-10,趋势窗体标尺部分   uint
    ChannelSacleDiv,          //标尺分割数，趋势窗体标尺部分     uint

    ChannelBarBase,          //棒图基准位置，1/2/3 ： 下限/中央/上限  uint
    ChannelBarDiv,             //棒图分割数：4-12 uint

    ChannelPartScaleOnOff, //部分放大缩小开关，趋势窗体，bool
    ChannelPartScalePos,     //部分放大缩小位置（%），趋势窗体，uint
    ChannelPartScaleBound,//部分放大缩小边界值，趋势窗体，qreal

    ChannelColorScalePos,  //彩色标尺带区域，0/1/2:off/内侧/外侧， 棒图/趋势共用，uint
    ChannelColorScaleColor, //彩色标尺带颜色 uint
    ChannelColorScaleUpper, //彩色标尺带上限，qreal
    ChannelColorScaleDowner, //彩色标尺带下限，qreal

    ChannelAlarmOnOff,  //报警点标记，在标尺上显示开关，趋势/棒图共用，bool
    ChannelAlarmType,    //报警点标记类型，0/1:报警/固定，uint
    ChannelAlarm1Type,  //报警1类型，0/1/2/3/4/5/6/7/8 ： off/H/L/R/r/T/t/h/l，uint
    ChannelAlarm1Status, //报警1状态，
    ChannelAlarm1Value, //报警1报警值，qreal
    ChannelAlarm1Color, //报警1颜色，固定模式,uint,Byte2-Red, Byte1-Green, Byte0-Blue
    ChannelAlarm2Type,  //报警2类型，0/1/2/3/4/5/6/7/8 ： off/H/L/R/r/T/t/h/l，uint
    ChannelAlarm2Status, //报警2状态，
    ChannelAlarm2Value, //报警2报警值，qreal
    ChannelAlarm2Color, //报警2颜色，固定模式,uint,Byte2-Red, Byte1-Green, Byte0-Blue
    ChannelAlarm3Type,  //报警3类型，0/1/2/3/4/5/6/7/8 ： off/H/L/R/r/T/t/h/l，uint
    ChannelAlarm3Status, //报警3状态，
    ChannelAlarm3Value, //报警3报警值，qreal
    ChannelAlarm3Color, //报警3颜色，固定模式,uint,Byte2-Red, Byte1-Green, Byte0-Blue
    ChannelAlarm4Type,  //报警4类型，0/1/2/3/4/5/6/7/8 ： off/H/L/R/r/T/t/h/l，uint
    ChannelAlarm4Status, //报警4状态，
    ChannelAlarm4Value, //报警4报警值，qreal
    ChannelAlarm4Color, //报警4颜色，固定模式,uint,Byte2-Red, Byte1-Green, Byte0-Blue
}ChannelItemRole;

/* 板卡（模块）类型定义*/
typedef enum Module_Type_Enum {
    Module_Type_AI = 0,                 //模拟输入板卡
    Module_Type_DI ,                      //数字输入板卡
    Module_Type_DO ,                    //数字输出板卡
    Module_Type_DIO,                    //数字输入输出板卡
    Module_Type_EXT,                     //扩展板卡
}Module_Type;

/* 通道类型定义*/
typedef enum Channel_Type_Enum{
    Channel_Type_Off = 0,       //不使用/无效通道
    Channel_Type_AI,              //输入输出通道
    Channel_Type_DI,               //数字输入
    Channel_Type_DO,             //数字输出
    Channel_Type_Comm,        //通信通道
    Channel_Type_Math,          //运算通道
}Channel_Type;

/* 数据运算状态*/
typedef enum Math_Status_Type_Enum {
    Math_Status_Type_Off = 0,           //运算关闭
    Math_Status_Type_On,                 //运算on
    Math_Status_Type_On_Reset,      //运算on（运算复位）
}Math_Status_Type;

/*报警类型*/
typedef enum Alarm_Type_Enum {
    Alarm_Type_Off = 0,
    Alarm_Type_H,                                              //上限
    Alarm_Type_L ,                                              //下限
    Alarm_Type_R,                                              //变化率上升限
    Alarm_Type_r,                                               //变化率下升限
    Alarm_Type_T,                                              //延迟上限
    Alarm_Type_t,                                              //延迟下限
    Alarm_Type_h,                                             //差值上限， Delta运算时有效
    Alarm_Type_l,
}Alarm_Type;

/* 寄存器类型定义*/
typedef enum Register_Type_Enum{
    Register_Type_INT16 = 0,
    Register_Type_UINT16,
    Register_Type_INT32B,
    Register_Type_INT32L,
    Register_Type_UINT32B,
    Register_Type_UINT32L,
    Register_Type_FLOAT,
    Register_Type_FLOATB,
    Register_Type_FLOATL,
    Register_Type_BIT,
}Register_Type;

/* 仪表状态类型定义*/
typedef enum  Device_Status_Type_Enum {
    Device_Status_Type_Record = 0,           //记录状态
    Device_Status_Type_Math,                     //运算状态
    Device_Status_Type_UserLock,              //用户锁定
    Device_Status_Type_UnderLogin,          //本体在登陆状态
    Device_Status_Type_MemErr,                //内存/外部存储器异常
    Device_Status_Type_MeasureErr,           //测量异常
    Device_Status_Type_CommErr,              //通信异常
}Device_Status_Type;

/* 语言类型定义*/
typedef enum Language_Type_Enum{
    Language_Type_English = 0,
    Language_Type_Japanese,
    Language_Type_German,
    Language_Type_French,
    Language_Type_Russian,
    Language_Type_Chinese,
    Language_Type_Korean,
}Language_Type;

/* 温度单位表示*/
typedef enum Temperature_Unit_Enum{
    Temperature_Unit_C = 0,
    Temperature_Unit_F,
}Temperature_Unit;

/* 小数点表示*/
typedef enum Decimal_Point_Type_Enum{
    Decimal_Point_Type_Point = 0,   //点
    Decimal_Point_Type_Comma,    //逗号
}Decimal_Point_Type;

/* 日期表示*/
typedef enum Date_Format_Enum{
    Date_Format_YMD =0,                 //年-月-日
    Date_Format_MDY,                      //月-日-年
    Date_Format_DMY,                      //日-月-年
}Date_Format;

/* 分割符表示*/
typedef enum Delimiter_Type_Enum{
    Delimiter_Type_Slash = 0,           // "/"
    Delimiter_Type_Point,                 // "."
    Delimiter_Type_Hyphen,             // "-"
}Delimiter_Type;

/* 月份表示*/
typedef enum Month_Indicator_Enum{
    Month_Indicator_Numerical = 0,  //数字
    Month_Indicator_Character,          //字符
}Month_Indicator;

/* 报警指示*/
typedef enum Alarm_Indicator_Enum{
    Alarm_Indicator_NonHold = 0,       //非保持
    Alarm_Indicator_Hold,                    //保持
}Alarm_Indicator;

/* 内部开关模式*/
typedef enum InterSwitch_Mode_Enum{
    InterSwitch_Mode_Alarm = 0,         //报警
    InterSwitch_Mode_Manual,             //手动
}InterSwitch_Mode;

/* 内部开关操作*/
typedef enum InterSwitch_Operate_Enum{
    InterSwitch_Operate_And = 0,         //与
    InterSwitch_Operate_Or,                  //或
}InterSwitch_Operate;

/* 继电器输出模式*/
typedef enum Relay_Output_Mode_Enum{
    Relay_Output_Mode_Fail = 0,          //异常输出
    Relay_Output_Mode_Status,           //状态输出
}Relay_Output_Mode;

/* 打印机纸张类型*/
typedef enum Printer_Paper_Size_Enum{
    Printer_Paper_Size_A4 = 0,
    Printer_Paper_Size_A3,
    Printer_Paper_Size_Letter,
}Printer_Paper_Size;

/* 打印机打印方向*/
typedef enum Printer_Orientation_Enum{
    Printer_Orientation_Ver = 0,
    Printer_Orientation_Hor,
}Printer_Orientation;

/* 打印机精度*/
typedef enum Printer_Resolution_DPI_Enum{
    Printer_Resolution_DPI_300 = 0,
    Printer_Resolution_DPI_600,
}Printer_Resolution_DPI;

/* SQL数据库信息块类型*/
typedef enum SQL_Block_Type_Enum{
    SQL_Block_Type_FileFormat = 0,          //文件格式识别块
    SQL_Block_Type_FileInfo,                     //文件信息块
    SQL_Block_Type_Group,                       //组信息复合块
    SQL_Block_Type_RecordChan,             //通道信息复合块
//    SQL_Block_Tyep_AlarmInfo,                //报警信息复合块
//    SQL_Block_Tyep_MessageInfo,           //消息复合块
    SQL_Block_Type_Report,                      //报表信息复合块
}SQL_Block_Type;

/* SQL数据库记录状态类型*/
typedef enum SQL_Record_Status_Enum{
    SQL_Record_Status_ManualKey = 0,    //手动按键开始或停止
    SQL_Record_Status_Trigger,                  //自动触发
    SQL_Record_Status_Recording,            //记录中
    SQL_Record_Status_AutoSplitter,         //自动保存，分割
    SQL_Record_Status_PowerOff,             //电源关闭
}SQL_Record_Status;

/* 数据库记录同步状态类型*/
typedef enum SQL_Record_Sync_Enum {
    SQL_Record_Sync_Off = 0,                    //同步功能off, 记录无需同步到外部存储器
    SQL_Record_Sync_On_Unsaved,          //同步功能on, 且记录还未同步到外部存储器
    SQL_Record_Sync_On_Saved,               //同步功能on,且记录已同步到外部存储器
}SQL_Record_Sync_Enum;

/* 报警状态类型*/
typedef enum SQL_Alarm_Status_Enum {
    SQL_Alarm_Status_NonHold_Occur = 0,    //非保持状态下，报警发生
    SQL_Alarm_Status_NonHold_Release,       //非保持状态下，报警释放
    SQL_Alarm_Status_NonHold_AllOff,
    SQL_Alarm_Status_Hold_Occur_NoAck,    //保持状态下，报警发生，且未解除（Non ACK）
    SQL_Alarm_Status_Hold_Occur_Ack,         //保持状态下，报警发生，且已解除（ACK）
    SQL_Alarm_Status_Hold_Release_NoAck, //保持状态下，报警释放，且未解除（Non ACK）
    SQL_Alarm_Status_Hold_Release_Ack,      //保持状态下，报警释放，且已解除（ACK）
    SQL_Alarm_Status_Hold_Ack_All,
    SQL_Alarm_Status_Hold_Ack_Single,
}SQL_Alarm_Status;

#endif // CFGGLOBALDEF_TYPE_H
