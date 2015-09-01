#include "channelselect.h"
#include "channelbutton.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QButtonGroup>
#include <QResizeEvent>
#include <QLabel>
#include <QDebug>
ChannelSelect::ChannelSelect(QWidget *parent)
    : QWidget(parent)
    , current_width(0)
    , current_height(0)
    , current_select(0)
    , AI_Num(120)
    , DI_Num(210)
    , DO_Num(120)
    , AIGroupID(0)
    , DIGroupID(0)
    , DOGroupID(0)
    , MATHGroupID(0)
    , COMMGroupID(0)
    , numSequence(0)
    , AIHight(0)
    , DIHight(0)
    , DOHight(0)
    , boolSequence(false)
    , channelButtonWidget(NULL)
    , channelShowWidget(NULL)
    , AIWidget(NULL)
    , DIWidget(NULL)
    , DOWidget(NULL)
    , MATHWidget(NULL)
    , COMMWidget(NULL)
    , buttonAIChannel(NULL)
    , buttonDIChannel(NULL)
    , buttonDOChannel(NULL)
    , buttonMathChannel(NULL)
    , buttonCommChannel(NULL)
    , buttonUpPage(NULL)
    , buttonDownPage(NULL)
    , buttonCancel(NULL)
    , buttonOK(NULL)
    , channelAIArea(NULL)
    , channelDIArea(NULL)
    , channelDOArea(NULL)
    , channelMATHArea(NULL)
    , channelCOMMArea(NULL)
    , AIScrollBar(NULL)
    , DIScrollBar(NULL)
    , DOScrollBar(NULL)
    , MATHScrollBar(NULL)
    , COMMScrollBar(NULL)
    , AIGroup(NULL)
    , DIGroup(NULL)
    , DOGroup(NULL)
    , MATHGroup(NULL)
    , COMMGroup(NULL)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    for (int i = 0; i < 500; ++i) {
        boolAI[i] = false;
        boolDI[i] = false;
        boolDO[i] = false;
    }
    for(int i = 0; i < 300; ++i) {
        boolCOMM[i] = false;
    }
    for(int i = 0; i < 100; ++i) {
        boolMATH[i] = false;
    }
    getChannelNum();
    setWindowsSize();
    initialWindows();
    connectFunC();
}

ChannelSelect::~ChannelSelect()
{

}

void ChannelSelect::setWindowsSize()
{
    current_width = QApplication::desktop()->width();
    current_height = QApplication::desktop()->height();
    resize(current_width, current_height);
}

