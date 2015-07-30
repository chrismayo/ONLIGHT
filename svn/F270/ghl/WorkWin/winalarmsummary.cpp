#include "winalarmsummary.h"
#include "../GlobalData/globalDef.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QHeaderView>
#include <QKeyEvent>
#include <QImage>

#include <QMessageBox>

static int currentRow;
static int sumRow;


static bool detailTime;

static int alarmWidth;
static int alarmHeight;


WinAlarmSummary * WinAlarmSummary::alarmSummary = NULL;

WinAlarmSummary * WinAlarmSummary::initAlarmSummary()
{
    if(alarmSummary == NULL)
    {
        alarmSummary = new WinAlarmSummary;
    }

    return alarmSummary;
}


WinAlarmSummary::WinAlarmSummary(QWidget *parent) :
    QWidget(parent)
{   
    btnPress = -1;
    btnStatus = false;

    dataName = "alarm";
    detailTime = true;
    currentRow = 0;

    initAlarmSummaryUI();

    initAlarmSummaryModel();

    showView();
    signalAndSlotConnect();

}

void WinAlarmSummary::initAlarmSummaryUI()
{
//    alarmWidth = this->size().width();
//    alarmHeight = this->size().height();

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    alarmView = new QTableView(this);
    alarmView->setObjectName(QStringLiteral("alarmView"));
    alarmView->setAutoScroll(false);
    alarmView->setAutoScrollMargin(0);
    alarmView->setSelectionBehavior(QAbstractItemView::SelectRows);
    alarmView->setSortingEnabled(false);

    //p_alarmmodel->headerData()

    upBtn = new QPushButton(this);
    upBtn->setObjectName(QStringLiteral("pushButton"));
    upBtn->setGeometry(QRect(0, 0, 45, 28));
    upBtn->setMaximumSize(QSize(50, 16777215));
    upBtn->setIcon(QIcon(":/summary/Image/summary/up.png"));
    upBtn->setIconSize(QSize(45, 28));
    upBtn->setFocusPolicy(Qt::NoFocus);
    //upBtn->setFlat(true);
    upBtn->hide();
    setStyleSheet("QPushButton {\
                 border: none;\
             }");


    downBtn = new QPushButton(this);
    downBtn->setObjectName(QStringLiteral("downBtn"));
    downBtn->setGeometry(QRect(45, 0, 90, 28));
    downBtn->setMaximumSize(QSize(50, 16777215));
    downBtn->setIcon(QIcon(":/summary/Image/summary/down.png"));
    downBtn->setIconSize(QSize(45, 28));
    downBtn->setFocusPolicy(Qt::NoFocus);
    //downBtn->setFlat(true);
    downBtn->hide();

    gridLayout->addWidget(alarmView, 0, 0, 1, 1);
}



void WinAlarmSummary::initAlarmSummaryModel()
{
    p_alarmmodel = new QStandardItemModel(this);

    int i = 0;

    QString timeFormate;

    timeFormate = detailTime ? "yyyy/MM/dd hh:mm:ss.zzz" : "yyyy/MM/dd hh:mm:ss";

    QSqlQuery query;

    /*
     * 查询ID是为类后期跟新数据用
     */
    query.exec(tr("select status, chanel, elec, type, alarmtime, ID from %1").arg(dataName));
    while (query.next())
    {
        QString startTime = QDateTime::fromMSecsSinceEpoch(query.value(4).toLongLong()).toString(timeFormate);

        QStandardItem *itemStatus = new QStandardItem(query.value(0).toString());
//        qDebug() << query.value(0).toInt();
        p_alarmmodel->setItem(i, 0, itemStatus);
        QStandardItem *itemCh = new QStandardItem(tr("%1").arg(query.value(1).toInt(), 4, 10, QChar('0')));
        p_alarmmodel->setItem(i, 1, itemCh);
        QStandardItem *itemElec = new QStandardItem(query.value(2).toString());
        p_alarmmodel->setItem(i, 2, itemElec);
        QStandardItem *itemType = new QStandardItem(query.value(3).toString());
        p_alarmmodel->setItem(i, 3, itemType);
        QStandardItem *itemTime = new QStandardItem(startTime);
        p_alarmmodel->setItem(i, 4, itemTime);
        i++;
    }

    sumRow = i;

    initHeaderData();

}

void WinAlarmSummary::initHeaderData()
{

    p_alarmmodel->setHeaderData(0, Qt::Horizontal, "");
    p_alarmmodel->setHeaderData(1, Qt::Horizontal, tr("源通道(%1/%2)").arg(currentRow + 1, 4, 10, QChar('0')).arg(sumRow, 4, 10, QChar('0')));
    p_alarmmodel->setHeaderData(2, Qt::Horizontal, "电平");
    p_alarmmodel->setHeaderData(3, Qt::Horizontal, "类型");
    p_alarmmodel->setHeaderData(4, Qt::Horizontal, "报警时间");
}


