#ifndef WINALARMSUMMARY_H
#define WINALARMSUMMARY_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QTimer>
#include <QItemDelegate>
#include <QPen>
#include <QPainter>
#include <QLabel>



class AlarmSummaryDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit AlarmSummaryDelegate(QTableView *tabelView, QObject * parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model,
//                     const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    QPen         pen;
    QTableView*  view;
};


class AlarmSummaryDetailUI : public QWidget
{
    Q_OBJECT
public:
    AlarmSummaryDetailUI(QStandardItemModel *model, QModelIndex index, QString title, QWidget *parent = 0);

    void initAlarmSummaryDetailUI();
    void signalAndSlotConnect();
    void alarmSummaryDetailShow(QStandardItemModel *model, QModelIndex index, QString &title);

    QString getTypeName(const QString & type);

private slots:
    void slotdisplayTrend();
    void sloteventTrend();

private:
    QLabel *topLabel;
    QFrame *line;
    QLabel *titleLabel;
    QPushButton *closeBtn;
    QFrame *line_2;
    QLabel *tagNoLabel;
    QLabel *tagLabel;
    QLabel *chanelLabel;
    QFrame *line_3;
    QLabel *elecLabel;
    QLabel *typeLabel;
    QLabel *timeLabel;
    QFrame *line_4;
    QPushButton *displayBtn;
    QPushButton *eventBtn;
    QFrame *line_5;
    QLabel *statusLabel;
};




class WinAlarmSummary : public QWidget
{
    Q_OBJECT
public:
    static WinAlarmSummary * initAlarmSummary();

private:
    explicit WinAlarmSummary(QWidget *parent = 0);
    static WinAlarmSummary *alarmSummary;
public:
    void initAlarmSummaryUI();
    void initAlarmSummaryModel();
    void initHeaderData();
    void signalAndSlotConnect();
    void showView();

    void resizeEvent(QResizeEvent * event);



signals:

public slots:
    void slotDetailMessage(QModelIndex index);
    void slotdisplayCurrentIndex(QModelIndex current, QModelIndex previous);

    void slotupBtnPressed();
    void slotupBtnRelease();
    void slotdownBtnPressed();
    void slotdownBtnRelease();
    void slottimeOut();


public:
    QPushButton *upBtn;
    QPushButton *downBtn;
    QGridLayout *gridLayout;
    QTableView *alarmView;

private:
    QStandardItemModel * p_alarmmodel;

    QString dataName;

    QTimer * timer;

    /* 上/下按钮是按下/松开 */
    bool btnStatus;

    /* 按下的是哪个按钮 默认 : -1, 0 : 上按钮  1 : 下按钮 */
    int btnPress;


    int width;
    int height;

};

#endif // WINALARMSUMMARY_H
