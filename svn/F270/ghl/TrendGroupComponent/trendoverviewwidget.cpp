#include "trendoverviewwidget.h"

TrendOverviewWidget::TrendOverviewWidget(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

TrendOverviewWidget::~TrendOverviewWidget()
{
    release();
}

void TrendOverviewWidget::setLayoutSize()
{
    p_gLayout_main->setColumnMinimumWidth(1, rect().width()*0.1);
    p_gLayout_main->setRowMinimumHeight(0, rect().height()*0.8);
}

void TrendOverviewWidget::initialize()
{
    p_label_dateStart = new QLabel();
    p_label_dateEnd = new QLabel();

    p_pButton_close = new QPushButton();
    p_pButton_toStart = new QPushButton();
    p_pButton_toEnd = new QPushButton();
    p_pButton_toLeft = new QPushButton();
    p_pButton_toRight = new QPushButton();

    p_gLayout_main = new QGridLayout();
    p_gLayout_control = new QGridLayout();

    p_pButton_close->setText(QString("close"));
    p_label_dateStart->setText(QString("dateStart"));
    p_label_dateEnd->setText(QString("dateEnd"));

    p_pButton_toStart->setText(QString("pStart"));
    p_pButton_toEnd->setText(QString("pEnd"));
    p_pButton_toLeft->setText(QString("pLeft"));
    p_pButton_toRight->setText(QString("pRight"));
}

void TrendOverviewWidget::release()
{
    delete p_label_dateStart;
    delete p_label_dateEnd;
    delete p_pButton_close;

    delete p_pButton_toStart;
    delete p_pButton_toEnd;
    delete p_pButton_toLeft;
    delete p_pButton_toRight;

    delete p_gLayout_control;
    delete p_gLayout_main;
}

void TrendOverviewWidget::setUserDefineStyle()
{
    setStyleSheet("QLabel {border: 1px solid;}");
    p_gLayout_control->setContentsMargins(0,0,0,0);
    p_gLayout_control->setSpacing(0);
    p_gLayout_control->setMargin(0);
}

void TrendOverviewWidget::setUserDefineContent()
{

}

void TrendOverviewWidget::setWinLayout()
{
    p_gLayout_control->addWidget(p_pButton_toEnd,0,0,2,1);
    p_gLayout_control->addWidget(p_pButton_toLeft, 0,1,2,1);
    p_gLayout_control->addWidget(p_label_dateStart, 0,2,1,1);
    p_gLayout_control->addWidget(p_label_dateEnd,   1,2,1,1);
    p_gLayout_control->addWidget(p_pButton_toStart,0,3,2,1);
    p_gLayout_control->addWidget(p_pButton_toRight, 0,4,2,1);

    p_gLayout_main->addLayout(p_gLayout_control, 1,0, 1, 2);
    p_gLayout_main->addWidget(p_pButton_close, 0, 1);

    setLayout(p_gLayout_main);
    p_gLayout_main->setAlignment(p_pButton_close, Qt::AlignTop);
}

void TrendOverviewWidget::sigAndSlotConnect()
{
    connect(p_pButton_close, SIGNAL(clicked()), this, SLOT(slotSendCloseSig()));
}

void TrendOverviewWidget::slotSendCloseSig()
{
    emit(sigHide());
}

