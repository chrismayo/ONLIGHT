#include "trendrulerwidget.h"

TrendRulerWidget::TrendRulerWidget(QWidget *parent) :
    QWidget(parent)
{
    m_press = false;
    m_largeScaleNum = 8;
    m_smallScaleNum = 5;
    m_startPoint = -1;
    m_endPoint = -1;
    setMouseTracking(false);
}

TrendRulerWidget::~TrendRulerWidget()
{

}

int TrendRulerWidget::setRulerMoveRange(int startPoint, int endPoint)
{
    if (startPoint == endPoint)
        return 1;
    m_startPoint = startPoint;
    m_endPoint = endPoint;
    return 0;
}

bool TrendRulerWidget::isSelected()
{
    return m_press;
}

void TrendRulerWidget::paintEvent(QPaintEvent *e)
{
    QVector<QLineF> largeScaleLines, smallScaleLines;
    float largescale = (float)rect().height()/(float)m_largeScaleNum;
    float smallscale =  largescale/m_smallScaleNum;
    //绘制尺子背景色 和 透明度
    QPainter painter(this);
    painter.fillRect(0, 0, rect().width(), rect().height(), QBrush(QColor(0x2f,0x2f,0x2f,0x10)));

    //绘制大刻度
    for (int i = 1; i<=m_largeScaleNum; i++)
    {
        largeScaleLines.append(QLineF(QPointF(0, largescale*i), QPointF(rect().width()/2, largescale*i)));
    }
    painter.drawLines(largeScaleLines);

    //绘制小刻度
    for (int i = 1; i<=m_smallScaleNum*m_largeScaleNum; i++)
    {
        smallScaleLines.append(QLineF(QPointF(0, smallscale*i), QPointF(rect().width()/4, smallscale*i)));
    }
    painter.drawLines(smallScaleLines);

    QWidget::paintEvent(e);
}

void TrendRulerWidget::mousePressEvent(QMouseEvent *e)
{
    m_press = true;
    QWidget::mousePressEvent(e);
}

void TrendRulerWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_press = false;
    QWidget::mouseReleaseEvent(e);
}

void TrendRulerWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_startPoint == m_endPoint)  //如果没有设置范围则 不能移动标尺
        return;
     if ( mapTo((QWidget *)parent(), e->pos()).x() <= m_startPoint)
     {
         return;
     }
     if (mapTo((QWidget *)parent(), e->pos()).x() >= m_endPoint)
     {
         move(m_endPoint+5, pos().y());
         return;
     }
     move(mapTo((QWidget *)parent(), e->pos()).x(), pos().y());
    QWidget::mouseMoveEvent(e);
}




