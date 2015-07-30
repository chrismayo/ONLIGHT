#include "winmemsummary.h"
#include <QHeaderView>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>
#include <QVBoxLayout>


#define DISP_MAIN_TABLE      "table_Main_Disp"     //显示数据主表
#define EVENT_MAIN_TABLE    "table_Main_Event"  //事件数据主表
#define MANUAL_MAIN_TABLE "table_Main_Manual"   //手动采样数据主表
#define REPORT_MAIN_TABLE   "table_Main_Report" //报表数据主表


static int currentRow;
static int sumRow;

static int summaryWidth;
static int summaryHeight;

WinMemSummary * WinMemSummary::memSummary = NULL;

WinMemSummary * WinMemSummary::initMemSummary()
{
    if(memSummary == NULL)
    {
        memSummary = new WinMemSummary;
    }

    return memSummary;
}

WinMemSummary::WinMemSummary(QWidget *parent) :
    QWidget(parent)
{
    /* 上/下按钮是按下/松开 */
    btnStatus = false;
    /* 按下的是哪个按钮 默认 : -1 , 0 : 上按钮  1 : 下按钮 */
    btnPress = -1;

    initMemSummaryUI();


    initModel();

    showView(eventView, p_eventModel);
    displayOrEventChange = true;
    eventView->hide();
    displayOrEventChange = false;
    showView(displayView, p_displayModel);

    signalAndSlotConnect();
}

WinMemSummary::~WinMemSummary()
{
//    delete numDisplayBtn;
//    delete eventView;
//    delete displayView;
//    delete eventRadionBtn;
//    delete displayRadioBtn;
//    delete toolBtn;
//    delete sampleLabel;
//    delete downBtn;
//    delete upBtn;
//    delete horizontalLayout;
//    delete horizontalLayoutWidget;

//    delete displayView;
//    delete eventView;
//    delete p_displayModel;
//    delete p_eventModel;
}


