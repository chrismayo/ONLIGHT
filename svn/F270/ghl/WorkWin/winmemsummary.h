#ifndef WINMEMSUMMARY_H
#define WINMEMSUMMARY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QTableView>
#include <QToolButton>
#include <QKeyEvent>
#include <QItemDelegate>
#include <QPen>
#include <QPainter>
#include <QTimer>
#include <QGroupBox>
#include <QDialog>

#include "../GlobalData/globalDef.h"

#include <QStandardItemModel>

#include "../GlobalData/cfgGlobalDef_Type.h"

/*
 * SQL数据库记录状态类型 ../GlobalData/cfgGlobalDef_Type.h
typedef enum SQL_Record_Status_Enum{
    SQL_Record_Status_ManualKey = 0,    //手动按键开始或停止
    SQL_Record_Status_Trigger,                  //自动触发
    SQL_Record_Status_Recording,            //记录中
    SQL_Record_Status_AutoSplitter,         //自动保存，分割
    SQL_Record_Status_PowerOff,             //电源关闭
}SQL_Record_Status;
*/


/*
 * 重写的代理类，实现view的第一列的checkbox和第二列的开始时间和结束时间显示在一列中
*/
class MemSummaryDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MemSummaryDelegate(QTableView *tabelView, QObject * parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    QPen         pen;
    QTableView*  view;
};


/*
** 详细信息弹出框提示类
*/
class MemSummaryDetailUI : public QDialog
{
    Q_OBJECT
public:
    explicit MemSummaryDetailUI(QStandardItemModel *model, QModelIndex index, QString title = "" ,QWidget *parent = 0);

    void initMemSummaryDetialUI();
    void addDataToMemSummaryDetialUI(QStandardItemModel *model, QModelIndex index, QString title = "");
    void connectSignalAndSlot();

public slots:
    void slottoEventTrend();

private:
    QLabel *                topLabel;
    QLabel *                titleLabel;
    QLabel *                startTimeLabel;
    QFrame *                line;
    QPushButton *           toEventTrendBtn;
    QLabel *                stopTimeLabel;
    QLabel *                tableNameLabel;
    QPushButton *           quitBtn;
};

class MemSummaryModel : public QStandardItemModel
{
public:

    explicit MemSummaryModel(QWidget *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};





class WinMemSummary : public QWidget
{
    Q_OBJECT
    //singleClass
private:
    explicit WinMemSummary(QWidget *parent = 0);
    static WinMemSummary *memSummary;

public:
    static WinMemSummary * initMemSummary();
    virtual ~WinMemSummary();
    /*UI*/
    void initMemSummaryUI();

    void signalAndSlotConnect();

    /*Model*/
    void initModel();
    void addDataToModel(QStandardItemModel * model, const QString dataName);
    //void setModelHeader(QStandardItemModel *model);

    /*View*/
    void showView(QTableView *view, QStandardItemModel *model);

    //void numDisplayBtnSetText(int currentRow, int sumRow);

    /*return the status of record*/
    const QString getRecordStatus(int record_status);

    void showShortcutKey(QStandardItemModel *model);

    void resizeEvent(QResizeEvent * event);

    /* 窗体大小改变时,更新view样式 **/
    void updateViewStyle(QTableView *view, QStandardItemModel *model);

    void setBtnTextAndPixmap(QPushButton * btn, QString picture);

signals:

public slots:
    void slotDisplayCurrentIndex(QModelIndex current, QModelIndex previous);

    void slotDetailMessage(QModelIndex index);

    void slotRadioBtnChange();

    void slotUpBtnPressed();
    void slotUpBtnRelease();
    void slotDownBtnPressed();
    void slotDownBtnRelease();
    void slotTimeOut();

    void slotUpdateTimeOut();

    void slotSaveBtnClicked();
    void slotCancleBtnClicked();



public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *upBtn;
    QPushButton *downBtn;
    QLabel *sampleLabel;
    QToolButton *toolBtn;
    QRadioButton *displayRadioBtn;
    QRadioButton *eventRadionBtn;
    QTableView *displayView;
    QTableView *eventView;
    QGridLayout *gridLayout;

    QSpacerItem * verticalSpacer;

    QFrame *frame;
    //QPushButton *numDisplayBtn;

    QGroupBox * btnBox;
    QPushButton * saveBtn;
    QPushButton * cancleBtn;

    MemSummaryModel *            p_displayModel;
    MemSummaryModel *            p_eventModel;
    //QTableView *                    p_view;

    /* 定时器 */
    QTimer *timer;
    QTimer *updateTime;


    int displayCount;
    int eventCount;

    /* 标志是displayBtn被选中还是eventBtn被选中 false:  true: */
    bool displayOrEventChange;

    /* 上/下按钮是按下/松开 */
    bool btnStatus;

    /* 按下的是哪个按钮 默认 : -1, 0 : 上按钮  1 : 下按钮 */
    int btnPress;


};

#endif // WINMEMSUMMARY_H
