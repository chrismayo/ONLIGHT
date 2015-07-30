#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QLinearGradient>

#include "GlobalData/cfgGlobalDef.h"
#include "windigitaldelegate.h"

WinDigitalDelegate::WinDigitalDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),margins(-6,-6,-6,-6)
{
}


void	WinDigitalDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
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

        /*****************绘制色卡******************/
        QRectF colorRect(rect);
        colorRect.setLeft(rect.right()-25);
        painter->setBrush(QBrush(index.data(ChannelColor).value<QColor>()));
        painter->drawRoundedRect(colorRect,5,5);

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

        /***************擦除多余色卡******************/
        colorRect.setRight(colorRect.left() + 2);
        painter->eraseRect(colorRect);

        /*****************测量值*********************/
        QRectF valRect(rect);
        valRect.setHeight(valRect.height()/3);
        valRect.moveTop(valRect.bottom());
        valRect.setRight(colorRect.left() - 3);
        QFont font = option.font;
        font.setFamily(font.defaultFamily());
        font.setPixelSize(valRect.height() - 3);
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(valRect,Qt::AlignVCenter,QString::number(index.data(ChannelData).toFloat(),'f',4));//index.data(ChannelData).toString()

        /*****************标记************************/
        QRectF tagRect(valRect);
        tagRect.moveBottom(tagRect.top());
        tagRect.setTop(tagRect.top() + 10);
        font.setPixelSize(tagRect.height()/2);
        painter->setFont(font);
        painter->setPen(Qt::gray);
        painter->drawText(tagRect,Qt::AlignRight,index.data(ChannelTag).toString());//Qt::AlignVCenter|

        /******************单位***********************/
        QRectF unitRect(valRect);
        unitRect.moveTop(unitRect.bottom());
        unitRect.setRight(unitRect.right() - 15);
        font.setPixelSize(tagRect.height()/2 - 5);
        painter->setFont(font);
        painter->setPen(Qt::black);
        painter->drawText(unitRect,Qt::AlignRight,index.data(ChannelUnit).toString());//Qt::AlignVCenter|

        /***************警报配置*************/
        QRadialGradient redLight, greenLight;
        QPen redPen(QColor(255, 0, 0, 40),1),greenPen(QColor(0, 255, 0, 140),1);
        QRectF alarmRect(unitRect);
        alarmRect.setHeight(alarmRect.height()/3);
        alarmRect.setWidth(alarmRect.height());
        qreal cx = 0.445 * alarmRect.width(), cy=0.527955 * alarmRect.height(), fx = 0.404545 * alarmRect.width(), fy=0.381*alarmRect.height();
        greenLight.setColorAt(0,QColor(255,255,255,255));
        greenLight.setColorAt(1,QColor(0, 255, 0, 223));
        greenLight.setRadius(alarmRect.height() * 0.88);
        redLight.setColorAt(0,QColor(255,255,255,255));
        redLight.setColorAt(1,QColor(255, 0, 0, 223));
        redLight.setRadius(alarmRect.height() * 0.88);
        font.setPixelSize(alarmRect.height()/3*2);
        painter->setFont(font);

        /**************电平****************/
        QRectF alarm1Rect(alarmRect);
        alarm1Rect.moveTop(alarm1Rect.bottom());
        alarm1Rect.moveLeft(unitRect.center().x());
        greenLight.setCenter(alarm1Rect.x() + cx, alarm1Rect.y() + cy);
        greenLight.setFocalPoint(alarm1Rect.x() + fx, alarm1Rect.y() + fy);
        painter->setPen(greenPen);
        painter->setBrush(greenLight);
        painter->drawEllipse(alarm1Rect);
        painter->setPen(Qt::gray);
        painter->drawText(alarm1Rect, Qt::AlignCenter,"H");

        QRectF alarm2Rect(alarm1Rect);
        alarm2Rect.moveLeft(alarm2Rect.right() + 5);
        redLight.setCenter(alarm2Rect.x() + cx, alarm2Rect.y() + cy);
        redLight.setFocalPoint(alarm2Rect.x() + fx, alarm2Rect.y() + fy);
        painter->setPen(redPen);
        painter->setBrush(redLight);
        painter->drawEllipse(alarm2Rect);
        painter->setPen(Qt::gray);
        painter->drawText(alarm2Rect, Qt::AlignCenter,"L");

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

QSize	WinDigitalDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & /*index*/) const
{
    return option.rect.size();
}

/*
 * 功能：
 *          去掉系统自带的toolTip
 */
bool WinDigitalDelegate::helpEvent(QHelpEvent */*event*/,
                           QAbstractItemView */*view*/,
                           const QStyleOptionViewItem &/*option*/,
                           const QModelIndex &/*index*/)
{
    return false;
}
