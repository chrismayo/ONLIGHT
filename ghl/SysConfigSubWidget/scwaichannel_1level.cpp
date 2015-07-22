#include "scwaichannel_1level.h"

SCWAiChannel_1Level::SCWAiChannel_1Level(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

SCWAiChannel_1Level::~SCWAiChannel_1Level()
{
    release();
}

void SCWAiChannel_1Level::slotNextSendWidgetIndex(int index, QString content)
{
    emit sigNextWidgetIndex(index, content);
}

void SCWAiChannel_1Level::initialize()
{
    p_vlayout = new QVBoxLayout();
    p_settingOption = new SysConfigOptionWidget();

}

void SCWAiChannel_1Level::release()
{
    delete p_settingOption;
    delete p_vlayout;
}

void SCWAiChannel_1Level::setUserDefineStyle()
{

}

void SCWAiChannel_1Level::setUserDefineContent()
{
    p_settingOption->setTargetWidgetIndex(2001);
    p_settingOption->setTitle(QString("aichannel_1"));
}

void SCWAiChannel_1Level::setWinLayout()
{
    p_vlayout->addWidget(p_settingOption);
    setLayout(p_vlayout);
}

void SCWAiChannel_1Level::sigAndSlotConnect()
{
    connect(p_settingOption, SIGNAL(sigTargetWidgetIndex(int,QString)), this, SLOT(slotNextSendWidgetIndex(int, QString)));
}
