#include "scwaichannel_3level_1.h"

SCWAiChannel_3Level_1::SCWAiChannel_3Level_1(QWidget *parent):
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

SCWAiChannel_3Level_1::~SCWAiChannel_3Level_1()
{
    release();
}

void SCWAiChannel_3Level_1::slotNextSendWidgetIndex(int index, QString content)
{
    emit sigNextWidgetIndex(index, content);
}

void SCWAiChannel_3Level_1::initialize()
{
    p_vlayout = new QVBoxLayout();
    p_settingOption = new SysConfigOptionWidget();
}

void SCWAiChannel_3Level_1::release()
{
    delete p_settingOption;
    delete p_vlayout;
}

void SCWAiChannel_3Level_1::setUserDefineStyle()
{

}

void SCWAiChannel_3Level_1::setUserDefineContent()
{
    p_settingOption->setTargetWidgetIndex(-2001);
    p_settingOption->setTitle(QString("aichannel_3"));
}

void SCWAiChannel_3Level_1::setWinLayout()
{
    p_vlayout->addWidget(p_settingOption);
    setLayout(p_vlayout);
}

void SCWAiChannel_3Level_1::sigAndSlotConnect()
{
    connect(p_settingOption, SIGNAL(sigTargetWidgetIndex(int,QString)), this, SLOT(slotNextSendWidgetIndex(int, QString)));
}

