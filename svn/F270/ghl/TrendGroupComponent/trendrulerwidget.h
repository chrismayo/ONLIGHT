#ifndef TRENDRULERWIDGET_H
#define TRENDRULERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class TrendRulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrendRulerWidget(QWidget *parent = 0);
    ~TrendRulerWidget();

    int setRulerMoveRange(int startPoint, int endPoint);   //设置标尺在父窗体中的移动范围
    bool isSelected();
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool m_press;
    int m_startPoint, m_endPoint;  //标准尺移动范围
    int m_largeScaleNum, m_smallScaleNum; //相对于尺子长度的大刻度数量， 相对于大刻度长度的小刻度数量

};

#endif // TRENDRULERWIDGET_H
