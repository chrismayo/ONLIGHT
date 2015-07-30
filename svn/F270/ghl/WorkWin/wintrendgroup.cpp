#include "wintrendgroup.h"

WinTrendGroup::WinTrendGroup(QWidget *parent, quint8 index) :
    QWidget(parent),
    m_grpIndex(index)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

WinTrendGroup::~WinTrendGroup()
{
    release();
}
void WinTrendGroup::initialize()
{
    p_vLayout = new QVBoxLayout();
    p_gLayout = new QGridLayout();
    p_hLayout = new QHBoxLayout();

    p_detailTrend = new TrendDetailWidget();
    p_digitalWidgt = new TrendDigitalWidget();
    p_overviewWidget = new TrendOverviewWidget();
    p_handWriting = new TrendHandWritingInfor();
    p_ruler = new TrendRulerWidget();
    setMouseTracking(false);
}

void WinTrendGroup::release()
{
    delete p_ruler;
    delete p_detailTrend;
    delete p_digitalWidgt;
    delete p_overviewWidget;
    delete p_hLayout;
    delete p_vLayout;
    delete p_gLayout;
    delete p_handWriting;
}

void WinTrendGroup::setUserDefineStyle()
{
    p_overviewWidget->hide();
    p_handWriting->hide();
}

void WinTrendGroup::setUserDefineContent()
{

}

void WinTrendGroup::setWinLayout()
{
    p_hLayout->addWidget(p_detailTrend);
    p_hLayout->addWidget(p_ruler);
    p_vLayout->addWidget(p_overviewWidget);
    p_vLayout->addLayout(p_hLayout);
    p_gLayout->addLayout(p_vLayout, 0, 0);
    p_gLayout->addWidget(p_digitalWidgt,0,1);

    p_gLayout->setContentsMargins(0,0,0,0);
    p_gLayout->setSpacing(0);
    p_gLayout->setMargin(0);
    p_vLayout->setContentsMargins(0,0,0,0);
    p_vLayout->setSpacing(0);
    p_vLayout->setMargin(0);
    p_hLayout->setContentsMargins(0,0,0,0);
    p_hLayout->setSpacing(0);
    p_hLayout->setMargin(0);

    setLayout(p_gLayout);
}
void WinTrendGroup::sigAndSlotConnect()
{
    connect(p_overviewWidget, SIGNAL(sigHide()), this, SLOT(slotHideOverViewTrend()));
    connect(p_detailTrend, SIGNAL(sigOverviewTrend()), this, SLOT(slotShowQverViewTrend()));
    connect(p_detailTrend, SIGNAL(sigInforHand()), this, SLOT(slotShowHandWritingWidget()));
}

void WinTrendGroup::slotHideOverViewTrend()
{
    p_overviewWidget->hide();
}

void WinTrendGroup::slotShowQverViewTrend()
{
    p_overviewWidget->show();
}

void WinTrendGroup::slotShowHandWritingWidget()
{
    p_handWriting->show();
}