void ChannelSelect::initialWindows()
{
    channelButtonWidget = new QWidget(this);
    channelButtonWidget->setGeometry(0, (int)(0.1429 * current_height), (int)(0.15 * current_width), (int)(0.4962 * current_height));

    channelShowWidget = new QWidget(this);
    channelShowWidget->setGeometry(channelButtonWidget->width(), (int)(0.1429 * current_height), (int)(0.85 * current_width), (int)(0.7619 * current_height));
    channelShowWidget->setStyleSheet("background-color: rgb(220, 220, 220)");

    buttonAIChannel = new QPushButton(channelButtonWidget);
    buttonDIChannel = new QPushButton(channelButtonWidget);
    buttonDOChannel = new QPushButton(channelButtonWidget);
    buttonMathChannel = new QPushButton(channelButtonWidget);
    buttonCommChannel = new QPushButton(channelButtonWidget);

    buttonAIChannel->setText(tr("AI Channel"));
    buttonDIChannel->setText(tr("DI Channel"));
    buttonDOChannel->setText(tr("DO Channel"));
    buttonMathChannel->setText(tr("Computation Channel"));
    buttonCommChannel->setText(tr("Communication Channel"));

    buttonAIChannel->setFocusPolicy(Qt::NoFocus);
    buttonDIChannel->setFocusPolicy(Qt::NoFocus);
    buttonDOChannel->setFocusPolicy(Qt::NoFocus);
    buttonMathChannel->setFocusPolicy(Qt::NoFocus);
    buttonCommChannel->setFocusPolicy(Qt::NoFocus);

    setDefaultStyle();

    if ((0 != AI_Num) && (0 != DI_Num) && (0 != DO_Num)) {
        buttonAIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDIChannel->setGeometry(0, buttonAIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDOChannel->setGeometry(0, buttonAIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonAIChannel->height() * 3, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonAIChannel->height() * 4, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
    } else if ((0 == AI_Num) && (0 != DI_Num) && (0 != DO_Num)) {
        buttonAIChannel->setHidden(true);
        buttonDIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDOChannel->setGeometry(0, buttonDIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonDIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonDIChannel->height() * 3, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
    } else if ((0 != AI_Num) && (0 == DI_Num) && (0 != DO_Num)) {
        buttonDIChannel->setHidden(true);
        buttonAIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDOChannel->setGeometry(0, buttonAIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonAIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonAIChannel->height() * 3, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
    } else if ((0 != AI_Num) && (0 != DI_Num) && (0 == DO_Num)) {
        buttonDOChannel->setHidden(true);
        buttonAIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDIChannel->setGeometry(0, buttonAIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonAIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonAIChannel->height() * 3, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
    } else if ((0 == AI_Num) && (0 == DI_Num) && (0 != DO_Num)) {
        buttonDOChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonDOChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonDOChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonAIChannel->setHidden(true);
        buttonDIChannel->setHidden(true);
    } else if ((0 == AI_Num) && (0 != DI_Num) && (0 == DO_Num)) {
        buttonDIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonDIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonDIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonAIChannel->setHidden(true);
        buttonDOChannel->setHidden(true);
    } else if ((0 != AI_Num) && (0 == DI_Num) && (0 == DO_Num)) {
        buttonAIChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonMathChannel->setGeometry(0, buttonAIChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonAIChannel->height() * 2, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonDIChannel->setHidden(true);
        buttonDOChannel->setHidden(true);
    } else {
        buttonMathChannel->setGeometry(0, 0, channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonCommChannel->setGeometry(0, buttonMathChannel->height(), channelButtonWidget->width(), (int)(channelButtonWidget->height() / 5));
        buttonAIChannel->setHidden(true);
        buttonDIChannel->setHidden(true);
        buttonDOChannel->setHidden(true);
    }


    AIScrollBar = new QScrollBar;
    DIScrollBar = new QScrollBar;
    DOScrollBar = new QScrollBar;
    MATHScrollBar = new QScrollBar;
    COMMScrollBar = new QScrollBar;
    AIScrollBar->setStyleSheet("QScrollBar:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color:rgb(154, 206, 240);"\
                               "}"\
                               "QScrollBar::handle:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color: rgb(45, 91, 131);"\
                               "border-radius: 6px;"\
                               "}");

    DIScrollBar->setStyleSheet("QScrollBar:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color:rgb(154, 206, 240);"\
                               "}"\
                               "QScrollBar::handle:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color: rgb(45, 91, 131);"\
                               "border-radius: 6px;"\
                               "}");

    DOScrollBar->setStyleSheet("QScrollBar:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color:rgb(154, 206, 240);"\
                               "}"\
                               "QScrollBar::handle:vertical"\
                               "{"\
                               "width: 8px;"\
                               "background-color: rgb(45, 91, 131);"\
                               "border-radius: 6px;"\
                               "}");

    MATHScrollBar->setStyleSheet("QScrollBar:vertical"\
                                 "{"\
                                 "width: 8px;"\
                                 "background-color:rgb(154, 206, 240);"\
                                 "}"\
                                 "QScrollBar::handle:vertical"\
                                 "{"\
                                 "width: 8px;"\
                                 "background-color: rgb(45, 91, 131);"\
                                 "border-radius: 6px;"\
                                 "}");

    COMMScrollBar->setStyleSheet("QScrollBar:vertical"\
                                 "{"\
                                 "width: 8px;"\
                                 "background-color:rgb(154, 206, 240);"\
                                 "}"\
                                 "QScrollBar::handle:vertical"\
                                 "{"\
                                 "width: 8px;"\
                                 "background-color: rgb(45, 91, 131);"\
                                 "border-radius: 6px;"\
                                 "}");
    channelAIArea = new QScrollArea(channelShowWidget);
    channelAIArea->setGeometry(0, (int)(0.0576 * current_height), channelShowWidget->width(), (int)(0.6053 * current_height));
    channelAIArea->setVerticalScrollBar(AIScrollBar);
    channelAIArea->setFrameStyle(0);


    channelDIArea = new QScrollArea(channelShowWidget);
    channelDIArea->setGeometry(0, (int)(0.0576 * current_height), channelShowWidget->width(), (int)(0.6053 * current_height));
    channelDIArea->setVerticalScrollBar(DIScrollBar);
    channelDIArea->setFrameStyle(0);

    channelDOArea = new QScrollArea(channelShowWidget);
    channelDOArea->setGeometry(0, (int)(0.0576 * current_height), channelShowWidget->width(), (int)(0.6053 * current_height));
    channelDOArea->setVerticalScrollBar(DOScrollBar);
    channelDOArea->setFrameStyle(0);

    channelMATHArea = new QScrollArea(channelShowWidget);
    channelMATHArea->setGeometry(0, (int)(0.0576 * current_height), channelShowWidget->width(), (int)(0.6053 * current_height));
    channelMATHArea->setVerticalScrollBar(MATHScrollBar);
    channelMATHArea->setFrameStyle(0);

    channelCOMMArea = new QScrollArea(channelShowWidget);
    channelCOMMArea->setGeometry(0, (int)(0.0576 * current_height), channelShowWidget->width(), (int)(0.6053 * current_height));
    channelCOMMArea->setVerticalScrollBar(COMMScrollBar);
    channelCOMMArea->setFrameStyle(0);

    AIWidget = new QWidget(channelAIArea);
    AIGroup = new QButtonGroup;

    if ((AI_Num >=0) && (AI_Num) < 61) {
        AIHight = (int)(0.5840 * current_height);
    } else if ((AI_Num >= 61) && (AI_Num < 121 )) {
        AIHight = 2 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 121) && (AI_Num < 181)) {
        AIHight = 3 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 181) && (AI_Num <241 )) {
        AIHight = 4 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 241) && (AI_Num < 301)) {
        AIHight = 5 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 301) && (AI_Num < 361)) {
        AIHight = 6 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 361) && (AI_Num < 421)) {
        AIHight = 7 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 421) && (AI_Num < 481)) {
        AIHight = 8 * (int)(0.5840 * current_height);
    } else if ((AI_Num >= 481) && (AI_Num < 501)) {
        AIHight = 9 * (int)(0.5840 * current_height);
    } else {
        // do nothing
    }

    AIWidget->setGeometry(0, 0, channelAIArea->width(), AIHight);

    DIWidget = new QWidget(channelDIArea);
    DIGroup = new QButtonGroup;

    if ((DI_Num >=0) && (DI_Num) < 61) {
        DIHight = (int)(0.5840 * current_height);
    } else if ((DI_Num >= 61) && (DI_Num < 121 )) {
        DIHight = 2 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 121) && (DI_Num < 181)) {
        DIHight = 3 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 181) && (DI_Num < 241)) {
        DIHight = 4 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 241) && (DI_Num < 301)) {
        DIHight = 5 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 301) && (DI_Num < 361)) {
        DIHight = 6 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 361) && (DI_Num < 421)) {
        DIHight = 7 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 421) && (DI_Num < 481)) {
        DIHight = 8 * (int)(0.5840 * current_height);
    } else if ((DI_Num >= 481) && (DI_Num < 501)) {
        DIHight = 9 * (int)(0.5840 * current_height);
    } else {
        // do nothing
    }
    DIWidget->setGeometry(0, 0, channelDIArea->width(), DIHight);

    DOWidget = new QWidget(channelDOArea);
    DOGroup = new QButtonGroup;

    if ((DO_Num >=0) && (DO_Num) < 61) {
        DOHight = (int)(0.5840 * current_height);
    } else if ((DO_Num >= 61) && (DO_Num < 121 )) {
        DOHight = 2 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 121) && (DO_Num < 181)) {
        DOHight = 3 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 181) && (DO_Num <241 )) {
        DOHight = 4 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 241) && (DO_Num < 301)) {
        DOHight = 5 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 301) && (DO_Num < 361)) {
        DOHight = 6 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 361) && (DO_Num < 421)) {
        DOHight = 7 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 421) && (DO_Num < 481)) {
        DOHight = 8 * (int)(0.5840 * current_height);
    } else if ((DO_Num >= 481) && (DO_Num < 501)) {
        DOHight = 9 * (int)(0.5840 * current_height);
    } else {
        // do nothing
    }
    DOWidget->setGeometry(0, 0, channelDOArea->width(), DOHight);

    MATHWidget = new QWidget(channelMATHArea);
    MATHGroup = new QButtonGroup;

    MATHWidget->setGeometry(0, 0, channelMATHArea->width(), (2 * (int)(0.5840 * current_height)));

    COMMWidget = new QWidget(channelCOMMArea);
    COMMGroup = new QButtonGroup;

    COMMWidget->setGeometry(0, 0, channelCOMMArea->width(), (5 * (int)(0.5840 * current_height)));

    buttonUpPage = new QPushButton(channelShowWidget);
    buttonUpPage->setGeometry(0, 0 , channelShowWidget->width(), (int)(0.0576 * current_height));
    buttonUpPage->setFocusPolicy(Qt::NoFocus);
    buttonUpPage->setText("Up");

    buttonDownPage = new QPushButton(channelShowWidget);
    buttonDownPage->setGeometry(0, (int)(0.6579 * current_height) , channelShowWidget->width(), (int)(0.0576 * current_height));
    buttonDownPage->setFocusPolicy(Qt::NoFocus);
    buttonDownPage->setText("Down");

    AILayout();
    DILayout();
    DOLayout();
    MATHLayout();
    COMMLayout();

    channelAIArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    channelDIArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    channelDOArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    channelMATHArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    channelCOMMArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    channelAIArea->setWidget(AIWidget);
    channelDIArea->setWidget(DIWidget);
    channelDOArea->setWidget(DOWidget);
    channelMATHArea->setWidget(MATHWidget);
    channelCOMMArea->setWidget(COMMWidget);

    buttonCancel = new QPushButton(this);
    buttonCancel->setText(tr("Cancel"));
    buttonCancel->setGeometry((int)(0.0113 * current_width), (int)(0.9185 * current_height), (int)(0.1165 * current_width), (int)(0.0652 * current_height));

    buttonOK = new QPushButton(this);
    buttonOK->setText(tr("OK"));
    buttonOK->setGeometry((int)(0.8694 * current_width), (int)(0.9185 * current_height), (int)(0.1165 * current_width), (int)(0.0652 * current_height));
    setAllhiden();

    switch (current_select) {
    case SelectAI:
        channelAIArea->setHidden(false);
        buttonAIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");
        break;
    case SelectDI:
        channelDIArea->setHidden(false);
        buttonDIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");
        break;
    case SelectDO:
        channelDOArea->setHidden(false);
        buttonDOChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");
        break;
    default:
        channelMATHArea->setHidden(false);
        buttonMathChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");
        break;
    }

}