void WinMemSummary::initMemSummaryUI()
{
    displayOrEventChange = false;

    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());

    this->setSizePolicy(sizePolicy);

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    upBtn = new QPushButton(this);
    upBtn->setObjectName(QStringLiteral("upBtn"));
    upBtn->setMaximumSize(QSize(50, 16777215));
    upBtn->setIcon(QIcon(":/summary/Image/summary/up.png"));
    upBtn->setIconSize(QSize(45, 25));
    upBtn->setFocusPolicy(Qt::NoFocus);


    horizontalLayout->addWidget(upBtn);

    downBtn = new QPushButton(this);
    downBtn->setObjectName(QStringLiteral("downBtn"));
    downBtn->setMaximumSize(QSize(50, 16777215));
    downBtn->setIcon(QIcon(":/summary/Image/summary/down.png"));
    downBtn->setIconSize(QSize(45, 25));
    downBtn->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(downBtn);

    QSpacerItem * verticalSpacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    horizontalLayout->addItem(verticalSpacer1);

    sampleLabel = new QLabel(this);
    sampleLabel->setObjectName(QStringLiteral("sampleLabel"));
    horizontalLayout->addWidget(sampleLabel);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    horizontalLayout->addItem(verticalSpacer);

    toolBtn = new QToolButton(this);
    toolBtn->setObjectName(QStringLiteral("toolBtn"));
    toolBtn->setMaximumSize(QSize(160, 40));

    toolBtn->setStyleSheet("background-color: rgb(255, 255, 255);");
    toolBtn->setFocusPolicy(Qt::NoFocus);
    setStyleSheet("QToolButton#toolBtn{\
                  border-top-right-radius:5px;\
                  border-bottom-right-radius:5px;\
                  background-color:#0000ff;\
                  height:20px;\
                  outline:none;\
                  }\
                  QToolButton#toolBtn:press{\
                  border-top-right-radius:5px;\
                  border-bottom-right-radius:5px;\
                  background-color:#00ff00;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton {\
                               border: none;\
                           }");

    displayRadioBtn = new QRadioButton(toolBtn);
    displayRadioBtn->setObjectName(QStringLiteral("dispalyRadioBtn"));
    displayRadioBtn->setGeometry(QRect(10, 0, 117, 16));
    displayRadioBtn->setChecked(!displayOrEventChange);
    displayRadioBtn->setFocusPolicy(Qt::NoFocus);
    eventRadionBtn = new QRadioButton(toolBtn);
    eventRadionBtn->setObjectName(QStringLiteral("eventRadioBtn"));
    eventRadionBtn->setGeometry(QRect(10, 20, 117, 16));
    //eventRadionBtn->setText("event data");
    eventRadionBtn->setFocusPolicy(Qt::NoFocus);


    horizontalLayout->addWidget(toolBtn);


    gridLayout->addLayout(horizontalLayout, 0, 0, 2, 1);

    displayView = new QTableView(this);
    displayView->setObjectName(QStringLiteral("displayView"));
    displayView->setBaseSize(QSize(0, 0));
    displayView->setShowGrid(false);
    displayView->setSortingEnabled(true);
    displayView->horizontalHeader()->setStretchLastSection(true);
    displayView->verticalHeader()->setStretchLastSection(false);

    eventView = new QTableView(this);
    eventView->setObjectName(QStringLiteral("displayView"));
    eventView->setBaseSize(QSize(0, 0));
    eventView->setShowGrid(false);
    eventView->setSortingEnabled(true);
    eventView->horizontalHeader()->setStretchLastSection(true);
    eventView->verticalHeader()->setStretchLastSection(false);
    eventView->hide();

    gridLayout->addWidget(displayView, 2, 0, 1, 1);
    gridLayout->addWidget(eventView, 2, 0, 1, 1);

    summaryWidth = this->width();
    summaryHeight = this->height();
    btnBox = new QGroupBox(this);
    btnBox->setObjectName(QStringLiteral("btnBox"));
    btnBox->setGeometry(QRect((summaryWidth - 280) / 2, summaryHeight - 90, 280, 90));
    btnBox->setFlat(false);
    btnBox->hide();

    saveBtn = new QPushButton(btnBox);
    saveBtn->setObjectName(QStringLiteral("saveBtn"));
    saveBtn->setGeometry(QRect(0, 0, 140, 90));
    saveBtn->setFlat(true);
    setBtnTextAndPixmap(saveBtn, "save.png");

    cancleBtn = new QPushButton(btnBox);
    cancleBtn->setObjectName(QStringLiteral("cancleBtn"));
    cancleBtn->setGeometry(QRect(140, 0, 140, 90));
    cancleBtn->setFlat(true);
    setBtnTextAndPixmap(cancleBtn, "cancle.png");

    sampleLabel->setText("数据采样...\n事件数据");

    displayRadioBtn->setText("显示数据");
    eventRadionBtn->setText("事件数据");
}


void WinMemSummary::setBtnTextAndPixmap(QPushButton * btn, QString picture)
{
    QVBoxLayout *btnLayout = new QVBoxLayout;

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(tr(":/summary/Image/summary/%1").arg(picture)));
    label->resize(QSize(140, 70));
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(0);
    btnLayout->addWidget(label);
    QLabel *label1 = new QLabel((picture == "save.png") ? "当前选择保存" : "取消选中");
    btnLayout->addWidget(label1);
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    label1->setFont(font);

    label1->resize(QSize(140, 20));
    label1->setAlignment(Qt::AlignCenter);
    //label1->setText();

    btn->setLayout(btnLayout);
}



/* 绑定信号和槽 */
void WinMemSummary::signalAndSlotConnect()
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));

    updateTime = new QTimer(this);
    connect(updateTime, SIGNAL(timeout()), this, SLOT(slotUpdateTimeOut()));
    updateTime->start(1000);


    /* 切换显示界面的信号和槽函数 */
    connect(toolBtn, SIGNAL(clicked()), this, SLOT(slotRadioBtnChange()));
    connect(displayRadioBtn, SIGNAL(clicked()), this, SLOT(slotRadioBtnChange()));
    connect(eventRadionBtn, SIGNAL(clicked()), this, SLOT(slotRadioBtnChange()));

    /* 点击当前行，显示当前行的详细信息  */
    connect(displayView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotDetailMessage(QModelIndex)));
    connect(eventView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotDetailMessage(QModelIndex)));

    /* 当前行变化时，显示当前行的行数也变化的信号和巢  */
    connect(displayView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                   this, SLOT(slotDisplayCurrentIndex(QModelIndex,QModelIndex)));
    connect(eventView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                   this, SLOT(slotDisplayCurrentIndex(QModelIndex,QModelIndex)));


    connect(upBtn, SIGNAL(pressed()), this, SLOT(slotUpBtnPressed()));
    connect(upBtn, SIGNAL(released()), this, SLOT(slotUpBtnRelease()));

    connect(downBtn, SIGNAL(pressed()), this, SLOT(slotDownBtnPressed()));
    connect(downBtn, SIGNAL(released()), this, SLOT(slotDownBtnRelease()));


    connect(saveBtn, SIGNAL(clicked()), this, SLOT(slotSaveBtnClicked()));
    connect(cancleBtn, SIGNAL(clicked()), this, SLOT(slotCancleBtnClicked()));

