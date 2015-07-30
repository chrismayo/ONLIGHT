#include "trenddigitalitem.h"

TrendDigitalItem::TrendDigitalItem(QLabel *parent) :
    QLabel(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
//    resize(600,400);
}

TrendDigitalItem::~TrendDigitalItem()
{
    release();
}

void TrendDigitalItem::paintEvent(QPaintEvent *e)
{
    p_colorMark->setFixedWidth(rect().width()*0.1);
    p_colorMark->move(0,0);

    QLabel::paintEvent(e);
}

void TrendDigitalItem::mousePressEvent(QMouseEvent *e)
{
    this->setFocus(Qt::OtherFocusReason);
    QWidget::mousePressEvent(e);
}

void TrendDigitalItem::focusInEvent(QFocusEvent *e)
{
    setStyleSheet("border: 1px solid;background-color: yellow");
    QWidget::focusInEvent(e);
}

void TrendDigitalItem::focusOutEvent(QFocusEvent *e)
{
    setStyleSheet("border: 1px solid;background-color: green");
    QWidget::focusOutEvent(e);
}


void TrendDigitalItem::initialize()
{
    p_colorMark = new QLabel();
    p_gLayout = new QGridLayout();
    p_hLayout = new QHBoxLayout();
}

void TrendDigitalItem::release()
{
    delete p_colorMark;
    delete p_gLayout;
    delete p_hLayout;
}

void TrendDigitalItem::setUserDefineStyle()
{
    p_colorMark->setStyleSheet("background-color: red;");
    setStyleSheet("border: 1px solid;background-color: green");
}

void TrendDigitalItem::setUserDefineContent()
{
}

void TrendDigitalItem::setWinLayout()
{
    p_hLayout->addWidget(p_colorMark);
    p_hLayout->addLayout(p_gLayout);

    p_hLayout->setContentsMargins(0,0,0,0);
    p_hLayout->setSpacing(0);
    p_hLayout->setMargin(0);
    setLayout(p_hLayout);
}

void TrendDigitalItem::sigAndSlotConnect()
{
}
