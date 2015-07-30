#include "winroot_sysconfig.h"

#include <QPainter>

WinRoot_SysConfig::WinRoot_SysConfig(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

WinRoot_SysConfig::~WinRoot_SysConfig()
{
    release();
}

void WinRoot_SysConfig::slotNavigationSwitch(int widgetIndex)
{
    switch (widgetIndex) {
    case 0: //aiChannel
        p_manageAiChannel->setSlidingScreen(p_sysConfigSlidingScreen);
        break;
    case 1:  //batchProc
        break;
    case 2:  //p_calcChannel
        break;
    case 3:  //comChannel
        break;
    case 4:  //diChannel
        break;
    case 5:  //display
        break;
    case 6:  //doChannel
        break;
    case 7:  //entherNet
        break;
    case 8:  //eventAction
        break;
    case 9:  //measure
        break;
    case 10: //record
        break;
    case 11: //report
        break;
    case 12: //saveData
        break;
    case 13: //security
        break;
    case 14: //serialPort
        break;
    case 15: //system
        break;
    case 16: //timer
        break;
    default:
        break;
    }
}

void WinRoot_SysConfig::resizeEvent(QResizeEvent *event)
{
    p_sysConfigSlidingScreen->setFixedWidth(rect().width()*0.80);
    QSize size = QSize(rect().width()*0.79, rect().height());
    p_sysConfigSlidingScreen->setSize(size);
    QWidget::resizeEvent(event);
}

void WinRoot_SysConfig::initialize()
{
    QAbstractScrollArea p;
    p_hLayout_Main = new QHBoxLayout();
    p_vLayout_Navigation = new QVBoxLayout();
    p_vWidget_Navigation = new QWidget();
    p_scrollArea = new QScrollArea();

    p_navWidget = new QVector<SysConfigNaviWidget *>(17,nullptr);

    for (int i = 0; i<17; ++i)
    {
        p_navWidget->operator [](i) = new SysConfigNaviWidget(0, i);
    }

    p_sysConfigSlidingScreen = new SysConfigSlidingScreen();
    p_manageAiChannel = new SysConfigManagerAiChannel();
}

void WinRoot_SysConfig::release()
{

   for (int i = 0; i<17; ++i)
   {
       delete p_navWidget->operator [](i);
   }
   delete p_navWidget;

   delete p_manageAiChannel;
   delete p_vLayout_Navigation;
   delete p_sysConfigSlidingScreen;
   delete p_vWidget_Navigation;
   delete p_scrollArea;
   delete p_hLayout_Main;

}

void WinRoot_SysConfig::setUserDefineStyle()
{

}

void WinRoot_SysConfig::setUserDefineContent()
{
    p_sysConfigSlidingScreen->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    p_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_vLayout_Navigation->setContentsMargins(0,0,0,0);
    p_vLayout_Navigation->setSpacing(0);
    p_vLayout_Navigation->setMargin(0);
}

void WinRoot_SysConfig::setWinLayout()
{
    foreach(SysConfigNaviWidget *p,  *p_navWidget)
        p_vLayout_Navigation->addWidget(p);

    p_vWidget_Navigation->setLayout(p_vLayout_Navigation);
    p_scrollArea->setWidget(p_vWidget_Navigation);
    p_hLayout_Main->addWidget(p_scrollArea);
    p_hLayout_Main->addWidget(p_sysConfigSlidingScreen);
    this->setLayout(p_hLayout_Main);
}

void WinRoot_SysConfig::sigAndSlotConnect()
{
    foreach(SysConfigNaviWidget *p,  *p_navWidget)
        connect(p, SIGNAL(sigClick(int)), this, SLOT(slotNavigationSwitch(int)));
}

/*
 * 功能：
 * 	  QWidget::paintEvent()重新实现。
 */
void WinRoot_SysConfig::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,this->width(), this->height(), QColor(0,0,255));
}
