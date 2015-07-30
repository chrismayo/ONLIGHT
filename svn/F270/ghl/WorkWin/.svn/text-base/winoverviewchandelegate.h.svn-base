#ifndef WINOVERVIEWCHANDELEGATE_H
#define WINOVERVIEWCHANDELEGATE_H

#include <QAbstractItemDelegate>

class WinOverviewChanDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit WinOverviewChanDelegate(QObject *parent = 0);

    virtual void	paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

    virtual QSize	sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

    bool helpEvent(QHelpEvent *event,
                               QAbstractItemView *view,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index);
signals:

public slots:

private:
    QMargins margins;
};

#endif // WINOVERVIEWCHANDELEGATE_H