void WinAlarmSummary::signalAndSlotConnect()
{

    connect(alarmView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotDetailMessage(QModelIndex)));

    connect(alarmView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                   this, SLOT(slotdisplayCurrentIndex(QModelIndex,QModelIndex)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slottimeOut()));


    connect(upBtn, SIGNAL(pressed()), this, SLOT(slotupBtnPressed()));
    connect(upBtn, SIGNAL(released()), this, SLOT(slotupBtnRelease()));

    connect(downBtn, SIGNAL(pressed()), this, SLOT(slotdownBtnPressed()));
    connect(downBtn, SIGNAL(released()), this, SLOT(slotdownBtnRelease()));
}


void WinAlarmSummary::showView()
{
    sumRow = p_alarmmodel->rowCount();
    if(sumRow == 0)
    {
        upBtn->hide();
        downBtn->hide();
    }
    else
    {
        upBtn->show();
        downBtn->show();
    }

    alarmView->setCurrentIndex(p_alarmmodel->index(0, 0));

    alarmView->setModel(p_alarmmodel);

    AlarmSummaryDelegate *alarmDelegate = new AlarmSummaryDelegate(alarmView);
//    alarmView->setItemDelegateForColumn(0, alarmDelegate);
//    alarmView->setItemDelegateForColumn(1, alarmDelegate);
//    alarmView->setItemDelegateForColumn(3, alarmDelegate);
    alarmView->setItemDelegate(alarmDelegate);

    for(int i = 0; i < sumRow; i++)
    {
        alarmView->setRowHeight(i, height / 11);
    }

    alarmView->setShowGrid(false);
    alarmView->setColumnWidth(0, 45);
    alarmView->setColumnWidth(1, 250);
    alarmView->verticalHeader()->hide();
    alarmView->horizontalHeader()->setHighlightSections(false);
    alarmView->setEditTriggers(false);

    alarmView->horizontalHeader()->setStretchLastSection(true);

    alarmView->setSortingEnabled(true);
    //alarmView->setStyleSheet("QTableView{ border:none; background:black; } \
                        QTableView::item:selected{ color:white; background:rgb(34, 175, 75); };");

    alarmView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void WinAlarmSummary::slotDetailMessage(QModelIndex index)
{
    AlarmSummaryDetailUI *ui = new AlarmSummaryDetailUI(p_alarmmodel, index, "报警一览");
    ui->setWindowModality(Qt::ApplicationModal);
    ui->show();
}


void WinAlarmSummary::slotdisplayCurrentIndex(QModelIndex current, QModelIndex previous)
{
    currentRow = current.row() + 1;
    p_alarmmodel->setHeaderData(1, Qt::Horizontal, tr("源通道(%1/%2)").arg(currentRow, 4, 10, QChar('0')).arg(sumRow, 4, 10, QChar('0')));

}


void WinAlarmSummary::slotupBtnPressed()
{
    btnStatus = true;
    btnPress = 0;
    timer->start(50);

    QKeyEvent * keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);

    qApp->sendEvent(alarmView, keyEvent);

}


void WinAlarmSummary::slotupBtnRelease()
{
    btnStatus = false;
}

void WinAlarmSummary::slotdownBtnPressed()
{
    btnStatus = true;
    btnPress = 1;
    timer->start(50);

    QKeyEvent * keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);

    qApp->sendEvent(alarmView, keyEvent);

}

void WinAlarmSummary::slotdownBtnRelease()
{
    btnStatus = false;
}

void WinAlarmSummary::slottimeOut()
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


/*
 * 重写resizeEvent函数，当界面大小小于一个值的时候，该view窗口会隐藏或者缩放某列
 *
 * 后续需优化
*/
void WinAlarmSummary::resizeEvent(QResizeEvent * event)
{
    alarmWidth = this->size().width();
    alarmHeight = this->size().height();

    int viewheight = alarmView->height() - alarmView->horizontalHeader()->height();
    alarmView->setColumnWidth(1, 250);
    alarmView->setColumnWidth(3, this->size().width() / 6);

    for (int i = 0; i < p_alarmmodel->rowCount(); i++)
    {
        alarmView->setRowHeight(i, viewheight / 11);
    }
}






/*****************************************************************************************
    自定义代理类的重新实现
        ：重写代理类，实现第一列图片，第二列通道
*****************************************************************************************/

AlarmSummaryDelegate::AlarmSummaryDelegate(QTableView* tableView, QObject *parent)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor,0,tableView->gridStyle());

    /* white font */
