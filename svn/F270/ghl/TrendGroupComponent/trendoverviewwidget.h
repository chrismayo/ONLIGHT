#ifndef TRENDOVERVIEWWIDGET_H
#define TRENDOVERVIEWWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QEvent>

class TrendOverviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrendOverviewWidget(QWidget *parent = 0);
    ~TrendOverviewWidget();
    void setLayoutSize();
signals:
    void sigHide();

public slots:
private slots:
    void slotSendCloseSig();

protected:

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QGridLayout *p_gLayout_main, *p_gLayout_control;
    QLabel *p_label_dateStart, *p_label_dateEnd;
    QPushButton *p_pButton_toLeft, *p_pButton_toRight, *p_pButton_toEnd,
                            *p_pButton_toStart, *p_pButton_close;


};

#endif // TRENDOVERVIEWWIDGET_H
