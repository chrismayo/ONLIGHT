#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QLinearGradient>

#include "GlobalData/cfgGlobalDef.h"
#include "winbardelegate.h"

WinBarDelegate::WinBarDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),margins(-3,-6,-3,-6)
{
}

void WinBarDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if(index.isValid() && index.data(ChannelData).isValid()){
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        /**************配置*****************/
        QRectF rect(option.rect.marginsAdded(margins));
        if(option.state & QStyle::State_Sunken && option.state & QStyle::State_HasFocus){
            rect.moveTo(rect.x() + 1, rect.y() + 1);
        }
        QRectF topRect(rect);
        topRect.setHeight(rect.height()/6);
        QFont font = option.font;
        font.setFamily(font.defaultFamily());

        /*****************色卡*****************/
        QRectF colorRect(topRect);
        colorRect.setHeight(topRect.height()/5 * 3);
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QColor(index.data(ChannelColor).value<QColor>()));
        painter->drawRoundedRect(colorRect,5,5);

        /****************头部背景色**************/
        QRectF headRect(topRect);
        headRect.setTop(colorRect.center().y());
        painter->setBrush(QBrush(QColor(240,240,240)));
        painter->drawRect(headRect);

        /******************底部背景色*******************/
        QRectF bottomRect(rect);
        bottomRect.setTop(topRect.bottom() + 2);
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QBrush(QColor(240,240,240)));
        painter->drawRect(bottomRect);

        /******************色柱********************/
        QRectF barRect(bottomRect);
        quint8 base = index.data(ChannelBarBase).toUInt();
        qreal mesureVal = index.data(ChannelData).toDouble();
        qreal rangeUpper = index.data(ChannelDispUpper).toDouble();
        qreal rangeDowner = index.data(ChannelDispDowner).toDouble();
        if(mesureVal >= 0){
            barRect.setTop(barRect.top() + barRect.height()/2 * (1 - mesureVal/rangeUpper));
        }else if(mesureVal < 0){
            barRect.setTop(barRect.top() + barRect.height()/2 * (1 + mesureVal/rangeDowner));
        }
        if(base == 1){
            barRect.setBottom(bottomRect.center().y());
        }else if(base == 2){
            barRect.setBottom(bottomRect.top());
        }
        painter->setPen(QColor(0,0,0,0));
        painter->setBrush(QColor(index.data(ChannelColor).value<QColor>()));
        painter->drawRect(barRect);

        /****************光泽效果*****************/
        QLinearGradient skinColor(rect.topLeft(),rect.topRight());
        skinColor.setColorAt(0,QColor(255,255,255,0));
        skinColor.setColorAt(0.09,QColor(255,255,255,0));
        skinColor.setColorAt(0.1,QColor(255,255,255,200));
        skinColor.setColorAt(0.13,QColor(255,255,255,200));
        skinColor.setColorAt(0.14,QColor(255,255,255,80));
        skinColor.setColorAt(0.50,QColor(0,0,0,20));
        skinColor.setColorAt(0.75,QColor(0,0,0,10));
        skinColor.setColorAt(0.76,QColor(255,255,255,30));
        skinColor.setColorAt(0.95,QColor(255,255,255,150));
        skinColor.setColorAt(0.96,QColor(255,255,255,0));
        skinColor.setColorAt(1,QColor(255,255,255,0));
        painter->setPen(QPen(QColor(200,230,255,0)));
        painter->setBrush(skinColor);
        painter->drawRect(rect);

        /*****************刻度*********************/
        qreal baseX = bottomRect.right();
        qreal baseY = bottomRect.top();
        qreal len = bottomRect.width()/8;
        quint8 count = index.data(ChannelBarDiv).toUInt();
        qreal span = bottomRect.height()/count;
        painter->setPen(Qt::black);
        painter->setBrush(QBrush(QColor(0,0,0,0)));
        for(quint8 i=1; i<count; ++i){
            painter->drawLine(baseX - len, baseY + i*span, baseX, baseY + i*span);
        }

        /**************量程*****************/
        QRectF valRect(bottomRect);
        valRect.setHeight(span);
        font.setPixelSize(valRect.height()/2);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black,1));
        painter->drawText(valRect,QString::number(rangeUpper,'f',4));
        valRect.moveBottom(bottomRect.bottom());
        painter->drawText(valRect,Qt::AlignBottom,QString::number(rangeDowner,'f',4));

        /**************测量值*********************/
        valRect.moveBottom(barRect.top());
        if(valRect.top() < baseY + span){
            valRect.moveTop(baseY + span);
        }else if(valRect.bottom() > bottomRect.bottom() - 2 * span){
            valRect.moveBottom(bottomRect.bottom() - 2 * span);
        }
        painter->drawText(valRect,Qt::AlignBottom|Qt::AlignHCenter,QString::number(mesureVal,'f',4));

        /*******************单位***********************/
        valRect.moveTop(valRect.bottom());
        valRect.setRight(baseX - len);
        //painter->setPen(QColor(100,100,100));
        painter->drawText(valRect,Qt::AlignRight|Qt::AlignTop,index.data(ChannelUnit).toString());

        /****************标记********************/
        font.setPixelSize(headRect.height()/2);
        painter->setFont(font);
        painter->setPen(QColor(100,100,100));
        painter->drawText(headRect,Qt::AlignCenter,index.data(ChannelTag).toString());

        /*****************擦除头尾连接**********************/
        painter->setBrush(QBrush(QColor(0,0,0,0)));
        painter->setPen(QPen(Qt::black,1));
        painter->drawRect(bottomRect);
        painter->eraseRect(QRectF(topRect.bottomLeft(), bottomRect.topRight()));

        /*********************按压效果*************************/
        if(option.state & QStyle::State_Sunken && option.state & QStyle::State_HasFocus){
            painter->setPen(QPen(QColor(0,0,255,100),3));
            painter->setBrush(QBrush(QColor(180,180,180,50)));
            painter->drawRoundedRect(rect,6,6);
        }

        painter->restore();
    }
}

QSize WinBarDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & /*index*/) const
{
    return option.rect.size();
}

/*
 * 功能：
 *      去掉系统自带的toolTip
 */
bool WinBarDelegate::helpEvent(QHelpEvent */*event*/,
                           QAbstractItemView */*view*/,
                           const QStyleOptionViewItem &/*option*/,
                           const QModelIndex &/*index*/)
{
    return false;
}
