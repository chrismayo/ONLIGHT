#include "trenddigitalwidget.h"

TrendDigitalWidget::TrendDigitalWidget(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

TrendDigitalWidget::~TrendDigitalWidget()
{
    release();
}

void TrendDigitalWidget::initialize()
{
    m_digitalWidgetNum = 20;
    m_pos = RIGHT;
    m_isPressed = false;

    p_gLayout = new QGridLayout();
    p_digitalWidgets = new QVector<TrendDigitalItem *>(20, nullptr);

    for (int i = 0; i<m_digitalWidgetNum; ++i)
    {
        p_digitalWidgets->operator [](i) = new TrendDigitalItem();
    }
}
void TrendDigitalWidget::release()
{
    for (int i = 0; i<m_digitalWidgetNum; ++i)
    {
        delete p_digitalWidgets->operator [](i);
    }
    delete p_digitalWidgets;
    delete p_gLayout;
}

void TrendDigitalWidget::setUserDefineStyle()
{

}

void TrendDigitalWidget::setUserDefineContent()
{

}

void TrendDigitalWidget::setWinLayout()
{
    for(int i = 0; i<m_digitalWidgetNum; ++i)
        p_gLayout->addWidget(p_digitalWidgets->at(i), i, 0);

    p_gLayout->setContentsMargins(0,0,0,0);
    p_gLayout->setSpacing(0);
    p_gLayout->setMargin(0);
    setLayout(p_gLayout);
}

void TrendDigitalWidget::sigAndSlotConnect()
{

}

void TrendDigitalWidget::changeLayout()
{
    for (int i = 0; i<m_digitalWidgetNum; ++i)
        p_gLayout->removeWidget(p_digitalWidgets->at(i));

    if (m_pos == UP || m_pos == DOWN) //当前为列表模式，改为表格模式
    {
        for(int i = 0; i<m_digitalWidgetNum; i=i+2)
        {
            p_gLayout->addWidget(p_digitalWidgets->at(i), 0, i);
            p_gLayout->addWidget(p_digitalWidgets->at(i+1), 1, i);
        }
    }
    else //当前为表格模式， 改为列表模式
    {
        for(int i = 0; i<m_digitalWidgetNum; ++i)
            p_gLayout->addWidget(p_digitalWidgets->at(i), i, 0);
    }
}

void TrendDigitalWidget::setPosition(TrendDigitalWidget::Position pos)
{
    m_pos = pos;
}

int TrendDigitalWidget::getPosition()
{
    return m_pos;
}

bool TrendDigitalWidget::getIsPressed()
{
    return m_isPressed;
}

void TrendDigitalWidget::mousePressEvent(QMouseEvent *e)
{
    m_isPressed = true;
    QWidget::mousePressEvent(e);
}

void TrendDigitalWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_isPressed = false;
    QWidget::mouseReleaseEvent(e);
}