void WinTrendGroup::dragDigitalWidget(int state)
{
    p_gLayout->removeItem(p_vLayout);
    p_gLayout->removeWidget(p_digitalWidgt);
    switch (state)
    {
    case 1:   //left
        p_digitalWidgt->setPosition(TrendDigitalWidget::LEFT);
        p_digitalWidgt->changeLayout();
        p_gLayout->addLayout(p_vLayout, 0, 1);
        p_gLayout->addWidget(p_digitalWidgt, 0, 0);
        p_gLayout->setColumnMinimumWidth(0, rect().width()*0.1);
        p_gLayout->setColumnMinimumWidth(1, rect().width()*0.9);
        p_gLayout->setRowMinimumHeight(0, 0);
        p_gLayout->setRowMinimumHeight(1,0);
        break;
    case 2:   //down
        p_digitalWidgt->setPosition(TrendDigitalWidget::DOWN);
        p_digitalWidgt->changeLayout();
        p_gLayout->addLayout(p_vLayout, 0, 0);
        p_gLayout->addWidget(p_digitalWidgt, 1, 0);
        p_gLayout->setColumnMinimumWidth(0, 0);
        p_gLayout->setColumnMinimumWidth(1, 0);
        p_gLayout->setRowMinimumHeight(0, rect().height()*0.85);
        p_gLayout->setRowMinimumHeight(1,rect().height()*0.15);
        break;
    case 3:   //right
        p_digitalWidgt->setPosition(TrendDigitalWidget::RIGHT);
        p_digitalWidgt->changeLayout();
        p_gLayout->addLayout(p_vLayout, 0, 0);
        p_gLayout->addWidget(p_digitalWidgt, 0, 1);
        p_gLayout->setColumnMinimumWidth(0, rect().width()*0.9);
        p_gLayout->setColumnMinimumWidth(1, rect().width()*0.1);
        p_gLayout->setRowMinimumHeight(0, 0);
        p_gLayout->setRowMinimumHeight(1,0);
        break;
    case 4:   //up
        p_digitalWidgt->setPosition(TrendDigitalWidget::UP);
        p_digitalWidgt->changeLayout();
        p_gLayout->addLayout(p_vLayout, 1, 0);
        p_gLayout->addWidget(p_digitalWidgt, 0, 0);
        p_gLayout->setColumnMinimumWidth(0, 0);
        p_gLayout->setColumnMinimumWidth(1, 0);
        p_gLayout->setRowMinimumHeight(0, rect().height()*0.15);
        p_gLayout->setRowMinimumHeight(1,rect().height()*0.85);
        break;
    default:
        break;
    }
    p_ruler->setRulerMoveRange(p_detailTrend->x(), p_detailTrend->width());
}
void WinTrendGroup::resizeEvent(QResizeEvent *e)
{
    switch (p_digitalWidgt->getPosition())
    {
    case TrendDigitalWidget::LEFT:   //left
        p_gLayout->setColumnMinimumWidth(0, rect().width()*0.1);
        p_gLayout->setColumnMinimumWidth(1, rect().width()*0.9);
        p_gLayout->setRowMinimumHeight(0, 0);
        p_gLayout->setRowMinimumHeight(1,0);
        break;
    case TrendDigitalWidget::DOWN:   //down
        p_gLayout->setColumnMinimumWidth(0, 0);
        p_gLayout->setColumnMinimumWidth(1, 0);
        p_gLayout->setRowMinimumHeight(0, rect().height()*0.85);
        p_gLayout->setRowMinimumHeight(1,rect().height()*0.15);
        break;
    case TrendDigitalWidget::RIGHT:   //right
        p_gLayout->setColumnMinimumWidth(0, rect().width()*0.9);
        p_gLayout->setColumnMinimumWidth(1,  rect().width()*0.1);
        p_gLayout->setRowMinimumHeight(0, 0);
        p_gLayout->setRowMinimumHeight(1,0);
        break;
    case TrendDigitalWidget::UP:   //up
        p_gLayout->setColumnMinimumWidth(0, 0);
        p_gLayout->setColumnMinimumWidth(1, 0);
        p_gLayout->setRowMinimumHeight(0, rect().height()*0.15);
        p_gLayout->setRowMinimumHeight(1,rect().height()*0.85);
        break;
    default:
        break;
    }

    p_detailTrend->setMinimumWidth(rect().width()*0.9*12/13);
    p_detailTrend->setMaximumHeight(rect().height());
    p_ruler->setMinimumWidth(p_detailTrend->width()/13);
    p_ruler->setMaximumHeight(p_detailTrend->height());
    p_ruler->setRulerMoveRange(p_detailTrend->x(), p_detailTrend->width());
    p_overviewWidget->setFixedHeight(rect().height()*0.35);
    p_overviewWidget->setLayoutSize();
    p_handWriting->resize(this->size());
    QWidget::resizeEvent(e);
}

void WinTrendGroup::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void WinTrendGroup::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}

void WinTrendGroup::mouseMoveEvent(QMouseEvent *e)
{
    if (p_digitalWidgt->getIsPressed())
    {
        if (e->pos().x() < rect().width()*0.25) //left
        {
            dragDigitalWidget(1);
        }
        else if (e->pos().x() > rect().width()*0.75) //right
        {
            dragDigitalWidget(3);
        }
        else if (e->pos().y() < rect().height()*0.25) //top
        {
            dragDigitalWidget(4);
        }
        else if (e->pos().y() > rect().height() * 0.75)//down
        {
            dragDigitalWidget(2);
        }

    }
    QWidget::mouseMoveEvent(e);
}
