#ifndef TRENDDIGITALITEM_H
#define TRENDDIGITALITEM_H

#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPaintEvent>

class TrendDigitalItem : public QLabel
{
    Q_OBJECT
public:
    explicit TrendDigitalItem(QLabel *parent = 0);
    ~TrendDigitalItem();

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QLabel *p_colorMark;
    QGridLayout *p_gLayout;
    QHBoxLayout *p_hLayout;

public slots:

};

#endif // TRENDDIGITALITEM_H
