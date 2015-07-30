#ifndef TRENDRECORDPAPER_H
#define TRENDRECORDPAPER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#define DIV_H 36
#define DIV_V 8
#define TOP_SPACE  20
#define BOTTOM_SPACE 20

class TrendRecordPaper : public QWidget
{
    Q_OBJECT
public:
    explicit TrendRecordPaper(QWidget *parent = 0, int index = 0    );
    ~TrendRecordPaper();

signals:
public slots:

protected:
    void paintEvent(QPaintEvent *e);

private:
    int m_index;

};

#endif // TRENDRECORDPAPER_H
