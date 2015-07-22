#include "threaddatacomm.h"

extern MODBUS_REGISTER_MAP  g_originDataMap;   //全局变量，原始数据对象

ThreadDataComm *ThreadDataComm::instance()
{
    static ThreadDataComm data;
    return &data;
}

ThreadDataComm::ThreadDataComm(QObject *parent) :
    QObject(parent)
{
}
