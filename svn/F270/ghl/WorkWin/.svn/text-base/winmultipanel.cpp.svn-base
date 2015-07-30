#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QFrame>

#include "winmultipanel.h"
#include "windigitalgroup.h"

WinMultiPanel::WinMultiPanel(QWidget *parent) :
    m_pressed(false),QWidget(parent)
{
    this->setStyleSheet("background-color:rgb(255,16,177);border:0;");
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(6);
    m_gridLayout->setContentsMargins(11, 11, 11, 11);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));

    m_maskView = new QWidget();
    m_maskView->setObjectName("MaskView");
    m_maskView->setStyleSheet("QWidget#MaskView{background-color:rgb(100,100,100,50);border-radius:0px;border:3px solid;border-color:rgb(0,0,255,100);}");
    m_maskView->setVisible(false);


    QWidget *widget;
//    widget = new QWidget(this);
//    widget->installEventFilter(this);
//    m_gridLayout->addWidget(widget,0,0,2,2);

    WinDigitalGroup *group = new WinDigitalGroup(1,this);
    group->installEventFilter(this);
    m_gridLayout->addWidget(group,0,0,2,2);

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

//void WinMultiPanel::paintEvent(QPaintEvent *event)
//{
//    //QWidget::paintEvent(event);
//    QPainter painter(this);

//    if(m_pressed){
//        event->accept();
//        painter.fillRect(this->rect(), QColor(0,255,0));
//        qDebug()<<"painter 1"<<this->rect();
//    }else{
//        painter.fillRect(this->rect(), QColor(1,16,177));
//        qDebug()<<"painter"<<this->rect();
//    }
//}

bool WinMultiPanel::eventFilter(QObject * watched, QEvent * event)
{
    qDebug()<<"event"<<event;
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button() == Qt::LeftButton && !m_pressed){
            m_pressed = true;
            QWidget *widget = static_cast<QWidget *>(watched);
            widget->setGeometry(widget->x()+1, widget->y()+1,widget->width(),widget->height());
            m_maskView->setParent(widget);
            //m_maskView->setGeometry(widget->geometry());
            m_maskView->setGeometry(0,0,widget->width(),widget->height());
            qDebug()<<m_maskView->rect()<<widget->rect();
            m_maskView->setVisible(true);
            qDebug()<<"press";
            return true;
        }
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button() == Qt::LeftButton && m_pressed){
            m_pressed = false;
            QWidget *widget = static_cast<QWidget *>(watched);
            widget->setGeometry(widget->x()-1, widget->y()-1,widget->width(),widget->height());
            m_maskView->setVisible(false);
            qDebug()<<"release";
            return true;
        }
    }else if(event->type() == QEvent::MouseMove){
        QWidget *widget = static_cast<QWidget *>(watched);
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(widget->rect().contains(mouseEvent->pos())){
            if(!m_pressed){
                m_pressed = true;
                QWidget *widget = static_cast<QWidget *>(watched);
                widget->setGeometry(widget->x()+1, widget->y()+1,widget->width(),widget->height());
                m_maskView->setParent(widget);
                //m_maskView->setGeometry(widget->geometry());
                m_maskView->setGeometry(0,0,widget->width(),widget->height());
                qDebug()<<m_maskView->rect()<<widget->rect();
                m_maskView->setVisible(true);
                qDebug()<<"press";
                return true;
            }
        }else{
            if(m_pressed){
                m_pressed = false;
                QWidget *widget = static_cast<QWidget *>(watched);
                widget->setGeometry(widget->x()-1, widget->y()-1,widget->width(),widget->height());
                m_maskView->setVisible(false);
                qDebug()<<"release";
                return true;
            }
        }
        qDebug()<<"move";
        return true;
    }else if(event->type() == QEvent::Paint && m_pressed){
        QWidget *widget = static_cast<QWidget *>(watched);
        qDebug()<<"paint 1"<<widget->rect();
//        QWidget::eventFilter(watched, event);
//        qDebug()<<"paint 2";
//        QWidget *widget = static_cast<QWidget *>(watched);
//        qDebug()<<"paint 3";
//        QPaintEvent *event = static_cast<QPaintEvent *>(event);
//        qDebug()<<"paint 4";
//        QPainter painter(widget);
//        qDebug()<<"paint 5"<<painter.isActive();
//        painter.fillRect(event->rect(), Qt::red);
//        qDebug()<<"paint 6";
//        event->accept();
    }
    return QWidget::eventFilter(watched, event);
}