//    connect(eventView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotDetailMessage(QModelIndex)));

}

/*
** 初始化显示数据的model和事件数据的model
** para 	: 无
** return : 无
*/
void WinMemSummary::initModel()
{
    p_displayModel = new MemSummaryModel;
    p_eventModel = new MemSummaryModel;

    addDataToModel(p_displayModel, DISP_MAIN_TABLE);
    addDataToModel(p_eventModel, EVENT_MAIN_TABLE);
}

/*
** 给model加载数据
** model : 	显示model或者事件model
** dataName : 数据库的表名
*/
void WinMemSummary::addDataToModel(QStandardItemModel *model, const QString dataName)
{

    int i = 0;
    QDateTime time;
    QSqlQuery query;

    QString fileNameSuffix;
    if (dataName == DISP_MAIN_TABLE)
    {
        fileNameSuffix = ".GDS";
    }
    else
    {
        fileNameSuffix = ".GEV";
    }

    /*
     * 查询ID是为类后期跟新数据用
     */
    query.exec(tr("select StartTime, EndTime, DataCount,RecordStatus,FileName, ID from %1").arg(dataName));
    while (query.next())
    {
        QString startTime = time.fromMSecsSinceEpoch(query.value(0).toLongLong()).toString("yyyy/MM/dd hh:mm:ss");
        QString stopTime = time.fromMSecsSinceEpoch(query.value(1).toLongLong()).toString("yyyy/MM/dd hh:mm:ss");

        QStandardItem *itemTime = new QStandardItem(QObject::tr("%1%2").arg(stopTime).arg(startTime));

        model->setItem(i, 1, itemTime);
        QStandardItem *itemData = new QStandardItem(query.value(2).toString());
        model->setItem(i, 2, itemData);
        QStandardItem *itemStatus = new QStandardItem(getRecordStatus(query.value(3).toInt()));
        model->setItem(i, 3, itemStatus);
        QStandardItem *itemFile = new QStandardItem(query.value(4).toString() + fileNameSuffix);
        model->setItem(i, 4, itemFile);
        i++;
    }


    //setModelHeader(model);
}

/*
** 初始化头信息
*/
//void WinMemSummary::setModelHeader(QStandardItemModel *model)
//{
//    model->setHeaderData(0, Qt::Horizontal, "");
//    model->setHeaderData(1, Qt::Horizontal, "\t\t\t\t\t停止时间\n\t\t\t\t\t开始时间");
//    model->setHeaderData(2, Qt::Horizontal, "数据");
//    model->setHeaderData(3, Qt::Horizontal, "Factor");
//    model->setHeaderData(4, Qt::Horizontal, "文件名");
//}


/*
** 当前行数变化的槽函数
*/
void WinMemSummary::slotDisplayCurrentIndex(QModelIndex current, QModelIndex previous)
{
    //QModelIndex index = current.model()->index(current.row(), 0);
    //numDisplayBtn->hide();
    currentRow = current.row() + 1;
    sumRow = current.model()->rowCount();

    if(displayOrEventChange)
        emit p_displayModel-> headerDataChanged(Qt::Horizontal, 0, 0);
    else
        emit p_eventModel->headerDataChanged(Qt::Horizontal, 0, 0);
    //numDisplayBtnSetText(index.row() + 1, current.model()->rowCount());
}

