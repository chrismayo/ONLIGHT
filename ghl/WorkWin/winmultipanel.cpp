#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

#include "winmultipanel.h"

WinMultiPanel::WinMultiPanel(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("background-color:rgb(1,16,177);border:0;");
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(6);
    m_gridLayout->setContentsMargins(11, 11, 11, 11);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));

    QWidget *widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,0,0,2,2);

    widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,0,2,1,1);

    widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,1,2,1,1);

    widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,2,2,1,1);

    widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,2,0,1,1);

    widget = new QWidget(this);
    widget->installEventFilter(this);
    m_gridLayout->addWidget(widget,2,1,1,1);
}


bool WinMultiPanel::eventFilter(QObject * watched, QEvent * event)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button() == Qt::LeftButton){
            event->accept();
            QWidget *widget = static_cast<QWidget *>(watched);
            widget->setGeometry(widget->x()+1, widget->y()+1,widget->width(),widget->height());
            qDebug()<<"press";
        }
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button() == Qt::LeftButton){
            event->accept();
            QWidget *widget = static_cast<QWidget *>(watched);
            widget->setGeometry(widget->x()-1, widget->y()-1,widget->width(),widget->height());
            qDebug()<<"release";
        }
    }else if(event->type() == QEvent::MouseMove){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button() == Qt::LeftButton){
            event->accept();
            qDebug()<<"move";
        }
    }
}