void ChannelSelect::getChannelNum()
{
        CfgChannel* channel = CfgChannel::instance();
        m_map_AI = channel->getExistChannelAI();
        m_map_DI = channel->getExistChannelDI();
        m_map_DO = channel->getExistChannelDO();
        m_map_MATH = channel->getExistChannelMATH();
        m_map_COMM = channel->getExistChannelCOMM();
        listEffectiveChannel = channel->getEffectiveChannel();

        AI_Num = m_map_AI.size();
        DI_Num = m_map_DI.size();
        DO_Num = m_map_DO.size();

    if (0 != AI_Num) {
        current_select = SelectAI;
    } else if (0 != DI_Num) {
        current_select = SelectDI;
    } else if (0 != DO_Num) {
        current_select = SelectDO;
    } else {
        current_select = SelectMATH;
    }
}

void ChannelSelect::setAllhiden()
{
    channelAIArea->setHidden(true);
    channelDIArea->setHidden(true);
    channelDOArea->setHidden(true);
    channelMATHArea->setHidden(true);
    channelCOMMArea->setHidden(true);
}

void ChannelSelect::AILayout()
{
    int i = 0;
    int j = 0;
    int buttonID = 0;
    for (j = 0; j < 50; ++j)
        for(i = 0; i < 10; ++i) {
            ChannelButton* btnName = new ChannelButton(AIWidget);
            connect(btnName, SIGNAL(sigMouseMove(int,int)), this, SLOT(slotMouseMove(int,int)));
            QLabel* labelName = new QLabel(btnName);
            listAI << labelName;
            listAI.at(buttonID)->setGeometry((int)(0.02 * current_width), (int)(0.0652 * current_height), (int)(0.0376 * current_width), (int)(0.0213 * current_height));
            listAI.at(buttonID)->setHidden(true);
            btnName->setFocusPolicy(Qt::NoFocus);
            btnName->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243);}");
            btnName->setGeometry((2 + i * (int)(0.0845 * current_width)), ((int)(0.01 * current_height) + (int)(0.0977 * current_height) * j), (int)(0.08 * current_width), (int)(0.0877 * current_height));
            AIGroup->addButton(btnName, buttonID);
            AIGroup->button(buttonID)->setHidden(true);
            ++buttonID;
        }

    buttonID = 0;
    for(it = m_map_AI.begin(); it != m_map_AI.end(); ++it) {
        AIGroup->button(buttonID)->setText(it.key());
        AIGroup->button(buttonID)->setHidden(false);
        ++buttonID;
    }
}

