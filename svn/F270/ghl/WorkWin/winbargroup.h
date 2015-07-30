#ifndef WINBARGROUP_H
#define WINBARGROUP_H

#include <QTableView>

class QRect;
class QTimer;
class WinBarGroup : public QTableView
{
    Q_OBJECT
public:
    explicit WinBarGroup(quint32 grpIndex, QWidget *parent = 0);

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

#endif // WINBARGROUP_H
