#include "trendhandwritingpaper.h"

TrendHandWritingPaper::TrendHandWritingPaper(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

TrendHandWritingPaper::~TrendHandWritingPaper()
{

}

QRectF TrendHandWritingPaper::boundingRect() const
{
        return QRectF(0, 0, 12960, 900);
}

QPainterPath TrendHandWritingPaper::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void TrendHandWritingPaper::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(QPointF(QPoint(0.0,100.0)), QString("hand paper&&&&&&&&&&&&"));
}