void ChannelSelect::DILayout()
{
    int i = 0;
    int j = 0;
    int buttonID = 0;
    for (j = 0; j < 50; ++j)
        for(i = 0; i < 10; ++i) {
            ChannelButton* btnName = new ChannelButton(DIWidget);
            connect(btnName, SIGNAL(sigMouseMove(int,int)), this, SLOT(slotMouseMove(int,int)));
            btnName->setFocusPolicy(Qt::NoFocus);
            QLabel* labelName = new QLabel(btnName);
            listDI << labelName;
            listDI.at(buttonID)->setGeometry((int)(0.02 * current_width), (int)(0.0652 * current_height), (int)(0.0376 * current_width), (int)(0.0213 * current_height));
            listDI.at(buttonID)->setHidden(true);
            btnName->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243);}");
            btnName->setGeometry((2 + i * (int)(0.0845 * current_width)), ((int)(0.01 * current_height) + (int)(0.0977 * current_height) * j), (int)(0.08 * current_width), (int)(0.0877 * current_height));
            DIGroup->addButton(btnName, buttonID);
            DIGroup->button(buttonID)->setHidden(true);
            ++buttonID;
        }

    buttonID = 0;
    for(it = m_map_DI.begin(); it != m_map_DI.end(); ++it) {
        DIGroup->button(buttonID)->setText(it.key());
        DIGroup->button(buttonID)->setHidden(false);
        ++buttonID;
    }
}

void ChannelSelect::DOLayout()
{
    int i = 0;
    int j = 0;
    int buttonID = 0;
    for (j = 0; j < 50; ++j)
        for(i = 0; i < 10; ++i) {
            ChannelButton* btnName = new ChannelButton(DOWidget);
            connect(btnName, SIGNAL(sigMouseMove(int,int)), this, SLOT(slotMouseMove(int,int)));
            btnName->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243);}");
            btnName->setFocusPolicy(Qt::NoFocus);
            QLabel* labelName = new QLabel(btnName);
            listDO << labelName;
            listDO.at(buttonID)->setGeometry((int)(0.02 * current_width), (int)(0.0652 * current_height), (int)(0.0376 * current_width), (int)(0.0213 * current_height));
            listDO.at(buttonID)->setHidden(true);
            btnName->setGeometry((2 + i * (int)(0.0845 * current_width)), ((int)(0.01 * current_height) + (int)(0.0977 * current_height) * j), (int)(0.08 * current_width), (int)(0.0877 * current_height));
            DOGroup->addButton(btnName, buttonID);
            DOGroup->button(buttonID)->setHidden(true);
            ++buttonID;
        }

    buttonID = 0;
    for(it = m_map_DO.begin(); it != m_map_DO.end(); ++it) {
        DOGroup->button(buttonID)->setText(it.key());
        DOGroup->button(buttonID)->setHidden(false);
        ++buttonID;
    }
}