/*
** 点击某行(不包括第一列)，显示详细信息的槽函数
** 点击选择某行的第一列，如果有选中，则显示快捷键，没有选中就不显示快捷键
*/
void WinMemSummary::slotDetailMessage(QModelIndex index)
{
    if (index.column() != 0)
    {
        if (index.model() == p_displayModel)
        {
            MemSummaryDetailUI *DetailUi = new MemSummaryDetailUI(p_displayModel, index, "内存一览");
            /* 没关该窗体之前，父窗体不允许操作 */
            DetailUi->setWindowModality(Qt::ApplicationModal);
            DetailUi->show();
        }
        else
        {
            MemSummaryDetailUI *DetailUi = new MemSummaryDetailUI(p_eventModel, index, "内存一览");
            DetailUi->setWindowModality(Qt::ApplicationModal);
            DetailUi->show();
        }
    }
    else if (index.column() == 0)
    {
        if (displayOrEventChange)
        {
            showShortcutKey(p_eventModel);
        }
        else
        {
            showShortcutKey(p_displayModel);
        }
    }
}

/*
** 显示显示数据或者事件信息的槽函数
*/
void WinMemSummary::slotRadioBtnChange()
{
    displayOrEventChange = !displayOrEventChange;
    displayRadioBtn->setChecked(!displayOrEventChange);
    eventRadionBtn->setChecked(displayOrEventChange);
    if (displayOrEventChange == false)
    {
        eventView->hide();
        btnBox->hide();
        displayView->setCurrentIndex(p_displayModel->index(0, 0));
        showView(displayView, p_displayModel);
    }
    else
    {
        showView(eventView, p_eventModel);
        eventView->hide();
        displayView->hide();
        btnBox->hide();
        eventView->setCurrentIndex(p_eventModel->index(0, 0));
        showView(eventView, p_eventModel);
    }
}

/* timer */
void WinMemSummary::slotTimeOut()
{
    if (btnStatus)
    {
        if (btnPress == 0)
        {
            emit upBtn->pressed();
        }
        else if (btnPress == 1)
        {
            emit downBtn->pressed();
        }
    }
}

void WinMemSummary::slotUpBtnPressed()
{
    btnStatus = true;
    btnPress = 0;
    timer->start(50);

    QKeyEvent * keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    if (displayOrEventChange)
    {
        qApp->sendEvent(eventView, keyEvent);
    }
    else
    {
        qApp->sendEvent(displayView, keyEvent);
    }
}


void WinMemSummary::slotUpBtnRelease()
{
    btnStatus = false;
}

void WinMemSummary::slotDownBtnPressed()
{
    btnStatus = true;
    btnPress = 1;
    timer->start(50);

    QKeyEvent * keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    if (displayOrEventChange)
    {
        qApp->sendEvent(eventView, keyEvent);
    }
    else
    {
        qApp->sendEvent(displayView, keyEvent);
    }
}

void WinMemSummary::slotDownBtnRelease()
{
    btnStatus = false;
}




/*
**
** 动态刷新view里面的值，当正在记录的数据列发生变化时，每秒钟刷新显示数据，当数据采集完毕时，将会显示记录名(第五列的文件名)
** 当有新的一列产生时，会插入新的一列
**
**
** 需要修改
**
*/
void WinMemSummary::slotUpdateTimeOut()
{
//    if(!displayOrEventChange)
//    {
//        static int i = 1000;
//        QStandardItem *item = new QStandardItem(QString::number(i++));
//        item->setBackground(QColor(239, 118, 69));

//        p_displayModel->setItem(0, 2, item);
//        displayView->show();
//    }
//    else
//    {
//        //showView(eventView, p_eventModel);
//    }
}


/*
 * 重写resizeEvent函数，当界面大小小于一个值的时候，该view窗口会隐藏或者缩放某列
 *
 * 后续需优化
*/
void WinMemSummary::resizeEvent(QResizeEvent * event)
{
    if(!displayOrEventChange)
    {
        updateViewStyle(displayView, p_displayModel);
    }
    else
    {
        updateViewStyle(eventView, p_eventModel);
    }
}

/* 窗体大小改变时,更新view样式 **/
void WinMemSummary::updateViewStyle(QTableView *view, QStandardItemModel *model)
{
    summaryWidth = this->width();
    summaryHeight = this->height();
    btnBox->setGeometry(QRect((summaryWidth - 280) / 2, summaryHeight - 90, 280, 90));
    view->setColumnWidth(1, this->size().width() / 5);
    view->setColumnWidth(3, this->size().width() / 6);

    int viewheight = view->height() - view->horizontalHeader()->height();

    for (int i = 0; i < model->rowCount(); i++)
    {
        view->setRowHeight(i, viewheight / 11);
    }
}



