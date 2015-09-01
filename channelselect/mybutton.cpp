#include "mybutton.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>
myButton::myButton(QWidget *parent) :
    QPushButton(parent)
{
    event = new QResizeEvent(QSize(1, 1), QSize(1, 1));
//    this->setFlat(true);
}

void myButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        qDebug() << "emit signal";
        emit buttonClicked(event);
    }
}