void ChannelSelect::MATHLayout()
{
    int i = 0;
    int j = 0;
    int buttonID = 0;
    for (j = 0; j < 10; ++j)
        for(i = 0; i < 10; ++i) {
            ChannelButton* btnName = new ChannelButton(MATHWidget);
            connect(btnName, SIGNAL(sigMouseMove(int,int)), this, SLOT(slotMouseMove(int,int)));
            btnName->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243);}");
            btnName->setFocusPolicy(Qt::NoFocus);
            QLabel* labelName = new QLabel(btnName);
            listMATH << labelName;
            listMATH.at(buttonID)->setGeometry((int)(0.02 * current_width), (int)(0.0652 * current_height), (int)(0.0376 * current_width), (int)(0.0213 * current_height));
            listMATH.at(buttonID)->setHidden(true);
            btnName->setGeometry((2 + i * (int)(0.0845 * current_width)), ((int)(0.01 * current_height) + (int)(0.0977 * current_height) * j), (int)(0.08 * current_width), (int)(0.0877 * current_height));
            MATHGroup->addButton(btnName, buttonID);
            MATHGroup->button(buttonID)->setHidden(true);
            ++buttonID;
        }

    buttonID = 0;
    for(it = m_map_MATH.begin(); it != m_map_MATH.end(); ++it) {
        MATHGroup->button(buttonID)->setText(it.key());
        MATHGroup->button(buttonID)->setHidden(false);
        ++buttonID;
    }
}

void ChannelSelect::COMMLayout()
{
    int i = 0;
    int j = 0;
    int buttonID = 0;
    for (j = 0; j < 30; ++j)
        for(i = 0; i < 10; ++i) {
            ChannelButton* btnName = new ChannelButton(COMMWidget);
            connect(btnName, SIGNAL(sigMouseMove(int,int)), this, SLOT(slotMouseMove(int,int)));
            btnName->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243);}");
            btnName->setFocusPolicy(Qt::NoFocus);
            QLabel* labelName = new QLabel(btnName);
            listCOMM << labelName;
            listCOMM.at(buttonID)->setGeometry((int)(0.02 * current_width), (int)(0.0652 * current_height), (int)(0.0376 * current_width), (int)(0.0213 * current_height));
            listCOMM.at(buttonID)->setHidden(true);
            btnName->setGeometry((2 + i * (int)(0.0845 * current_width)), ((int)(0.01 * current_height) + (int)(0.0977 * current_height) * j), (int)(0.08 * current_width), (int)(0.0877 * current_height));
            COMMGroup->addButton(btnName, buttonID);
            COMMGroup->button(buttonID)->setHidden(true);
            ++buttonID;
        }
    buttonID = 0;
    for(it = m_map_COMM.begin(); it != m_map_COMM.end(); ++it) {
        COMMGroup->button(buttonID)->setText(it.key());
        COMMGroup->button(buttonID)->setHidden(false);
        ++buttonID;
    }
}

void ChannelSelect::setDefaultStyle()
{
    buttonAIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181);}");
    buttonDIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181);}");
    buttonDOChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181);}");
    buttonMathChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181);}");
    buttonCommChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181);}");
}

void ChannelSelect::setIntoShow()
{
    for (int i = 0; i < listEffectiveChannel.size(); ++i) {

    }
}

void ChannelSelect::connectFunC()
{
    connect(buttonAIChannel, SIGNAL(clicked()), this, SLOT(slotAIButtonClicked()));
    connect(buttonDIChannel, SIGNAL(clicked()), this, SLOT(slotDIButtonClicked()));
    connect(buttonDOChannel, SIGNAL(clicked()), this, SLOT(slotDOButtonClicked()));
    connect(buttonMathChannel, SIGNAL(clicked()), this, SLOT(slotMATHButtonClicked()));
    connect(buttonCommChannel, SIGNAL(clicked()), this, SLOT(slotCOMMButtonClicked()));
    connect(buttonUpPage, SIGNAL(clicked()), this, SLOT(slotUpPageClicked()));
    connect(buttonDownPage, SIGNAL(clicked()), this, SLOT(slotDownPageClicked()));
    connect(AIGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotAIChannelClicked(int)));
    connect(DIGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotDIChannelClicked(int)));
    connect(DOGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotDOChannelClicked(int)));
    connect(MATHGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotMATHChannelClicked(int)));
    connect(COMMGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotCOMMChannelClicked(int)));

    connect(AIGroup, SIGNAL(buttonPressed(int)), this, SLOT(slotAIGroupPressed(int)));
    connect(DIGroup, SIGNAL(buttonPressed(int)), this, SLOT(slotDIGroupPressed(int)));
    connect(DOGroup, SIGNAL(buttonPressed(int)), this, SLOT(slotDOGroupPressed(int)));
    connect(MATHGroup, SIGNAL(buttonPressed(int)), this, SLOT(slotMATHGroupPressed(int)));
    connect(COMMGroup, SIGNAL(buttonPressed(int)), this, SLOT(slotCOMMGroupPressed(int)));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(slotCancelClicked()));
    connect(buttonOK, SIGNAL(clicked()), this, SLOT(slotOKClicked()));
}

