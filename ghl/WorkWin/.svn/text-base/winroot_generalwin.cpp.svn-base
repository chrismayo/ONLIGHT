#include "winroot_generalwin.h"
#include <QPainter>


WinRoot_GeneralWin::~WinRoot_GeneralWin()
{

}

WinRoot_GeneralWin::WinRoot_GeneralWin(QWidget *parent) :
    QWidget(parent)
{
}


/*
 * 功能：
 * 	  QWidget::paintEvent()重新实现。
 */
void WinRoot_GeneralWin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,this->width(), this->height(), QColor(0,255,255));
}
