#include <QPalette>
#include <QMouseEvent>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QEvent>
#include <QTimer>

#include "windigitalgroup.h"
#include "windigitaldelegate.h"
#include "./DataModel/modeldigitalgroupchannel.h"

WinDigitalGroup::WinDigitalGroup(quint32 grpIndex, QWidget *parent) :
    m_pressed(false),m_grpIndex(grpIndex),QTableView(parent)
{
    this->setStyleSheet("background-color:rgb(1,16,177);border:0;");//1,16,177

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAutoScroll(false);

    this->setSelectionMode(QAbstractItemView::NoSelection);
    this->horizontalHeader()->setVisible(false);
    this->horizontalHeader()->setHighlightSections(false);
    this->verticalHeader()->setVisible(false);
    this->verticalHeader()->setHighlightSections(false);

    this->setShowGrid(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setMouseTracking(false);

    this->setModel(new ModelDigitalGroupChannel(m_grpIndex,this));
    this->setItemDelegate(new WinDigitalDelegate(this));
}

//void WinDigitalGroup::showEvent(QShowEvent *e)
//{
//    timer->start(500);
//    QTableView::showEvent(e);
//}

//void WinDigitalGroup::hideEvent(QHideEvent *e)
//{
//    timer->stop();
//    QTableView::hideEvent(e);
//}

void WinDigitalGroup::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(event->button() == Qt::LeftButton && index.isValid()){
        m_rect = visualRect(index);
        m_pressed = true;
        update(index);
    }
    QTableView::mousePressEvent(event);
}

void WinDigitalGroup::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    update(indexAt(event->pos()));
    QTableView::mouseReleaseEvent(event);
}

void WinDigitalGroup::mouseMoveEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(index.isValid() && !m_rect.intersects(visualRect(index))){
        m_pressed = false;
        update(indexAt(event->pos()));
    }else{
        m_pressed = true;
        update(indexAt(event->pos()));
    }

    QTableView::mouseMoveEvent(event);
}

QStyleOptionViewItem WinDigitalGroup::viewOptions() const
{
    QStyleOptionViewItem option = QTableView::viewOptions();
    option.backgroundBrush = QBrush(Qt::white);
    if(m_pressed == true){
        option.state |= QStyle::State_Sunken;
    }
    return option;
}
