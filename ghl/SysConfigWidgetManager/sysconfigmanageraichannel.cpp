#include "sysconfigmanageraichannel.h"

SysConfigManagerAiChannel::SysConfigManagerAiChannel(QObject *parent, SysConfigSlidingScreen *sliding) :
    QObject(parent) , p_sliding(sliding)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

SysConfigManagerAiChannel::~SysConfigManagerAiChannel()
{
    release();
}

void SysConfigManagerAiChannel::setSlidingScreen(SysConfigSlidingScreen *sp)
{
    if (sp == nullptr)
        return;

    p_sliding = sp;
    p_sliding->setInitWidget(p_widget_1Level_1);
}

void SysConfigManagerAiChannel::slotSlidingWidget(int index, QString content)
{ //need modify 需要修改

    switch (index) {
    case 2001:
        p_sliding->setNextWidget(p_leve2Widget->at(0));
        p_sliding->moveToNextWidget();
        break;
    case 3001:
        p_sliding->setNextWidget(p_leve3Widget->at(0));
        p_sliding->moveToNextWidget();
    case -2001:
        p_sliding->setPreWidget(p_leve2Widget->at(0)); //-2001负数表示反方向滑动，千位表示第几级窗体，剩下为at()的参数号
        p_sliding->movePreWidget();
        break;
    default:
        break;
    }
}

void SysConfigManagerAiChannel::initialize()
{
    p_widget_1Level_1 = new SCWAiChannel_1Level();
    p_widget_2Level_1 = new SCWAiChannel_2Level_1();
    p_widget_3Level_1 = new SCWAiChannel_3Level_1();

    p_leve1Widget = new QVector<QWidget *>;
    p_leve2Widget = new QVector<QWidget *>;
    p_leve3Widget = new QVector<QWidget *>;

    p_leve1Widget->append(p_widget_1Level_1);    //一级窗体指针缓存
    p_leve2Widget->append(p_widget_2Level_1);    //二级窗体指针缓存
    p_leve3Widget->append(p_widget_3Level_1);    //三级窗体指针缓存
}

void SysConfigManagerAiChannel::release()
{
    delete p_widget_1Level_1;
    delete p_widget_2Level_1;
    delete p_widget_3Level_1;

    delete p_leve1Widget;
    delete p_leve2Widget;
    delete p_leve3Widget;
}

void SysConfigManagerAiChannel::setUserDefineStyle()
{

}

void SysConfigManagerAiChannel::setUserDefineContent()
{

}

void SysConfigManagerAiChannel::setWinLayout()
{

}

void SysConfigManagerAiChannel::sigAndSlotConnect()
{
    connect(p_widget_1Level_1, SIGNAL(sigNextWidgetIndex(int,QString)), this, SLOT(slotSlidingWidget(int,QString)));
    connect(p_widget_2Level_1, SIGNAL(sigNextWidgetIndex(int,QString)), this, SLOT(slotSlidingWidget(int,QString)));
    connect(p_widget_3Level_1, SIGNAL(sigNextWidgetIndex(int,QString)), this, SLOT(slotSlidingWidget(int,QString)));
}