/*
** 显示显示数据或者事件数据的view函数
*/
void WinMemSummary::showView(QTableView *view, QStandardItemModel *model)
{
    currentRow = 1;
    sumRow = model->rowCount();
    //view->setCurrentIndex(model->index(0, 0));

    view->verticalHeader()->hide();


    view->setModel(model);

    MemSummaryDelegate *myDelegate = new MemSummaryDelegate(view);
//    view->setItemDelegateForColumn(0, myDelegate);
//    view->setItemDelegateForColumn(1, myDelegate);
    view->setItemDelegate(myDelegate);
    view->horizontalHeader()->stretchLastSection();

    view->setColumnWidth(0, 80);
    view->setColumnWidth(1, this->size().width() / 5);
    view->setColumnWidth(3, this->size().width() / 6);

    int viewHeight = eventView->height() - eventView->horizontalHeader()->height();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex index = model->index(i, 0);
        model->setData(index, false);
        view->setRowHeight(i, viewHeight / 11);
    }

   // numDisplayBtnSetText(0, model->rowCount());
    view->setSortingEnabled(false);
    view->setEditTriggers(false);
    /* 设置表头不聚焦(解决全部选中时表头塌陷问题) */
    view->horizontalHeader()->setHighlightSections(false);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

//    view->setStyleSheet("QTableView{ border:none; background:white; } \
//                        QTableView::item:selected{ color:white; background:rgb(34, 175, 75); };");

    view->show();


}



/*
** 显示当前行数和总函数的信息  如： 0016/0180
*/
//void WinMemSummary::numDisplayBtnSetText(int currentRow, int sumRow)
//{
//    if (sumRow < 12)
//    {
//        if (currentRow == 0)
//        {
//            currentRow = sumRow;
//        }
////        numDisplayBtn->setText(tr("%1/%2").arg(currentRow, 4, 10, QChar('0')).arg(sumRow, 4, 10, QChar('0')));
//    }
//    else
//    {
//        if (currentRow == 0)
//        {
//            currentRow = 11;
//        }

//    }
//    //numDisplayBtn->setText(tr("(%1/%2)").arg(currentRow, 4, 10, QChar('0')).arg(sumRow, 4, 10, QChar('0')));
//}

/*
** 把从数据库中读取的整型值转换为相对应的字符串
*/
const QString WinMemSummary::getRecordStatus(int record_status)
{

    if (record_status == SQL_Record_Status_ManualKey)
    {
        return "手动按键开始或停止";
    }
    else if (record_status == SQL_Record_Status_Trigger)
    {
        return "自动触发";
    }
    else if (record_status == SQL_Record_Status_Recording)
    {
        return "记录中";
    }
    else if (record_status == SQL_Record_Status_AutoSplitter)
    {
        return "自动保存，分割";
    }
    else if (record_status == SQL_Record_Status_PowerOff)
    {
        return "电源关闭";
    }
    else
    {
        return "";
    }

}

/*
** 保存选中
*/
void WinMemSummary::slotSaveBtnClicked()
{
    QStandardItemModel *model;
    if(displayOrEventChange)
    {
        model = p_eventModel;
    }
    else
    {
       model = p_displayModel;
    }

    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex index = model->index(i, 0);
        bool ok = index.data().toBool();
        if(ok)
        {
            QMessageBox::about(this, "save", "save data");
        }
    }

}

/*
** 取消所有选中
*/
void WinMemSummary::slotCancleBtnClicked()
{
    //qDebug() << "cancel";
    QStandardItemModel *model;

    if(displayOrEventChange)
    {
        model = p_eventModel;
    }
    else
    {
        model = p_displayModel;
    }
    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex index = model->index(i, 0);
        model->setData(index, false);
    }

    btnBox->hide();
}



/*
** 快捷键的显示和隐藏
*/
void WinMemSummary::showShortcutKey(QStandardItemModel *model)
{
    int i;
    int k = 0;
    for (i = 0; i < model->rowCount(); i++)
    {
        if (model->index(i, 0).data().toBool())
        {
            k = 1;
            btnBox->show();
            break;
        }
    }
    if (k == 0)
    {
        btnBox->hide();
    }

}












