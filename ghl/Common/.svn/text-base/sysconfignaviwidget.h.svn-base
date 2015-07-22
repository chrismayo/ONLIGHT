#ifndef SYSCONFIGNAVIWIDGET_H
#define SYSCONFIGNAVIWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>

class SysConfigNaviWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit SysConfigNaviWidget(QPushButton *parent = 0, int index = 0);
    ~SysConfigNaviWidget();
signals:
    void sigClick(int index);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
public slots:

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    int m_index;

};

#endif // SYSCONFIGNAVIWIDGET_H
