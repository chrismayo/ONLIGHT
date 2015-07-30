#ifndef TRENDDETAILWIDGET_H
#define TRENDDETAILWIDGET_H

#include <QDebug>
#include <QGraphicsView>
#include <QPushButton>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPoint>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QPainter>

#include "trendrecordpaper.h"
#include "trendhandwritingpaper.h"

#define PB_Show_Time 4000

class TrendDetailWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TrendDetailWidget(QGraphicsView *parent = 0);
    ~TrendDetailWidget();
signals:
    void sigInforHand();                    //手写信息按钮被按下时，发射该信号
    void sigInforChar();                     //信息输入按钮按下时，发射该信号
    void sigOverviewTrend();

public slots:
    void slotPaperPosChange(bool stat);

private slots:
    void slotPBTimerOut();                                      //界面浮动按钮显示time out槽
    void slotPBOverviewTrendIsClicked();
    void slotPBInforHandIsClicked();
    void slotPBInforCharIsClicked();
    void slotPBMoveStartIsClicked();
    void slotPBMoveEndIsClicked();
    void slotPBMoveLeftIsClicked();
    void slotPBMoveRightIsClicked();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

    void showControlPB();                             //显示浮动控制按钮函数
    void paperMove(int stepX);                     //移动趋势绘制纸窗体函数


private:
    QTimer *p_qt_pbTimer;
    QPushButton *p_pb_inforHand, *p_pb_inforChar,*p_pb_moveLeftStep,
                            *p_pb_moveRightStep, *p_pb_moveStart, *p_pb_moveEnd,
                            *p_pb_overviewTrend;
    QHBoxLayout *p_hlayout_ruler;
    QGraphicsScene *p_graphicScene;

    TrendRecordPaper *p_recordPaper1, *p_recordPaper2, *p_recordPaper3;       //趋势记录纸张
    TrendHandWritingPaper *p_handInforPaper;

    bool m_isPress;                             //标明鼠标按键按下
    QPoint m_prePoint;                      //用于计算鼠标移动距离
    int m_paperPosState;                   //用于记录三张纸张的位置状态，0代表 123， 1代表312， 2代表231
    int m_paperMoveStep;                 //纸张移动步长
    int m_watchPoint;
};
#endif // TRENDDETAILWIDGET_H
