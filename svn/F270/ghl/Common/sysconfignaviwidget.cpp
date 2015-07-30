#include "sysconfignaviwidget.h"

SysConfigNaviWidget::SysConfigNaviWidget(QPushButton *parent, int index) :
    QPushButton(parent), m_index(index)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

SysConfigNaviWidget::~SysConfigNaviWidget()
{
    release();
}

void SysConfigNaviWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit(sigClick(m_index));
    QPushButton::mouseReleaseEvent(event);
}


void SysConfigNaviWidget::initialize()
{
    setText(QString::number(m_index));
    setFixedHeight(QDesktopWidget().height() * 0.1);
    setFixedWidth(QDesktopWidget().width() * 0.17);
}

void SysConfigNaviWidget::release()
{

}

void SysConfigNaviWidget::setUserDefineStyle()
{
}

void SysConfigNaviWidget::setUserDefineContent()
{
    this->setStyleSheet(QString("QPushButton {background-color: gray}"));
}

void SysConfigNaviWidget::setWinLayout()
{
//    this->setStyleSheet(QString("QPushButton { border: 1px solid black}"));
//                                 QPushButton:hover {background-color: cyan}"));
//                                 QPushButton {background-color: yellow}"));
}

void SysConfigNaviWidget::sigAndSlotConnect()
{

}
