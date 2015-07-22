#include <QTableView>
#include <QHeaderView>
#include <QTimer>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPalette>
#include <QPainter>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "winoverview.h"
#include "winoverviewchandelegate.h"
#include "winoverviewgroupdelegate.h"
#include "./DataModel/modeldigitalgroupchannel.h"

WinOverView::WinOverView(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QStackedLayout();
    m_allChannelView = new WinChannelView();
    m_allGroupView = new WinChannelView();
    //m_allChannelView->setStyleSheet("background-color:rgb(255,0,0);");
    //m_allGroupView->setStyleSheet("background-color:rgb(0,0,255);");
    m_allChannelView->setItemDelegate(new WinOverviewChanDelegate(m_allChannelView));
    ModelDigitalGroupChannel *model = new ModelDigitalGroupChannel(0, this);
    m_allChannelView->setModel(model);
    m_allGroupView->setItemDelegate(new WinOverviewGroupDelegate(m_allGroupView));
    m_allGroupView->setModel(model);

    QFrame *frame = new QFrame(this);
    frame->resize(this->size());
    QVBoxLayout *verticalLayout =new QVBoxLayout(frame);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    horizontalLayout->addWidget(new QPushButton("返回"));
    horizontalLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    horizontalLayout->addWidget(new QPushButton("<"));
    horizontalLayout->addWidget(new QLabel("Group 1"));
    horizontalLayout->addWidget(new QPushButton(">"));
    horizontalLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    horizontalLayout->addWidget(new QPushButton("趋势"));
    verticalLayout->addLayout(horizontalLayout);

     WinChannelView *channelView = new WinChannelView(this);
     channelView->setItemDelegate(new WinOverviewChanDelegate(m_allChannelView));
     channelView->setModel(new ModelDigitalGroupChannel(1, this) );
    verticalLayout->addWidget(channelView);

   m_layout->addWidget(frame);


    m_layout->addWidget(m_allGroupView);
    m_layout->addWidget(m_allChannelView);
    m_layout->setCurrentIndex(1);

    this->setLayout(m_layout);
    connect(m_allGroupView,SIGNAL(clicked(QModelIndex)),this,SLOT(slotSwitchFrame(QModelIndex )));
}

void WinOverView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(e->rect(), QColor(1,16,177));
    QWidget::paintEvent(e);
}

void WinOverView::slotSwitchFrame(QModelIndex index)
{
    if(index.isValid()){
        m_layout->setCurrentIndex(0);
    }
}

WinOverView::WinChannelView::WinChannelView(QWidget *parent):
    QTableView(parent)
{
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
    this->setStyleSheet("background-color:rgb(0,0,0,0); border:0;");
}

void WinOverView::WinChannelView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(event->button() == Qt::LeftButton && index.isValid()){
        m_rect = visualRect(index);
        m_pressed = true;
        update(index);
    }
    QTableView::mousePressEvent(event);
}

void WinOverView::WinChannelView::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    update(indexAt(event->pos()));
    QTableView::mouseReleaseEvent(event);
}

void WinOverView::WinChannelView::mouseMoveEvent(QMouseEvent *event)
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

QStyleOptionViewItem WinOverView::WinChannelView::viewOptions() const
{
    QStyleOptionViewItem option = QTableView::viewOptions();
    option.backgroundBrush = QBrush(Qt::white);
    if(m_pressed == true){
        option.state |= QStyle::State_Sunken;
    }
    return option;
}
