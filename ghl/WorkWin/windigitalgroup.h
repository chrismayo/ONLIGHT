#ifndef WINDIGITALGROUP_H
#define WINDIGITALGROUP_H

#include <QTableView>
#include <QRect>

class WinDigitalGroup : public QTableView
{
    Q_OBJECT
public:
    explicit WinDigitalGroup(quint32 grpIndex, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QStyleOptionViewItem viewOptions() const;

signals:

public slots:

private:
    bool m_pressed;
    QRect m_rect;
    quint32 m_grpIndex;
};

#endif // WINDIGITALGROUP_H