void ChannelSelect::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(28, 28, 28, 90));
}

void ChannelSelect::mouseReleaseEvent(QMouseEvent *)
{
    if (!boolSequence) {
        switch (current_select) {
        case SelectAI:
            boolAI[AIGroupID] = !boolAI[AIGroupID];
            break;
        case SelectDI:
            boolDI[DIGroupID] = !boolDI[DIGroupID];
            break;
        case SelectDO:
            boolDO[DOGroupID] = !boolDO[DOGroupID];
            break;
        case SelectMATH:
            boolMATH[MATHGroupID] = !boolMATH[MATHGroupID];
            break;
        case SelectCOMM:
            boolMATH[MATHGroupID] = !boolMATH[MATHGroupID];
            break;
        default:
            break;
        }
    }
}

void ChannelSelect::slotAIButtonClicked()
{
    current_select = SelectAI;
    setAllhiden();
    setDefaultStyle();
    channelAIArea->setHidden(false);
    buttonAIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");
}

void ChannelSelect::slotDIButtonClicked()
{
    current_select = SelectDI;
    setAllhiden();
    setDefaultStyle();
    channelDIArea->setHidden(false);
    buttonDIChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");

}

void ChannelSelect::slotDOButtonClicked()
{
    current_select = SelectDO;
    setAllhiden();
    setDefaultStyle();
    channelDOArea->setHidden(false);
    buttonDOChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");

}

void ChannelSelect::slotMATHButtonClicked()
{
    current_select = SelectMATH;
    setAllhiden();
    setDefaultStyle();
    channelMATHArea->setHidden(false);
    buttonMathChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");

}

void ChannelSelect::slotCOMMButtonClicked()
{
    current_select = SelectCOMM;
    setAllhiden();
    setDefaultStyle();
    channelCOMMArea->setHidden(false);
    buttonCommChannel->setStyleSheet("QPushButton{background-color: rgb(220, 220, 220); border-width: 1px; border-style: solid; border-color: rgb(220, 220, 220);}");

}

void ChannelSelect::slotUpPageClicked()
{
    switch (current_select) {
    case SelectAI:
        AIScrollBar->setValue(AIScrollBar->value() - (int)(0.583 * current_height));
        break;
    case SelectDI:
        DIScrollBar->setValue(DIScrollBar->value() - (int)(0.583 * current_height));
        break;
    case SelectDO:
        DOScrollBar->setValue(DOScrollBar->value() - (int)(0.583 * current_height));
        break;
    case SelectMATH:
        MATHScrollBar->setValue(MATHScrollBar->value() - (int)(0.583 * current_height));
        break;
    case SelectCOMM:
        COMMScrollBar->setValue(COMMScrollBar->value() - (int)(0.583 * current_height));
        break;
    default:
        break;
    }
}

void ChannelSelect::slotDownPageClicked()
{
    switch (current_select) {
    case SelectAI:
        AIScrollBar->setValue((int)(0.583 * current_height) + AIScrollBar->value());
        break;
    case SelectDI:
        DIScrollBar->setValue((int)(0.583 * current_height) + DIScrollBar->value());
        break;
    case SelectDO:
        DOScrollBar->setValue((int)(0.583 * current_height) + DOScrollBar->value());
        break;
    case SelectMATH:
        MATHScrollBar->setValue((int)(0.583 * current_height) + MATHScrollBar->value());
        break;
    case SelectCOMM:
        COMMScrollBar->setValue((int)(0.583 * current_height) + COMMScrollBar->value());
        break;
    default:
        break;
    }
}

void ChannelSelect::slotAIChannelClicked(int id)
{
    if (!boolAI[id]) {
        AIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
        if (boolSequence) {
            listAI.at(id)->setHidden(false);
            listAI.at(id)->setAlignment(Qt::AlignCenter);
            listAI.at(id)->setStyleSheet("QLabel{background-color: rgb(226, 255, 240)}");
            listAI.at(id)->setText(QString("%1").arg(numSequence++));
            listSaveClicked << listAI.at(id);
        }
        boolAI[id] = true;
    } else {
        AIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
        if (boolSequence) {
            int text = listAI.at(id)->text().toInt() + 1;
            for (int i = text; i < listSaveClicked.count(); ++i) {
                int labelText = listSaveClicked.at(i)->text().toInt() - 1;
                listSaveClicked.at(i)->setText(QString("%1").arg(labelText));
            }
            listSaveClicked.removeAt(listAI.at(id)->text().toInt());
            --numSequence;
            if (numSequence < 0)
                numSequence = 0;
            listAI.at(id)->setHidden(true);
        }
        boolAI[id] = false;
    }

}

