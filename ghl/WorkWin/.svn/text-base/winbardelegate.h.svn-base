#ifndef WINBARDELEGATE_H
#define WINBARDELEGATE_H

#include <QAbstractItemDelegate>

class WinBarDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit WinBarDelegate(QObject *parent = 0);
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

#endif // WINBARDELEGATE_H
