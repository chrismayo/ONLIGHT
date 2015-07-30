#include "trendrecordpaper.h"

TrendRecordPaper::TrendRecordPaper(QWidget *parent, int index) :
    QWidget(parent), m_index(index)
{
}

TrendRecordPaper::~TrendRecordPaper()
{
}

void TrendRecordPaper::paintEvent(QPaintEvent *e)
{
    QPen backPen;
    backPen.setStyle(Qt::SolidLine);
    backPen.setColor(Qt::black);
    //参数设置
     int width = rect().width();
     int height = rect().height();
     QPainter painter(this);
     //背景绘制
     painter.fillRect(0, 0, rect().width(), rect().height(), QBrush(Qt::white));
     painter.setPen(backPen);

     qreal divY = (qreal) (height-TOP_SPACE-BOTTOM_SPACE )/DIV_V;
     int divX = (width)/DIV_H;

//     //水平网格线
     for (int i=0; i<DIV_H; i++)
     {
         painter.drawLine(QPointF(0, TOP_SPACE+(divY*i)), QPointF(width, TOP_SPACE+(divY*i)));
     }
     for (int j = 0; j<DIV_H; j++)
     {
         painter.drawLine(QPoint(divX*j, TOP_SPACE), QPoint(divX*j, height-BOTTOM_SPACE));
     }

     painter.drawText(QPointF(QPoint(12,24)), QString::number(m_index));
     QWidget::paintEvent(e);
}

