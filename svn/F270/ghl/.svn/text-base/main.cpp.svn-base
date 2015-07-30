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

#include "./WorkWin/winmainframe.h"
#include "./WorkWin/winroot.h"

#include "./GlobalData/sqlBlock_RecordChanInfo.h"

#include "./Threads/threaddataprocess.h"
#include "./Threads/threaddatarecord.h"
#include "./Threads/threaddatasync.h"

#include "./WorkWin/wintrendgroup.h"

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qsqlerror.h>
#include <QDateTime>

DEVICE_CONFIG testConfigStruct;
DEVICE_CONFIG *p_gDeviceCfg=&testConfigStruct;                  //全局变量指针，指向LPSRAM中的设备配置结构

QSharedMemory   g_sharedDataTable;

quint64 gTmep;
//线程初始化：信号槽链接  && 启动线程
void threadInit()
{
    QObject::connect(ThreadDataProcess::instance(), SIGNAL(sigMathProcessFinished()), \
                                   ThreadDataSync::instance(), SIGNAL(sigSyncData()));

    ThreadDataProcess::instance()->changeMeasurePeriod();

    ThreadDataRecord::instance()->start();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    threadInit();

    WinMainFrame *pMainWin = WinMainFrame::instance();

    pMainWin->addWorkWin(new WinRoot());
    pMainWin->showFullScreen();

    WinTrendGroup *pTrend = new WinTrendGroup;
    pTrend->showFullScreen();

    return a.exec();
}
