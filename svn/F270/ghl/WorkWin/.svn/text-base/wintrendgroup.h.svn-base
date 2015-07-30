#ifndef WINTRENDGROUP_H
#define WINTRENDGROUP_H
#include <QDebug>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "./TrendGroupComponent/trenddetailwidget.h"
#include "./TrendGroupComponent/trenddigitalwidget.h"
#include "./TrendGroupComponent/trendoverviewwidget.h"
#include "./TrendGroupComponent/trendhandwritinginfor.h"
#include "./TrendGroupComponent/trendrulerwidget.h"

class WinTrendGroup : public QWidget
{
    Q_OBJECT
public:
    explicit WinTrendGroup(QWidget *parent = 0, quint8 index = 0);
    ~WinTrendGroup();

signals:

public slots:
    void slotHideOverViewTrend();
    void slotShowQverViewTrend();
    void slotShowHandWritingWidget();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

    void dragDigitalWidget(int state); //state == 1 means left, 2 means down, 3 means right, 4 meas up

private:
    quint8 m_grpIndex;      //趋势组索引值
    QVBoxLayout *p_vLayout;   //详细与概要趋势窗体布局器
    QGridLayout *p_gLayout;   //总体布局器；
    QHBoxLayout *p_hLayout;  //尺子与趋势图布局器

    TrendDetailWidget *p_detailTrend;
    TrendDigitalWidget  *p_digitalWidgt;
    TrendOverviewWidget *p_overviewWidget;
    TrendHandWritingInfor *p_handWriting;
    TrendRulerWidget *p_ruler;
};

#endif // WINTRENDGROUP_H
