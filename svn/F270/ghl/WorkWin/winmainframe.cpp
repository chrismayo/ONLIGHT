#include "winmainframe.h"
#include "../GlobalData/globalDef.h"

WinMainStatus::WinMainStatus(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(DESKTOP_HEIGHT/MAINWIN_STATUSBAR_HIGHT_SCALE);
    setAutoFillBackground(true);
}

WinMainFrame *WinMainFrame::instance()
{
    static WinMainFrame data;
    return &data;
}

WinMainFrame::WinMainFrame(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setWinLayout();
    sigAndSlotConnect();
}

void WinMainFrame::addWorkWin(QWidget *workWin)
{
    m_workWinStacked.addWidget(workWin);
}

void WinMainFrame::initialize()
{
    p_mainLayout  = new QVBoxLayout();
}

void WinMainFrame::setWinLayout()
{
    setContentsMargins(0,0,0,0);
    p_mainLayout->setContentsMargins(0,0,0,0);
    p_mainLayout->setSpacing(0);

    p_mainLayout->addWidget(&m_statusBar);
    p_mainLayout->addWidget(&m_workWinStacked);

    setLayout(p_mainLayout);
}

void WinMainFrame::sigAndSlotConnect()
{

}
