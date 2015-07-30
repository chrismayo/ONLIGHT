#ifndef TRENDHANDWRITINGINFOR_H
#define TRENDHANDWRITINGINFOR_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QImage>
#include <QFile>

class TrendHandWritingInfor : public QWidget
{
    Q_OBJECT
public:
    explicit TrendHandWritingInfor(QWidget *parent = 0);
    ~TrendHandWritingInfor();
signals:

public slots:
    void slotHide();

protected:
    void showEvent(QShowEvent *e);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QGridLayout *p_gLayout;
    QPushButton m_close;
    QVector<QPointF> *p_picture;
    QVector<QVector<QPointF>> *p_pictures;
    QImage *p_imageFile;
    bool m_flag;
};

#endif // TRENDHANDWRITINGINFOR_H
