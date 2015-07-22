#include <QApplication>
#include <QLabel>
#include <QSharedMemory>
#include <QTableView>

#include <QDebug>
#include <QDateTime>
#include "./Common/slidingscreen.h"
#include "./Common/softkeypad.h"
#include "./GlobalData/cfgGlobalDef.h"
#include "./GlobalData/dataGlobalDef_ModbusReg.h"

#include "./DataModel/modeldigitalgroupchannel.h"
#include "./Threads/threaddataprocess.h"

#include "./WorkWin/winmainframe.h"
#include "./WorkWin/winroot.h"

#include "./GlobalData/sqlBlock_RecordChanInfo.h"

#include "./Threads/threaddatarecord.h"

DEVICE_CONFIG testConfigStruct;
DEVICE_CONFIG *p_gDeviceCfg=&testConfigStruct;                  //全局变量指针，指向LPSRAM中的设备配置结构

QSharedMemory   g_sharedDataTable;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ThreadDataRecord *pDispData = new ThreadDataRecord;
//    pDispData->start();

//    ThreadDataProcess::instance()->sigDataProcessFinished();

//    WinMainFrame *pMainWin = WinMainFrame::instance();

//    pMainWin->addWorkWin(new WinRoot());
//    pMainWin->showFullScreen();

//    DISPLAY_DATA_RECORD testData;
//    pDispData->newDispData(&testData);
//    pDispData->newDispData(&testData);
//    pDispData->newDispData(&testData);
//    pDispData->newDispData(&testData);

//    EVENT_DATA_RECORD testDataEvent;
//    pDispData->newManualData(&testDataEvent);
//    pDispData->newManualData(&testDataEvent);
//    pDispData->newManualData(&testDataEvent);
//    pDispData->newManualData(&testDataEvent);

    SoftKeyPad w;
    w.show();

    return a.exec();
}