//    QColor gridColor(255, 255, 255);
//    pen = QPen(gridColor);

    view = tableView;
}



void AlarmSummaryDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{

    if (index.column() == 0)
    {
        int x = option.rect.x();
        int y = option.rect.y();
        int width = option.rect.width();
        int height = option.rect.height();

        QString status = index.model()->data(index).toString();

        QImage *image;
        if (status == "0")
        {
            image = new QImage(":/summary/Image/summary/ACK.png");
        }
        else if (status == "1")
        {

            image = new QImage(":/summary/Image/summary/on.png");

        }
        else if (status == "2")
        {
            image = new QImage(":/summary/Image/summary/OFF.png");
        }
        else
        {
            image = new QImage(":/summary/Image/summary/image.png");
        }

        painter->drawImage(x + (height - image->width()) / 2, y + (height - image->height()) / 2 , *image, 0, 0, height, height);
    }
    else if (index.column() == 1)
    {
        QString chanel = index.model()->data(index, Qt::DisplayRole).toString();

        int x = option.rect.x();
        int y = option.rect.y();
        int width = option.rect.width();
        int height = option.rect.height();

        painter->drawText(x, y, width, height, Qt::AlignVCenter, chanel);
    }
    else if (index.column() == 3)
    {
        QString type = index.model()->data(index, Qt::DisplayRole).toString();

        int x = option.rect.x();
        int y = option.rect.y();
        int width = option.rect.width();
        int height = option.rect.height();

        if (type == "0")
        {
            type = "H";
        }
        else if (type == "1")
        {
            type = "L";
        }
        else if (type == "2")
        {
            type = "R";
        }
        else
        {
            type = "None";
        }


        painter->drawText(x, y, width, height, Qt::AlignVCenter, type);
    }
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
    QStyleOptionViewItem itemOption(option);
    if(itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    QPen oldPen = painter->pen();
    painter->setPen(pen);
    //painter->drawLine(option.rect.topRight(),option.rect.bottomRight());
    painter->drawLine(itemOption.rect.bottomLeft(),itemOption.rect.bottomRight());

    painter->setPen(oldPen);
}

//bool AlarmSummaryDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
//                              const QStyleOptionViewItem &option,const QModelIndex &index)
//{

//}



/*****************************************************************************************
 *
 *
 *
 * ***************************************************************************************/

AlarmSummaryDetailUI:: AlarmSummaryDetailUI(QStandardItemModel *model, QModelIndex index, QString title, QWidget *parent)
{
    initAlarmSummaryDetailUI();

    signalAndSlotConnect();

    alarmSummaryDetailShow(model, index, title);
}

void AlarmSummaryDetailUI::initAlarmSummaryDetailUI()
{
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

    closeBtn = new QPushButton(this);
    closeBtn->setObjectName(QStringLiteral("closeBtn"));
    //quitBtn->setStyleSheet("border:1px groove gray;border-radius:10px;padding:1px 2px;");
    closeBtn->setGeometry(QRect(330, 0, 40, 40));
    closeBtn->setIcon(QIcon(":/summary/Image/summary/close_1.png"));
    closeBtn->setIconSize(QSize(40, 40));
    closeBtn->setFocusPolicy(Qt::NoFocus);
    closeBtn->setFlat(true);
  //  setStyleSheet("QPushButton {\
                 border: none;\
             }");


    line = new QFrame(this);
    line->setObjectName(QStringLiteral("line"));
    line->setGeometry(QRect(30, 70, 311, 16));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    statusLabel = new QLabel(this);
    statusLabel->setObjectName(QStringLiteral("statusLabel"));
    statusLabel->setGeometry(QRect(30, 40, 321, 31));

    line_2 = new QFrame(this);
    line_2->setObjectName(QStringLiteral("line_2"));
    line_2->setGeometry(QRect(30, 170, 311, 16));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);


    tagNoLabel = new QLabel(this);
    tagNoLabel->setObjectName(QStringLiteral("tagNoLabel"));
    tagNoLabel->setGeometry(QRect(30, 80, 321, 31));

    tagLabel = new QLabel(this);
    tagLabel->setObjectName(QStringLiteral("tagLabel"));
    tagLabel->setGeometry(QRect(30, 110, 321, 31));

    chanelLabel = new QLabel(this);
    chanelLabel->setObjectName(QStringLiteral("chanelLabel"));
    chanelLabel->setGeometry(QRect(30, 140, 321, 31));

    line_3 = new QFrame(this);
    line_3->setObjectName(QStringLiteral("line_3"));
    line_3->setGeometry(QRect(30, 240, 311, 16));
    line_3->setFrameShape(QFrame::HLine);
    line_3->setFrameShadow(QFrame::Sunken);


    elecLabel = new QLabel(this);
    elecLabel->setObjectName(QStringLiteral("elecLabel"));
    elecLabel->setGeometry(QRect(30, 180, 321, 31));

    typeLabel = new QLabel(this);
    typeLabel->setObjectName(QStringLiteral("typeLabel"));
    typeLabel->setGeometry(QRect(30, 210, 321, 31));

    line_4 = new QFrame(this);
    line_4->setObjectName(QStringLiteral("line_4"));
    line_4->setGeometry(QRect(30, 280, 311, 16));
    line_4->setFrameShape(QFrame::HLine);
    line_4->setFrameShadow(QFrame::Sunken);

    timeLabel = new QLabel(this);
    timeLabel->setObjectName(QStringLiteral("timeLabel"));
    timeLabel->setGeometry(QRect(30, 250, 321, 31));

    line_5 = new QFrame(this);
    line_5->setObjectName(QStringLiteral("line_5"));
    line_5->setGeometry(QRect(10, 30, 341, 20));
    line_5->setFrameShape(QFrame::HLine);
    line_5->setFrameShadow(QFrame::Sunken);


    displayBtn = new QPushButton(this);
    displayBtn->setObjectName(QStringLiteral("displayBtn"));
    QPixmap icondisplay(":/summary/Image/summary/displayTrend.png");
    displayBtn->setGeometry(QRect(100, 300, icondisplay.width(), icondisplay.height()));
    displayBtn->setIcon(icondisplay);
    displayBtn->setIconSize(QSize(icondisplay.width(), icondisplay.height()));
    displayBtn->setFocusPolicy(Qt::NoFocus);
    displayBtn->setFlat(true);


    eventBtn = new QPushButton(this);
    eventBtn->setObjectName(QStringLiteral("eventBtn"));
    QPixmap iconevent(":/summary/Image/summary/eventTrend.png");
    eventBtn->setGeometry(QRect(200, 300, iconevent.width(), iconevent.height()));
    eventBtn->setIcon(iconevent);
    eventBtn->setIconSize(QSize(iconevent.width(), iconevent.height()));
    eventBtn->setFocusPolicy(Qt::NoFocus);
    eventBtn->setFlat(true);

    QMetaObject::connectSlotsByName(this);

    this->setGeometry((alarmWidth - 320) / 2 ,(alarmHeight - 350) / 2, 370, 350);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
}