/*****************************************************************************************
	自定义代理类的重新实现
		：实现了第一列显示checkBox按钮
		：实现了第二列显示两行信息(上一行：停止时间， 下一行：开始时间)
*****************************************************************************************/


/*
** 画checkBox的函数
*/
static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options)
{
    QStyleOptionButton check_box_style_option;
    QRect check_box_rect = QApplication::style()->subElementRect(
        QStyle::SE_CheckBoxIndicator,
        &check_box_style_option);

    QPoint check_box_point(view_item_style_options.rect.x() +
                           view_item_style_options.rect.width() / 2 -
                           check_box_rect.width() / 2,
                           view_item_style_options.rect.y() +
                           view_item_style_options.rect.height() / 2 -
                           check_box_rect.height() / 2);
    return QRect(check_box_point, check_box_rect.size());
}

MemSummaryDelegate::MemSummaryDelegate(QTableView* tableView, QObject *parent)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor,0,tableView->gridStyle());
    view = tableView;
}

/*
** 
*/
void MemSummaryDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    //QStyledItemDelegate::paint(painter,option,index);
    QStyleOptionViewItem itemOption(option);
    if(itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    //QStyledItemDelegate::paint(painter,itemOption,index);
    QPen oldPen = painter->pen();
    painter->setPen(pen);
    //painter->drawLine(option.rect.topRight(),option.rect.bottomRight());
    painter->drawLine(itemOption.rect.bottomLeft(),itemOption.rect.bottomRight());
    if (index.column() == 0)
    {
        bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
        /*重新绘制第一列view */

        //qDebug() << checked;
        QStyleOptionButton * check_box_style_option = new QStyleOptionButton();

        check_box_style_option->state |= QStyle::State_Enabled;
        if(checked)
        {
            check_box_style_option->state |= QStyle::State_On;
        }
        else
        {
            check_box_style_option->state |= QStyle::State_Off;
        }
        check_box_style_option->rect = CheckBoxRect(option);
        QApplication::style()->drawControl(QStyle::CE_CheckBox,check_box_style_option,painter);

        painter->drawLine(option.rect.topRight(),option.rect.bottomRight());
    }
    painter->setPen(oldPen);
    if (index.column() == 1)
    {
        QString str = index.model()->data(index, Qt::DisplayRole).toString();

        int x = option.rect.x();
        int y = option.rect.y();
        int width = option.rect.width();
        int height = option.rect.height();

        painter->drawText(x, y, width, height / 2 , Qt::AlignCenter, str.left(19));
        painter->drawText(x, y + height / 2, width, height / 2 , Qt::AlignCenter, str.right(19));
    }
    if (index.column() != 1 && index.column() != 0)
    {
        QItemDelegate::paint(painter,option,index);
    }
}

