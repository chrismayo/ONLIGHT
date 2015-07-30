#ifndef WINDIGITALDELEGATE_H
#define WINDIGITALDELEGATE_H

#include <QAbstractItemDelegate>

class WinDigitalDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit WinDigitalDelegate(QObject *parent = 0);

    virtual void	paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

    virtual QSize	sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

    bool helpEvent(QHelpEvent *event,
                               QAbstractItemView *view,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index);
signals:

public slots:

private:
//    QStyleOptionViewItem setOption(const QStyleOptionViewItem & option, const QModelIndex & index, int role) const;
//    bool drawAlarm1(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    bool drawAlarm2(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    bool drawAlarm3(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    bool drawAlarm4(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    void drawChanName(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    void drawChanUnit(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    void drawMesureValue(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect, const QString text) const;
//    void drawPressRoundedRect(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect) const;
//    void drawChanColor(QPainter * painter, const QStyleOptionViewItem & option, const QRect &rect) const;

private:
    QMargins margins;

};

#endif // WINDIGITALDELEGATE_H
