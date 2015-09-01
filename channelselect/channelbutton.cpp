#include "channelbutton.h"
#include <QMouseEvent>
#include <QDebug>
ChannelButton::ChannelButton(QWidget *parent) :
    QPushButton(parent)
{
}

void ChannelButton::mouseMoveEvent(QMouseEvent *e)
{
    emit sigMouseMove(e->x(), e->y());
}
