#ifndef TRENDDIGITALWIDGET_H
#define TRENDDIGITALWIDGET_H

#include <QDebug>

#include <QWidget>
#include <QVector>
#include <QGridLayout>

#include "./TrendGroupComponent/trenddigitalitem.h"

class TrendDigitalWidget : public QWidget
{
    Q_OBJECT
public:
    typedef enum {
        UP,
        DOWN,
        LEFT,
        RIGHT
    }Position;
    explicit TrendDigitalWidget(QWidget *parent = 0);
    ~TrendDigitalWidget();

    void changeLayout();
    void setPosition(Position pos);
    int getPosition();
    bool getIsPressed();

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QGridLayout *p_gLayout;

    QVector<TrendDigitalItem *> *p_digitalWidgets;
    int m_digitalWidgetNum;
    Position m_pos;
    bool m_isPressed;

};

#endif // TRENDDIGITALWIDGET_H