bool MemSummaryDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                              const QStyleOptionViewItem &option,const QModelIndex &index)
{
//    if (index.column() == 0)
//    {
        if ((event->type() == QEvent::MouseButtonRelease)
                || (event->type() == QEvent::MouseButtonDblClick))
        {
            //qDebug() << "MouseButtonRelease | MouseButtonDblClick";
            QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
            if(mouse_event->button() != Qt::LeftButton ||
               !CheckBoxRect(option).contains(mouse_event->pos()))
            {

                return false;
            }

            if (event->type() == QEvent::MouseButtonDblClick)
            {
                return true;
            }
        }
        else if (event->type() == QEvent::KeyPress)
        {
            if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space
                    && static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
        return model->setData(index, !checked, Qt::EditRole);
//    }
}



/********************************************************************************************************
 *
 * 详细显示某一列信息的界面
 *
 * *****************************************************************************************************/
MemSummaryDetailUI::MemSummaryDetailUI(QStandardItemModel *model, QModelIndex index, QString title, QWidget *parent) : QDialog(parent)
{
    initMemSummaryDetialUI();
    addDataToMemSummaryDetialUI(model, index, title);
    connectSignalAndSlot();
}

void MemSummaryDetailUI::initMemSummaryDetialUI()
{

    //this->resize(322, 306);

    topLabel = new QLabel(this);
    topLabel->setObjectName(QStringLiteral("topLabel"));
    topLabel->setGeometry(QRect(0, 0, 370, 40));
    topLabel->setPixmap(QPixmap(":/summary/Image/summary/title.png"));

    titleLabel = new QLabel(this);
    titleLabel->setObjectName(QStringLiteral("titleLabel"));
    titleLabel->setGeometry(QRect(10, 0, 80, 40));
    QPalette color;
    color.setColor(QPalette::WindowText,Qt::white);
    titleLabel->setPalette(color);

    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(12);
    font.setBold(true);
    font.setWeight(75);
    titleLabel->setFont(font);

    startTimeLabel = new QLabel(this);
    startTimeLabel->setObjectName(QStringLiteral("startTimeLabel"));
    startTimeLabel->setGeometry(QRect(30, 60, 320, 41));
    startTimeLabel->setFont(font);

    line = new QFrame(this);
    line->setObjectName(QStringLiteral("line"));
    line->setGeometry(QRect(10, 30, 350, 20));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    stopTimeLabel = new QLabel(this);
    stopTimeLabel->setObjectName(QStringLiteral("stopTimeLabel"));
    stopTimeLabel->setGeometry(QRect(30, 110, 320, 41));
    stopTimeLabel->setFont(font);

    tableNameLabel = new QLabel(this);
    tableNameLabel->setObjectName(QStringLiteral("tableNameLabel"));
    tableNameLabel->setGeometry(QRect(30, 160, 320, 41));
    tableNameLabel->setFont(font);

    quitBtn = new QPushButton(this);
    quitBtn->setObjectName(QStringLiteral("quitBtn"));
    //quitBtn->setStyleSheet("border:1px groove gray;border-radius:10px;padding:1px 2px;");
    quitBtn->setGeometry(QRect(340, 10, 20, 20));
    quitBtn->setIcon(QIcon(":/summary/Image/summary/close_1.png"));
    quitBtn->setIconSize(QSize(40, 40));
    quitBtn->setFocusPolicy(Qt::NoFocus);
    quitBtn->setFlat(true);


    toEventTrendBtn = new QPushButton(this);
    toEventTrendBtn->setObjectName(QStringLiteral("toTrendBtn"));
    QPixmap icon(":/summary/Image/summary/eventTrend.png");
    toEventTrendBtn->setGeometry(QRect((370 - icon.width()) / 2, 210, icon.width(), icon.height()));
    toEventTrendBtn->setFont(font);
    toEventTrendBtn->setIcon(icon);
    toEventTrendBtn->setIconSize(QSize(icon.width(), icon.height()));
    toEventTrendBtn->setFocusPolicy(Qt::NoFocus);
    toEventTrendBtn->setFlat(true);


    //retranslateUi(this);

    QMetaObject::connectSlotsByName(this);

    this->setGeometry((summaryWidth - 320) / 2 ,(summaryHeight - 300) / 2, 370, 260);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
}

void MemSummaryDetailUI::addDataToMemSummaryDetialUI(QStandardItemModel *model, QModelIndex index, QString title)
{

    QModelIndex timeIndex = index.model()->index(index.row(), 1);
    QModelIndex tableIndex = index.model()->index(index.row(), 4);
    QString time = model->data(timeIndex).toString();
    QString table = model->data(tableIndex).toString();


    titleLabel->setText(title);

    startTimeLabel->setText(tr("开始时间 %1").arg(time.right(19)));
    stopTimeLabel->setText(tr("结束时间 %1").arg(time.left(19)));
    tableNameLabel->setText(tr("文件名  %1").arg(table));
}

void MemSummaryDetailUI::connectSignalAndSlot()
{
     connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
     connect(toEventTrendBtn, SIGNAL(clicked()), this, SLOT(slottoEventTrend()));
}

void MemSummaryDetailUI::slottoEventTrend()
{
    QMessageBox::information(this, "至趋势", "没数据");
}





/********************************************************************************************
 *
 * model
 *
 * *****************************************************************************************/
MemSummaryModel::MemSummaryModel(QWidget *parent) : QStandardItemModel(parent)
{

}

QVariant MemSummaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("(%1/%2)").arg(currentRow, 4, 10, QChar('0')).arg(sumRow, 4, 10, QChar('0'));

        case 1: return tr("停止时间\n开始时间");

        case 2: return tr("数据");

        case 3: return tr("Factor");
        case 4: return tr("文件名");

            break;
        default:
            break;
        }
    }
}


