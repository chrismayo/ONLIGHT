#include <QPalette>
#include <QMouseEvent>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QEvent>
#include <QTimer>

#include "winbargroup.h"
#include "winbardelegate.h"
#include "./DataModel/modelbargroupchannel.h"

WinBarGroup::WinBarGroup(quint32 grpIndex, QWidget *parent) :
    m_pressed(false),m_grpIndex(grpIndex),QTableView(parent)
{
    this->setStyleSheet("background-color:rgb(1,16,177);border:0;");//WinBarGroup{background-color:rgb(1,16,177);}

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

    this->setModel(new ModelBarGroupChannel(m_grpIndex, this));
    this->setItemDelegate(new WinBarDelegate(this));
}

void WinBarGroup::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(event->button() == Qt::LeftButton && index.isValid()){
       m_rect = visualRect(index);
        m_pressed = true;
        update(index);
    }
    QTableView::mousePressEvent(event);
}

void WinBarGroup::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    update(indexAt(event->pos()));
    QTableView::mouseReleaseEvent(event);
}

void WinBarGroup::mouseMoveEvent(QMouseEvent *event)
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

QStyleOptionViewItem WinBarGroup::viewOptions() const
{
    QStyleOptionViewItem option = QTableView::viewOptions();
    option.backgroundBrush = QBrush(Qt::white);
    if(m_pressed == true){
        option.state |= QStyle::State_Sunken;
    }
    return option;
}
