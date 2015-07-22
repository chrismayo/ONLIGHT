#include <QPainter>
#include "winoverviewgroupdelegate.h"
#include "./GlobalData/cfgGlobalDef.h"

WinOverviewGroupDelegate::WinOverviewGroupDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),margins(-2,-2,-2,-2)
{
}

void WinOverviewGroupDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if(index.isValid() && index.data(ChannelData).isValid()){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        /***************绘制背景色***************/
        QRectF rect(option.rect.marginsAdded(margins));
        if(option.state & QStyle::State_Sunken && option.state & QStyle::State_HasFocus){
            rect.moveTo(rect.x() + 1, rect.y() + 1);
        }
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QBrush(QColor(240,240,240)));
        painter->drawRoundedRect(rect,5,5);


        /*******************三角标记********************/
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QBrush(QColor(255,142,0)));
        QPointF points[4];
        points[0] = QPointF(rect.right() - 5, rect.top());
        points[1] = QPointF(rect.right(), rect.top() + 5);
        points[2] = QPointF(rect.right(), rect.top() + rect.height()/5);
        points[3] = QPointF(rect.right() - rect.height()/5, rect.top());
        painter->drawPolygon(points,4);
        QRectF chordRect(rect.right() - 10, rect.top(), 10, 10);
        painter->drawChord(chordRect, 0*16, 90*16);

        /****************绘制光泽效果****************/
        QLinearGradient skinColor(rect.topLeft(),rect.bottomLeft());
        skinColor.setColorAt(0,QColor(255,255,255,160));
        skinColor.setColorAt(0.04,QColor(255,255,255,160));
        skinColor.setColorAt(0.05,QColor(255,255,255,100));
        skinColor.setColorAt(0.48,QColor(0,0,0,5));
        skinColor.setColorAt(0.49,QColor(100,100,100,20));
        skinColor.setColorAt(0.97,QColor(255,255,255,0));
        skinColor.setColorAt(0.98,QColor(255,255,255,50));
        skinColor.setColorAt(1,QColor(255,255,255,150));
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QBrush(skinColor));
        painter->drawRoundedRect(rect, 5, 5);

        /*********************组名**********************/
        QFont font =option.font;
        font.setPixelSize(rect.height()/3);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawText(rect,Qt::AlignCenter, index.data(ChannelData).toString());

        /*********************按压效果**********************/
        if(option.state & QStyle::State_Sunken && option.state & QStyle::State_HasFocus){
            painter->setPen(QPen(QColor(0,0,255,100),3));
            painter->setBrush(QBrush(QColor(180,180,180,50)));
            painter->drawRoundedRect(rect,6,6);
        }
        //qDebug("state: %X, flag:%X",option.state, index.flags());
        painter->restore();
    }
}

QSize WinOverviewGroupDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & /*index*/) const
{
    return option.rect.size();
}

/*
 * 功能：
 *          去掉系统自带的toolTip
 */
bool WinOverviewGroupDelegate::helpEvent(QHelpEvent */*event*/,
                           QAbstractItemView */*view*/,
                           const QStyleOptionViewItem &/*option*/,
                           const QModelIndex &/*index*/)
{
    return false;
}
