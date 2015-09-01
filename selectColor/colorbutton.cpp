#include "colorbutton.h"
#include <QDebug>
ColorButton::ColorButton(QWidget *parent) :
    QLabel(parent)
{
}

void ColorButton::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit sigLabelClicked();
}