void ChannelSelect::slotDIChannelClicked(int id)
{
    if (!boolDI[id]) {
        DIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
        if (boolSequence) {
            listDI.at(id)->setHidden(false);
            listDI.at(id)->setAlignment(Qt::AlignCenter);
            listDI.at(id)->setStyleSheet("QLabel{background-color: rgb(226, 255, 240)}");
            listDI.at(id)->setText(QString("%1").arg(numSequence++));
            listSaveClicked << listDI.at(id);
        }

        boolDI[id] = true;
    } else {
        DIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
        if (boolSequence) {
            int text = listDI.at(id)->text().toInt() + 1;
            for (int i = text; i < listSaveClicked.count(); ++i) {
                int labelText = listSaveClicked.at(i)->text().toInt() - 1;
                listSaveClicked.at(i)->setText(QString("%1").arg(labelText));
            }
            listSaveClicked.removeAt(listDI.at(id)->text().toInt());
            --numSequence;
            if (numSequence < 0)
                numSequence = 0;
            listDI.at(id)->setHidden(true);
        }
        boolDI[id] = false;
    }
}

void ChannelSelect::slotDOChannelClicked(int id)
{
    if (!boolDO[id]) {
        DOGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
        if (boolSequence) {
            listDO.at(id)->setHidden(false);
            listDO.at(id)->setAlignment(Qt::AlignCenter);
            listDO.at(id)->setStyleSheet("QLabel{background-color: rgb(226, 255, 240)}");
            listDO.at(id)->setText(QString("%1").arg(numSequence++));
            listSaveClicked << listDO.at(id);
        }
        boolDO[id] = true;
    } else {
        DOGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
        if (boolSequence) {
            int text = listDO.at(id)->text().toInt() + 1;
            for (int i = text; i < listSaveClicked.count(); ++i) {
                int labelText = listSaveClicked.at(i)->text().toInt() - 1;
                listSaveClicked.at(i)->setText(QString("%1").arg(labelText));
            }
            listSaveClicked.removeAt(listDO.at(id)->text().toInt());
            --numSequence;
            if (numSequence < 0)
                numSequence = 0;
            listDO.at(id)->setHidden(true);
        }
        boolDO[id] = false;
    }
}

void ChannelSelect::slotMATHChannelClicked(int id)
{
    if (!boolMATH[id]) {
        MATHGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
        if (boolSequence) {
            listMATH.at(id)->setHidden(false);
            listMATH.at(id)->setAlignment(Qt::AlignCenter);
            listMATH.at(id)->setStyleSheet("QLabel{background-color: rgb(226, 255, 240)}");
            listMATH.at(id)->setText(QString("%1").arg(numSequence++));
            listSaveClicked << listMATH.at(id);
        }

        boolMATH[id] = true;
    } else {
        MATHGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
        if (boolSequence) {
            int text = listMATH.at(id)->text().toInt() + 1;
            for (int i = text; i < listSaveClicked.count(); ++i) {
                int labelText = listSaveClicked.at(i)->text().toInt() - 1;
                listSaveClicked.at(i)->setText(QString("%1").arg(labelText));
            }
            listSaveClicked.removeAt(listMATH.at(id)->text().toInt());
            --numSequence;
            if (numSequence < 0)
                numSequence = 0;
            listMATH.at(id)->setHidden(true);
        }

        boolMATH[id] = false;
    }
}

void ChannelSelect::slotCOMMChannelClicked(int id)
{
    if (!boolCOMM[id]) {
        COMMGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
        if (boolSequence) {
            listCOMM.at(id)->setHidden(false);
            listCOMM.at(id)->setAlignment(Qt::AlignCenter);
            listCOMM.at(id)->setStyleSheet("QLabel{background-color: rgb(226, 255, 240)}");
            listCOMM.at(id)->setText(QString("%1").arg(numSequence++));
            listSaveClicked << listCOMM.at(id);
        }

        boolCOMM[id] = true;
    } else {
        COMMGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
        if (boolSequence) {
            int text = listCOMM.at(id)->text().toInt() + 1;
            for (int i = text; i < listSaveClicked.count(); ++i) {
                int labelText = listSaveClicked.at(i)->text().toInt() - 1;
                listSaveClicked.at(i)->setText(QString("%1").arg(labelText));
            }
            listSaveClicked.removeAt(listCOMM.at(id)->text().toInt());
            --numSequence;
            if (numSequence < 0)
                numSequence = 0;
            listCOMM.at(id)->setHidden(true);
        }
        boolCOMM[id] = false;
    }
}

void ChannelSelect::slotAIGroupPressed(int id)
{
    AIGroupID = id;
}

void ChannelSelect::slotDIGroupPressed(int id)
{
    DIGroupID = id;
}