void AlarmSummaryDetailUI::signalAndSlotConnect()
{
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    connect(displayBtn, SIGNAL(clicked()), this, SLOT(slotdisplayTrend()));
    connect(eventBtn, SIGNAL(clicked()), this, SLOT(sloteventTrend()));
}

void AlarmSummaryDetailUI::alarmSummaryDetailShow(QStandardItemModel *model, QModelIndex index, QString &title)
{
    titleLabel->setText(title);

    QModelIndex indexStatus = index.model()->index(index.row(), 0);
    statusLabel->setText(tr("状态 \t\t%1").arg(model->data(indexStatus).toString()));

    tagNoLabel->setText("标记号码 \t1");
    tagLabel->setText("标记\t\t1");

    QModelIndex indexChanel = index.model()->index(index.row(), 1);
    chanelLabel->setText(tr("通道号码 \t%1").arg(model->data(indexChanel).toString()));

    QModelIndex indexElec = index.model()->index(index.row(), 2);
    elecLabel->setText(tr("电平 \t\t%1").arg(model->data(indexElec).toString()));

    QModelIndex indexType = index.model()->index(index.row(), 3);
    QString typeName = getTypeName(model->data(indexType).toString());
    typeLabel->setText(tr("类型 \t\t%1").arg(typeName));

    QModelIndex indexTime = index.model()->index(index.row(), 4);
    timeLabel->setText(tr("时间 \t%1").arg(model->data(indexTime).toString()));
}


void AlarmSummaryDetailUI::slotdisplayTrend()
{
    QMessageBox::information(this, "至趋势(显示)", "暂无数据");
}

void AlarmSummaryDetailUI::sloteventTrend()
{
    QMessageBox::information(this, "至趋势(事件)", "暂无数据");
}


/*
** 后期需改动
*/
QString AlarmSummaryDetailUI::getTypeName(const QString & type)
{
    if (type == "0")
    {
        return "H";
    }
    else if (type == "1")
    {
        return "L";
    }
    else if (type == "2")
    {
        return "R";
    }
    else if (type == "3")
    {
        return "r";
    }
    else if (type == "4")
    {
        return "l";
    }
    else
    {
        return "";
    }
}

