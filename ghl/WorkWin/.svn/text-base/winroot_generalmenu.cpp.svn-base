#include "winroot_generalmenu.h"
#include <QPainter>


WinRoot_GeneralMenu::WinRoot_GeneralMenu(QWidget *parent) :
    QWidget(parent)
{
}

/*
 * 功能：
 * 	  QWidget::paintEvent()重新实现。
 */
void WinRoot_GeneralMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,this->width(), this->height(), QColor(255,255,0));
}
