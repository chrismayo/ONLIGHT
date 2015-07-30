#include <QPainter>

#include "winoverviewchandelegate.h"
#include "./GlobalData/cfgGlobalDef.h"

WinOverviewChanDelegate::WinOverviewChanDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),margins(-2,-2,-2,-2)
{
}

void	WinOverviewChanDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if(index.isValid() && index.data(ChannelData).isValid()){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        /**********************背景*********************/
        QRectF rect(option.rect.marginsAdded(margins));
        if(option.state & QStyle::State_Sunken && option.state & QStyle::State_HasFocus){
            rect.moveTo(rect.x() + 1, rect.y() + 1);
        }
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QBrush(QColor(240,240,240)));
        painter->drawRoundedRect(rect,5,5);

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

        /*******************值************************/
        QRectF valRect(rect);
        valRect.adjust(5,10,-5,-10);
        QFont font = option.font;
        font.setPixelSize(valRect.height()/5);
        painter->setFont(font);
        painter->setPen(Qt::gray);
        painter->drawText(valRect, Qt::AlignTop | Qt::AlignRight, index.data(ChannelTag).toString());

        font.setPixelSize(valRect.height()/3);
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(valRect, Qt::AlignLeft | Qt::AlignBottom, index.data(ChannelData).toString());

        font.setPixelSize(valRect.height()/5);
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(valRect, Qt::AlignRight | Qt::AlignBottom, index.data(ChannelUnit).toString());

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

QSize	WinOverviewChanDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & /*index*/) const
{
    return option.rect.size();
}

/*
 * 功能：
 *          去掉系统自带的toolTip
 */
bool WinOverviewChanDelegate::helpEvent(QHelpEvent */*event*/,
                           QAbstractItemView */*view*/,
                           const QStyleOptionViewItem &/*option*/,
                           const QModelIndex &/*index*/)
{
    return false;
}