void ChannelSelect::slotDOGroupPressed(int id)
{
    DOGroupID = id;
}

void ChannelSelect::slotCOMMGroupPressed(int id)
{
    COMMGroupID = id;
}

void ChannelSelect::slotMATHGroupPressed(int id)
{
    MATHGroupID = id;
}

void ChannelSelect::slotCancelClicked()
{
    this->close();
}

void ChannelSelect::slotOKClicked()
{

}

void ChannelSelect::slotMouseMove(int x, int y)
{
    if (!boolSequence) {
        switch (current_select) {
        case SelectAI:
        {
            int posX = AIGroup->button(AIGroupID)->x() + x;
            int posY = AIGroup->button(AIGroupID)->y() + y;
            for (int id = 0; id < AI_Num; ++id) {
                if ((posX >= AIGroup->button(id)->x()) && (posX <= AIGroup->button(id)->x() + AIGroup->button(id)->width())\
                        && (posY >= AIGroup->button(id)->y()) && (posY <= AIGroup->button(id)->y() + AIGroup->button(id)->height())) {
                    if (!boolAI[AIGroupID]) {
                        AIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
                        if (id != AIGroupID) {
                            boolAI[id] = true;
                        } else {
                            // do nothing
                        }
                    } else {
                        AIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
                        if (id != AIGroupID) {
                            boolAI[id] = false;
                        } else {
                            // do nothing
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SelectDI:
        {
            int posX = DIGroup->button(DIGroupID)->x() + x;
            int posY = DIGroup->button(DIGroupID)->y() + y;
            for (int id = 0; id < DI_Num; ++id) {
                if ((posX >= DIGroup->button(id)->x()) && (posX <= DIGroup->button(id)->x() + DIGroup->button(id)->width())\
                        && (posY >= DIGroup->button(id)->y()) && (posY <= DIGroup->button(id)->y() + DIGroup->button(id)->height())) {
                    if (!boolDI[DIGroupID]) {
                        DIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
                        if (id != DIGroupID) {
                            boolDI[id] = true;
                        } else {
                            // do nothing
                        }
                    } else {
                        DIGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
                        if (id != DIGroupID) {
                            boolDI[id] = false;
                        } else {
                            // do nothing
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SelectDO:
        {
            int posX = DOGroup->button(DOGroupID)->x() + x;
            int posY = DOGroup->button(DOGroupID)->y() + y;
            for (int id = 0; id < DO_Num; ++id) {
                if ((posX >= DOGroup->button(id)->x()) && (posX <= DOGroup->button(id)->x() + DOGroup->button(id)->width())\
                        && (posY >= DOGroup->button(id)->y()) && (posY <= DOGroup->button(id)->y() + DOGroup->button(id)->height())) {
                    if (!boolDO[DOGroupID]) {
                        DOGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
                        if (id != DOGroupID) {
                            boolDO[id] = true;
                        } else {
                            // do nothing
                        }
                    } else {
                        DOGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
                        if (id != DOGroupID) {
                            boolDO[id] = false;
                        } else {
                            // do nothing
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SelectMATH:
        {
            int posX = MATHGroup->button(MATHGroupID)->x() + x;
            int posY = MATHGroup->button(MATHGroupID)->y() + y;
            for (int id = 0; id < 100; ++id) {
                if ((posX >= MATHGroup->button(id)->x()) && (posX <= MATHGroup->button(id)->x() + MATHGroup->button(id)->width())\
                        && (posY >= MATHGroup->button(id)->y()) && (posY <= MATHGroup->button(id)->y() + MATHGroup->button(id)->height())) {
                    if (!boolMATH[MATHGroupID]) {
                        MATHGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
                        if (id != MATHGroupID) {
                            boolMATH[id] = true;
                        } else {
                            // do nothing
                        }
                    } else {
                        MATHGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
                        if (id != MATHGroupID) {
                            boolMATH[id] = false;
                        } else {
                            // do nothing
                        }
                    }
                    break;
                }
            }
            break;
        }
        case SelectCOMM:
        {
            int posX = COMMGroup->button(COMMGroupID)->x() + x;
            int posY = COMMGroup->button(COMMGroupID)->y() + y;
            for (int id = 0; id < 300; ++id) {
                if ((posX >= COMMGroup->button(id)->x()) && (posX <= COMMGroup->button(id)->x() + COMMGroup->button(id)->width())\
                        && (posY >= COMMGroup->button(id)->y()) && (posY <= COMMGroup->button(id)->y() + COMMGroup->button(id)->height())) {
                    if (!boolCOMM[COMMGroupID]) {
                        COMMGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(226, 255, 240)}");
                        if (id != COMMGroupID) {
                            boolCOMM[id] = true;
                        } else {
                            // do nothing
                        }
                    } else {
                        COMMGroup->button(id)->setStyleSheet("QPushButton{background-color: rgb(244, 255, 243)}");
                        if (id != COMMGroupID) {
                            boolCOMM[id] = false;
                        } else {
                            // do nothing
                        }
                    }
                    break;
                }
            }
            break;
        }
        default:
            break;
        }
    }
}
