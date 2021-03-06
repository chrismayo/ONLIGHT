/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：SoftKeyPad.cpp
 * 概   要：在调用该类时，画面会出现一个软件盘供用户输入
 *
 * 当前版本：V1.0.0
 * 作   者：葛 海 浪
 * 完成日期：2015-7-21
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "softkeypad.h"
#include "ui_softkeypad.h"
#include <QTextCodec>
#include <QPalette>
#include <QButtonGroup>
#include <QPainter>
#include <QDebug>
#include <QList>

/*
 * 功能：
 * 	  构造函数，初始化有限状态机并run之。
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
SoftKeyPad::SoftKeyPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::softKeyPad)
  , firstInputFlag(true)
  , shiftFlag(true)
  , firstInputLetter(true)
  , leftBtnClicked(false)
  , rightBtnClicked(false)
  , chineseInputFlag(false)
  , current_choice(0)
  , listId(0)
  , listCount(0)
  , inputLetter("")
  , singleLetter("")
  , groupBtnShow(NULL)
  , groupButtonAll(NULL)
  , inputStr("")
{
    ui->setupUi(this);
    showFullScreen();
    int i = this->height();
    qDebug() << "height is " << i;

    int j = this->width();
    qDebug() << "widget is " << j;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    /**************** 设置提示信息 ************/

    ui->textEdit->setTextColor(Qt::gray);
    ui->textEdit->setText(" 最多32个字符（全角字符：2）");
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->showTxt->setHidden(true);
    ui->textEdit_letter->setHidden(true);

    /**************** 设置汉字备选框为透明 ************/

    QPalette pl = ui->textEdit_letter->palette();
    pl.setBrush(QPalette::Base, QBrush(QColor(135, 206, 250, 0)));
    ui->textEdit_letter->setPalette(pl);
    setWindowFlags(Qt::FramelessWindowHint);
    connectDatabase();
    addGroupButtonAll();
    englishPressed();
    addGroupButtonShow();
    englishButtonClicked();
    connectFunc();
}

/*
 * 功能：
 * 	  获取用户输入的文字
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  输入框中输入的文字
 */

QString SoftKeyPad::getInputStr()
{
    inputStr = ui->textEdit->toPlainText();
    return inputStr;
}

/*
 * 功能：
 * 	  析构函数
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
SoftKeyPad::~SoftKeyPad()
{
    delete ui;
}

/*
 * 功能：
 * 	  设置界面按钮下押时候的背景雅颜色
 *
 * 参数：
 * 	  按钮ID
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotNumPressed(int id)
{
    if (50 == id) {
        ui->pushButton_Space->setStyleSheet("background-image: url(:/keypad/Image/keypad/space p.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if (51 == id) {
        ui->pushButton_Space_e->setStyleSheet("background-image: url(:/keypad/Image/keypad/space_ep.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if (24 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter p.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if ((39 == id) || (15 == id)) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/OK p.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    } else if (17 == id) {
        setDefaultShow();
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/zhong p.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    } else if (23 == id) {
        setDefaultShow();
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/ying p.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    } else if (52 == id) {
        setDefaultShow();
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/fuhao p.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    } else if (44 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/YOU P.png);font-family:'Microsoft YaHei';font-size:30px");
    } else if (32 == id){
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/zuo P.png);font-family:'Microsoft YaHei';font-size:30px");
    } else if ((33 != id) && (45 != id)) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/shuzi p.bmp);font-family:'Microsoft YaHei';font-size:30px");
    }
}

/*
 * 功能：
 * 	  设置界面按钮释放时候的背景雅颜色
 *
 * 参数：
 * 	  按钮ID
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotNumReleased(int id)
{
    if (50 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/space.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if (51 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/space_e.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if (24 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter.bmp);font-family:'Microsoft YaHei';font-size:30px");
    } else if ((39 == id) || (15 == id)) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/OK.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    } else if (44 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/YOU.png);font-family:'Microsoft YaHei';font-size:30px");
    } else if (32 == id) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/zuo.png);font-family:'Microsoft YaHei';font-size:30px");
    }
    else if ((17 != id) && (23 != id) && (52 != id) && (33 != id) && (45 != id)) {
        groupButtonAll->button(id)->setStyleSheet("background-image: url(:/keypad/Image/keypad/shuzi.bmp);font-family:'Microsoft YaHei';font-size:30px");
    }
}

/*
 * 功能：
 * 	  添加按钮组，方便管理按钮触发事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::addGroupButtonAll()
{
    groupButtonAll = new QButtonGroup;
    groupButtonAll->addButton(ui->pushButton_0, 0);
    groupButtonAll->addButton(ui->pushButton_1, 1);
    groupButtonAll->addButton(ui->pushButton_2, 2);
    groupButtonAll->addButton(ui->pushButton_3, 3);
    groupButtonAll->addButton(ui->pushButton_4, 4);
    groupButtonAll->addButton(ui->pushButton_5, 5);
    groupButtonAll->addButton(ui->pushButton_6, 6);
    groupButtonAll->addButton(ui->pushButton_7, 7);
    groupButtonAll->addButton(ui->pushButton_8, 8);
    groupButtonAll->addButton(ui->pushButton_9, 9);
    groupButtonAll->addButton(ui->pushButton_A, 10);
    groupButtonAll->addButton(ui->pushButton_B, 11);
    groupButtonAll->addButton(ui->pushButton_backSlash, 12);
    groupButtonAll->addButton(ui->pushButton_C, 14);
    groupButtonAll->addButton(ui->pushButton_Colon, 18);
    groupButtonAll->addButton(ui->pushButton_Comma, 19);
    groupButtonAll->addButton(ui->pushButton_D, 20);
    groupButtonAll->addButton(ui->pushButton_E, 22);
    groupButtonAll->addButton(ui->pushButton_F, 25);
    groupButtonAll->addButton(ui->pushButton_G, 26);
    groupButtonAll->addButton(ui->pushButton_H, 27);
    groupButtonAll->addButton(ui->pushButton_I, 28);
    groupButtonAll->addButton(ui->pushButton_J, 29);
    groupButtonAll->addButton(ui->pushButton_K, 30);
    groupButtonAll->addButton(ui->pushButton_L, 31);
    groupButtonAll->addButton(ui->pushButton_less, 34);
    groupButtonAll->addButton(ui->pushButton_M, 35);
    groupButtonAll->addButton(ui->pushButton_more, 36);
    groupButtonAll->addButton(ui->pushButton_N, 37);
    groupButtonAll->addButton(ui->pushButton_O, 38);
    groupButtonAll->addButton(ui->pushButton_P, 40);
    groupButtonAll->addButton(ui->pushButton_Period, 41);
    groupButtonAll->addButton(ui->pushButton_Q, 42);
    groupButtonAll->addButton(ui->pushButton_R, 43);
    groupButtonAll->addButton(ui->pushButton_S, 46);
    groupButtonAll->addButton(ui->pushButton_Semicolon, 47);
    groupButtonAll->addButton(ui->pushButton_slash, 49);
    groupButtonAll->addButton(ui->pushButton_T, 53);
    groupButtonAll->addButton(ui->pushButton_U, 54);
    groupButtonAll->addButton(ui->pushButton_V, 55);
    groupButtonAll->addButton(ui->pushButton_W, 56);
    groupButtonAll->addButton(ui->pushButton_X, 57);
    groupButtonAll->addButton(ui->pushButton_Y, 58);
    groupButtonAll->addButton(ui->pushButton_Z, 59);
    groupButtonAll->addButton(ui->pushButton_BS, 13);
    groupButtonAll->addButton(ui->pushButton_Cancel, 15);
    groupButtonAll->addButton(ui->pushButton_CH, 16);
    groupButtonAll->addButton(ui->pushButton_China, 17);
    groupButtonAll->addButton(ui->pushButton_DEL, 21);
    groupButtonAll->addButton(ui->pushButton_English, 23);
    groupButtonAll->addButton(ui->pushButton_Enter, 24);
    groupButtonAll->addButton(ui->pushButton_left, 32);
    groupButtonAll->addButton(ui->pushButton_LeftShift, 33);
    groupButtonAll->addButton(ui->pushButton_OK, 39);
    groupButtonAll->addButton(ui->pushButton_right, 44);
    groupButtonAll->addButton(ui->pushButton_RightShift, 45);
    groupButtonAll->addButton(ui->pushButton_SH, 48);
    groupButtonAll->addButton(ui->pushButton_Space, 50);
    groupButtonAll->addButton(ui->pushButton_Space_e, 51);
    groupButtonAll->addButton(ui->pushButton_Symbol, 52);
    groupButtonAll->addButton(ui->pushButton_ZH, 60);
}

/*
 * 功能：
 * 	  连接信号与槽
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::connectFunc()
{
    connect(groupButtonAll, SIGNAL(buttonPressed(int)), this, SLOT(slotNumPressed(int)));
    connect(groupButtonAll, SIGNAL(buttonReleased(int)), this, SLOT(slotNumReleased(int)));
    connect(groupButtonAll, SIGNAL(buttonClicked(int)), this, SLOT(slotKeyInputClicked(int)));
    connect(ui->btn_rightTurn, SIGNAL(clicked()), this, SLOT(slotRightTurnClicked()));
    connect(ui->btn_leftTurn, SIGNAL(clicked()), this, SLOT(slotLeftTurnClicked()));
    connect(groupBtnShow, SIGNAL(buttonClicked(int)), this, SLOT(slotChineseInputClicked(int)));
}

/*
 * 功能：
 * 	  设置中文状态下的界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setChineseShow()
{
    ui->pushButton_0->setText("0");
    ui->pushButton_1->setText("1");
    ui->pushButton_2->setText("2");
    ui->pushButton_3->setText("3");
    ui->pushButton_4->setText("4");
    ui->pushButton_5->setText("5");
    ui->pushButton_6->setText("6");
    ui->pushButton_7->setText("7");
    ui->pushButton_8->setText("8");
    ui->pushButton_9->setText("9");
    ui->pushButton_A->setText("a");
    ui->pushButton_B->setText("b");
    ui->pushButton_C->setText("c");
    ui->pushButton_D->setText("d");
    ui->pushButton_E->setText("e");
    ui->pushButton_F->setText("f");
    ui->pushButton_G->setText("g");
    ui->pushButton_H->setText("h");
    ui->pushButton_I->setText("i");
    ui->pushButton_J->setText("j");
    ui->pushButton_K->setText("k");
    ui->pushButton_L->setText("l");
    ui->pushButton_M->setText("m");
    ui->pushButton_N->setText("n");
    ui->pushButton_O->setText("o");
    ui->pushButton_P->setText("p");
    ui->pushButton_Q->setText("q");
    ui->pushButton_R->setText("r");
    ui->pushButton_S->setText("s");
    ui->pushButton_T->setText("t");
    ui->pushButton_U->setText("u");
    ui->pushButton_V->setText("v");
    ui->pushButton_W->setText("w");
    ui->pushButton_X->setText("x");
    ui->pushButton_Y->setText("y");
    ui->pushButton_Z->setText("z");
    ui->pushButton_less->setText("-");
    ui->pushButton_more->setText("+");
    ui->pushButton_Enter->setText("Enter");
    ui->pushButton_Comma->setText("，");
    ui->pushButton_Period->setText("。");
    ui->pushButton_Semicolon->setText(";");
    ui->pushButton_Colon->setText(":");
    ui->pushButton_LeftShift->setText("Shift");
    ui->pushButton_Space->setText("SPACE");
    ui->pushButton_Space_e->setHidden(true);
    ui->pushButton_RightShift->setText("Shift");
    ui->pushButton_CH->setText("ch");
    ui->pushButton_SH->setText("sh");
    ui->pushButton_ZH->setText("zh");
}

/*
 * 功能：
 * 	  设置英文显示界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setEnglishShow()
{
    ui->pushButton_0->setText("0");
    ui->pushButton_1->setText("1");
    ui->pushButton_2->setText("2");
    ui->pushButton_3->setText("3");
    ui->pushButton_4->setText("4");
    ui->pushButton_5->setText("5");
    ui->pushButton_6->setText("6");
    ui->pushButton_7->setText("7");
    ui->pushButton_8->setText("8");
    ui->pushButton_9->setText("9");
    ui->pushButton_A->setText("a");
    ui->pushButton_B->setText("b");
    ui->pushButton_C->setText("c");
    ui->pushButton_D->setText("d");
    ui->pushButton_E->setText("e");
    ui->pushButton_F->setText("f");
    ui->pushButton_G->setText("g");
    ui->pushButton_H->setText("h");
    ui->pushButton_I->setText("i");
    ui->pushButton_J->setText("j");
    ui->pushButton_K->setText("k");
    ui->pushButton_L->setText("l");
    ui->pushButton_M->setText("m");
    ui->pushButton_N->setText("n");
    ui->pushButton_O->setText("o");
    ui->pushButton_P->setText("p");
    ui->pushButton_Q->setText("q");
    ui->pushButton_R->setText("r");
    ui->pushButton_S->setText("s");
    ui->pushButton_T->setText("t");
    ui->pushButton_U->setText("u");
    ui->pushButton_V->setText("v");
    ui->pushButton_W->setText("w");
    ui->pushButton_X->setText("x");
    ui->pushButton_Y->setText("y");
    ui->pushButton_Z->setText("z");
    ui->pushButton_less->setText("-");
    ui->pushButton_more->setText("+");
    ui->pushButton_Enter->setText("Enter");
    ui->pushButton_Comma->setText("，");
    ui->pushButton_Period->setText("。");
    ui->pushButton_Semicolon->setText("/");
    ui->pushButton_Colon->setText("?");
    ui->pushButton_LeftShift->setText("Shift");
    ui->pushButton_Space_e->setText("SPACE");
    ui->pushButton_Space_e->setGeometry(230, 516, 604, 76);
    ui->pushButton_RightShift->setText("Shift");
    ui->pushButton_CH->setHidden(true);
    ui->pushButton_SH->setHidden(true);
    ui->pushButton_ZH->setHidden(true);
    ui->pushButton_Space->setHidden(true);
    ui->pushButton_Space_e->setHidden(false);
}

/*
 * 功能：
 * 	  设置符号显示界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setSymbolShow()
{
    ui->pushButton_0->setText("(");
    ui->pushButton_1->setText("~");
    ui->pushButton_2->setText("!");
    ui->pushButton_3->setText("@");
    ui->pushButton_4->setText("#");
    ui->pushButton_5->setText("$");
    ui->pushButton_6->setText("%");
    ui->pushButton_7->setText("^");
    ui->pushButton_8->setText("&&");
    ui->pushButton_9->setText("*");
    ui->pushButton_A->setText("|");
    ui->pushButton_B->setText("B");
    ui->pushButton_C->setText("μ");
    ui->pushButton_D->setText(">");
    ui->pushButton_E->setText(".");
    ui->pushButton_F->setText("{");
    ui->pushButton_G->setText("}");
    ui->pushButton_H->setText("[");
    ui->pushButton_I->setText("+");
    ui->pushButton_J->setText("]");
    ui->pushButton_K->setText("·");
    ui->pushButton_L->setText("。");
    ui->pushButton_M->setHidden(true);
    ui->pushButton_N->setHidden(true);
    ui->pushButton_O->setText("-");
    ui->pushButton_P->setText("/");
    ui->pushButton_Q->setText("\"");
    ui->pushButton_R->setText(":");
    ui->pushButton_S->setText("<");
    ui->pushButton_T->setText("?");
    ui->pushButton_U->setText("=");
    ui->pushButton_V->setText("℃");
    ui->pushButton_W->setText("\'");
    ui->pushButton_X->setText("±");
    ui->pushButton_Y->setText("—");
    ui->pushButton_Z->setText("￥");
    ui->pushButton_less->setText(")");
    ui->pushButton_more->setText("\\");
    ui->pushButton_backSlash->setText("÷");
    ui->pushButton_slash->setText("×");
    ui->pushButton_Space_e->setHidden(true);
    ui->pushButton_Enter->setHidden(true);
    ui->pushButton_Comma->setHidden(true);
    ui->pushButton_Period->setHidden(true);
    ui->pushButton_Semicolon->setHidden(true);
    ui->pushButton_Colon->setHidden(true);
    ui->pushButton_LeftShift->setHidden(true);
    ui->pushButton_Space->setHidden(true);
    ui->pushButton_Space_e->setHidden(true);
    ui->pushButton_RightShift->setHidden(true);
    ui->pushButton_CH->setHidden(true);
    ui->pushButton_SH->setHidden(true);
    ui->pushButton_ZH->setHidden(true);
    ui->pushButton_slash->setHidden(false);
    ui->pushButton_backSlash->setHidden(false);

}

/*
 * 功能：
 * 	  隐藏特定的按钮
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setNumShow()
{
    ui->pushButton_Enter->setHidden(false);
    ui->pushButton_Comma->setHidden(false);
    ui->pushButton_Period->setHidden(false);
    ui->pushButton_Semicolon->setHidden(false);
    ui->pushButton_Colon->setHidden(false);
    ui->pushButton_LeftShift->setHidden(false);
    ui->pushButton_Space->setHidden(false);
    ui->pushButton_RightShift->setHidden(false);
    ui->pushButton_CH->setHidden(false);
    ui->pushButton_SH->setHidden(false);
    ui->pushButton_ZH->setHidden(false);
    ui->pushButton_M->setHidden(false);
    ui->pushButton_N->setHidden(false);
    ui->pushButton_slash->setHidden(true);
    ui->pushButton_backSlash->setHidden(true);
}

/*
 * 功能：
 * 	  设置中文英文符号这三个按钮的默认背景颜色
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setDefaultShow()
{
    ui->pushButton_English->setStyleSheet("background-image: url(:/keypad/Image/keypad/ying.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    ui->pushButton_China->setStyleSheet("background-image: url(:/keypad/Image/keypad/zhong.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
    ui->pushButton_Symbol->setStyleSheet("background-image: url(:/keypad/Image/keypad/fuhao.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
}

/*
 * 功能：
 * 	  设置英文状态时按钮的颜色背景
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::englishPressed()
{
    setDefaultShow();
    ui->pushButton_English->setStyleSheet("background-image: url(:/keypad/Image/keypad/ying p.bmp);font-family:'Microsoft YaHei';font-size:30px;color:white");
}

/*
 * 功能：
 * 	  设置字母大写状态下的界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::ABCShow()
{
    ui->pushButton_0->setText(")");
    ui->pushButton_1->setText("!");
    ui->pushButton_2->setText("@");
    ui->pushButton_3->setText("#");
    ui->pushButton_4->setText("$");
    ui->pushButton_5->setText("%");
    ui->pushButton_6->setText("^");
    ui->pushButton_7->setText("&&");    // button中'&'符号有特殊含义，两个'&'显示一个
    ui->pushButton_8->setText("*");
    ui->pushButton_9->setText("(");
    ui->pushButton_A->setText("A");
    ui->pushButton_B->setText("B");
    ui->pushButton_C->setText("C");
    ui->pushButton_D->setText("D");
    ui->pushButton_E->setText("E");
    ui->pushButton_F->setText("F");
    ui->pushButton_G->setText("G");
    ui->pushButton_H->setText("H");
    ui->pushButton_I->setText("I");
    ui->pushButton_J->setText("J");
    ui->pushButton_K->setText("K");
    ui->pushButton_L->setText("L");
    ui->pushButton_M->setText("M");
    ui->pushButton_N->setText("N");
    ui->pushButton_O->setText("O");
    ui->pushButton_P->setText("P");
    ui->pushButton_Q->setText("Q");
    ui->pushButton_R->setText("R");
    ui->pushButton_S->setText("S");
    ui->pushButton_T->setText("T");
    ui->pushButton_U->setText("U");
    ui->pushButton_V->setText("V");
    ui->pushButton_W->setText("W");
    ui->pushButton_X->setText("X");
    ui->pushButton_Y->setText("Y");
    ui->pushButton_Z->setText("Z");
    ui->pushButton_less->setText("-");
    ui->pushButton_more->setText("+");
    ui->pushButton_Enter->setText("Enter");
    ui->pushButton_Comma->setText("，");
    ui->pushButton_Period->setText("。");
    ui->pushButton_Semicolon->setText("/");
    ui->pushButton_Colon->setText("?");
    ui->pushButton_LeftShift->setText("Shift");
    ui->pushButton_Space_e->setText("SPACE");
    ui->pushButton_Space_e->setGeometry(230, 516, 604, 76);
    ui->pushButton_RightShift->setText("Shift");
    ui->pushButton_CH->setHidden(true);
    ui->pushButton_SH->setHidden(true);
    ui->pushButton_ZH->setHidden(true);
    ui->pushButton_Space->setHidden(true);
    ui->pushButton_Space_e->setHidden(false);
}

/*
 * 功能：
 * 	  选择英文输入时要显示的界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::englishButtonClicked()
{
    current_choice = KeyInput_English;      // 设置当前的输入状态标识为英文
    setNumShow();
    setEnglishShow();
}

/*
 * 功能：
 * 	  shift下押时显示的背景(大写)
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::shiftABC()
{
    ui->pushButton_RightShift->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter p.bmp);font-family:'Microsoft YaHei';font-size:30px");
    ui->pushButton_LeftShift->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter p.bmp);font-family:'Microsoft YaHei';font-size:30px");

    /**************** 大小写切换标志符 ************/
    shiftFlag = false;
}

/*
 * 功能：
 * 	  shift下押时显示的背景(小写)
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::shiftabc()
{
    ui->pushButton_RightShift->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter.bmp);font-family:'Microsoft YaHei';font-size:30px");
    ui->pushButton_LeftShift->setStyleSheet("background-image: url(:/keypad/Image/keypad/enter.bmp);font-family:'Microsoft YaHei';font-size:30px");

    /**************** 大小写切换标志符 ************/
    shiftFlag = true;
}

/*
 * 功能：
 * 	  数据库连接
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::connectDatabase()
{
    /**************** 添加sqlite数据库驱动 ************/
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
//    if (QSqlDatabase::contains("china.db")) {
//        db = QSqlDatabase::database("china.db");
//    } else {
//         db = QSqlDatabase::addDatabase("QSQLITE", "china.db");
//         db.setDatabaseName("china.db");
//    }
    if(db.open()) {
        qDebug() << "db open successful!";
    } else {
        qDebug() << "db open failure!";
    }

    query = QSqlQuery(db);
    if(db.open()) {
        qDebug() << "db open successful!";
    } else {
        qDebug() << "db open failure!";
    }

    query = QSqlQuery("china.db");
}

/*
 * 功能：
 * 	  汉字备选框中的按钮设置为一个按钮组
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::addGroupButtonShow()
{
    groupBtnShow = new QButtonGroup;
    groupBtnShow->addButton(ui->btn1, 0);
    groupBtnShow->addButton(ui->btn2, 1);
    groupBtnShow->addButton(ui->btn3, 2);
    groupBtnShow->addButton(ui->btn4, 3);
    groupBtnShow->addButton(ui->btn5, 4);
    groupBtnShow->addButton(ui->btn6, 5);
    groupBtnShow->addButton(ui->btn7, 6);
    groupBtnShow->addButton(ui->btn8, 7);
}

/*
 * 功能：
 * 	  SQL执行语句
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::sqlSelect()
{
    /**************** 根据首字母查询对应的表 ************/
    if ("a" == singleLetter) {
        if(query.exec(QString("select word from pinyin_a where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_a successful!";
        } else {
            qDebug() << "query from pinyin_a fail!";
        }
        qDebug() << "select from pinyin_a";
    } else if ("b" == singleLetter) {
        if(query.exec(QString("select word from pinyin_b where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_b successful!";
        } else {
            qDebug() << "query from pinyin_b fail!";
        }
        qDebug() << "select from pinyin_b";
    } else if (("c" == singleLetter) || ("ch" == singleLetter)) {
        if(query.exec(QString("select word from pinyin_c where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_c successful!";
        } else {
            qDebug() << "query from pinyin_c fail!";
        }
        qDebug() << "select from pinyin_c";
    } else if ("d" == singleLetter) {
        if(query.exec(QString("select word from pinyin_d where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_d successful!";
        } else {
            qDebug() << "query from pinyin_d fail!";
        }
        qDebug() << "select from pinyin_d";
    } else if ("e" == singleLetter) {
        if(query.exec(QString("select word from pinyin_e where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_e successful!";
        } else {
            qDebug() << "query from pinyin_e fail!";
        }
        qDebug() << "select from pinyin_e";
    } else if ("f" == singleLetter) {
        if(query.exec(QString("select word from pinyin_f where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_f successful!";
        } else {
            qDebug() << "query from pinyin_f fail!";
        }
        qDebug() << "select from pinyin_f";
    } else if ("g" == singleLetter) {
        if(query.exec(QString("select word from pinyin_g where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_g successful!";
        } else {
            qDebug() << "query from pinyin_g fail!";
        }
        qDebug() << "select from pinyin_g";
    } else if ("h" == singleLetter) {
        if(query.exec(QString("select word from pinyin_h where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_h successful!";
        } else {
            qDebug() << "query from pinyin_h fail!";
        }
        qDebug() << "select from pinyin_h";
    } else if ("i" == singleLetter) {
        if(query.exec(QString("select word from pinyin_i where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_i successful!";
        } else {
            qDebug() << "query from pinyin_i fail!";
        }
        qDebug() << "select from pinyin_i";
    } else if ("j" == singleLetter) {
        if(query.exec(QString("select word from pinyin_j where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_j successful!";
        } else {
            qDebug() << "query from pinyin_j fail!";
        }
        qDebug() << "select from pinyin_j";
    } else if ("k" == singleLetter) {
        if(query.exec(QString("select word from pinyin_k where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_k successful!";
        } else {
            qDebug() << "query from pinyin_k fail!";
        }
        qDebug() << "select from pinyin_k";
    } else if ("l" == singleLetter) {
        if(query.exec(QString("select word from pinyin_l where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_l successful!";
        } else {
            qDebug() << "query from pinyin_l fail!";
        }
        qDebug() << "select from pinyin_l";
    } else if ("m" == singleLetter) {
        if(query.exec(QString("select word from pinyin_m where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_m successful!";
        } else {
            qDebug() << "query from pinyin_m fail!";
        }
        qDebug() << "select from pinyin_m";
    } else if ("n" == singleLetter) {
        if(query.exec(QString("select word from pinyin_n where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_n successful!";
        } else {
            qDebug() << "query from pinyin_n fail!";
        }
        qDebug() << "select from pinyin_n";
    } else if ("o" == singleLetter) {
        if(query.exec(QString("select word from pinyin_o where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_o successful!";
        } else {
            qDebug() << "query from pinyin_o fail!";
        }
        qDebug() << "select from pinyin_o";
    } else if ("p" == singleLetter) {
        if(query.exec(QString("select word from pinyin_p where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_p successful!";
        } else {
            qDebug() << "query from pinyin_p fail!";
        }
        qDebug() << "select from pinyin_p";
    } else if ("q" == singleLetter) {
        if(query.exec(QString("select word from pinyin_q where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_q successful!";
        } else {
            qDebug() << "query from pinyin_q fail!";
        }
        qDebug() << "select from pinyin_q";
    } else if ("r" == singleLetter) {
        if(query.exec(QString("select word from pinyin_r where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_r successful!";
        } else {
            qDebug() << "query from pinyin_r fail!";
        }
        qDebug() << "select from pinyin_r";
    } else if (("s" == singleLetter) || ("sh" == singleLetter)) {
        if(query.exec(QString("select word from pinyin_s where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_s successful!";
        } else {
            qDebug() << "query from pinyin_s fail!";
        }
        qDebug() << "select from pinyin_s";
    } else if ("t" == singleLetter) {
        if(query.exec(QString("select word from pinyin_t where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_t successful!";
        } else {
            qDebug() << "query from pinyin_t fail!";
        }
        qDebug() << "select from pinyin_t";
    } else if ("u" == singleLetter) {
        if(query.exec(QString("select word from pinyin_u where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_u successful!";
        } else {
            qDebug() << "query from pinyin_u fail!";
        }
        qDebug() << "select from pinyin_u";
    }  else if ("v" == singleLetter) {
        if(query.exec(QString("select word from pinyin_v where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_v successful!";
        } else {
            qDebug() << "query from pinyin_v fail!";
        }
        qDebug() << "select from pinyin_v";
    } else if ("w" == singleLetter) {
        if(query.exec(QString("select word from pinyin_w where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_w successful!";
        } else {
            qDebug() << "query from pinyin_w fail!";
        }
        qDebug() << "select from pinyin_w";
    } else if ("x" == singleLetter) {
        if(query.exec(QString("select word from pinyin_x where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_x successful!";
        } else {
            qDebug() << "query from pinyin_x fail!";
        }
        qDebug() << "select from pinyin_x";
    } else if ("y" == singleLetter) {
        if(query.exec(QString("select word from pinyin_y where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_y successful!";
        } else {
            qDebug() << "query from pinyin_y fail!";
        }
        qDebug() << "select from pinyin_y";
    } else if (("z" == singleLetter) || ("zh" == singleLetter)) {
        if(query.exec(QString("select word from pinyin_z where pinyin like '" + inputLetter + "%'"))) {
            qDebug() << "query from pinyin_z successful!";
        } else {
            qDebug() << "query from pinyin_z fail!";
        }
        qDebug() << "select from pinyin_z";
    }

    /**************** 将查询到的汉字插入到list链表中 ************/
    while(query.next()) {
        list << query.value(0).toString();
    }

    /**************** 统计list中string的数量 ************/
    listCount = list.count();
}

/*
 * 功能：
 * 	  软件盘按钮被点击时会触发该函数，实现文字输入以及其他附加功能
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotKeyInputClicked(int id)
{
    /**************** 通用按钮事件处理 ************/
    if (17 == id) {   // china_button
        current_choice = KeyInput_Chinese;
        setNumShow();
        setChineseShow();
    } else if (23 == id) {   // english_button
        current_choice = KeyInput_English;
        setNumShow();
        setEnglishShow();
    } else if (52 == id) {   //symbol_button
        current_choice = KeyInput_Symbol;
        setNumShow();
        setSymbolShow();
    } else if (15 == id) {  //取消按钮压下
        /**************** 清空文本框内容 ************/
        ui->textEdit->setText("");
    } else if (24 == id) {  //enter button click
        if (firstInputFlag == true) {
            /**************** 消除提示信息 ************/
            ui->textEdit->setText("");
            firstInputFlag = false;
        }
        if ((KeyInput_Chinese == current_choice) && (ui->textEdit_letter->toPlainText() != "")) {
            ui->textEdit->insertPlainText(ui->textEdit_letter->toPlainText());
            ui->textEdit_letter->setText("");
            ui->textEdit_letter->setHidden(true);
            ui->showTxt->setHidden(true);
            firstInputLetter = true;
        } else {
            /**************** 发送信号 ************/
            emit sigOkPressSignal();
        }

    }
    else if (39 == id) {  //OK 按钮下压
        /**************** 发送信号 ************/
        emit sigOkPressSignal();
    } else if (13 == id) {     // BS button click
        if ((KeyInput_Chinese == current_choice) && (ui->textEdit_letter->toPlainText() != "")) {
            listId = 0;
            list.clear();
            course = ui->textEdit_letter->textCursor();
            course.deletePreviousChar();
            inputLetter = ui->textEdit_letter->toPlainText().toLower();
            if ("" == inputLetter) {
                ui->textEdit_letter->setHidden(true);
                ui->showTxt->setHidden(true);
                firstInputLetter = true;
            } else {
                ui->showTxt->setHidden(false);
                sqlSelect();
                if (0 == listCount) {
                    ui->showTxt->setHidden(true);
                } else if (1 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText("");
                    ui->btn3->setText("");
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (2 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText("");
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (3 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (4 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText(list.at(3));
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (5 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText(list.at(3));
                    ui->btn5->setText(list.at(5));
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (6 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText(list.at(3));
                    ui->btn5->setText(list.at(4));
                    ui->btn6->setText(list.at(5));
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (7 == listCount) {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText(list.at(3));
                    ui->btn5->setText(list.at(4));
                    ui->btn6->setText(list.at(5));
                    ui->btn7->setText(list.at(6));
                    ui->btn8->setText("");
                } else {
                    ui->btn1->setText(list.at(0));
                    ui->btn2->setText(list.at(1));
                    ui->btn3->setText(list.at(2));
                    ui->btn4->setText(list.at(3));
                    ui->btn5->setText(list.at(4));
                    ui->btn6->setText(list.at(5));
                    ui->btn7->setText(list.at(6));
                    ui->btn8->setText(list.at(7));
                    ui->btn_rightTurn->setEnabled(true);
                    listId = 8;
                }
                qDebug() << "DEL button listCount is " << listCount << " listId is " <<listId;
            }
        } else {
            course = ui->textEdit->textCursor();
            course.deletePreviousChar();
        }

    } else if (21 == id) { // DEL button click
        if ((KeyInput_Chinese == current_choice) && (ui->textEdit_letter->toPlainText() != "")) {
            // do nothing
        } else {
            course = ui->textEdit->textCursor();
            course.deleteChar();
            course.movePosition(QTextCursor::NoMove);
            ui->textEdit->setTextCursor(course);
        }

    } else if (32 == id) {    // left move Button click
        if ((KeyInput_Chinese == current_choice) && (ui->textEdit_letter->toPlainText() != "")) {
            // do nothing
        } else {
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::PreviousCharacter);
            ui->textEdit->setTextCursor(course);
        }
    } else if (44 == id) {   // right move Button click
        if ((KeyInput_Chinese == current_choice) && (ui->textEdit_letter->toPlainText() != "")) {
            // do nothing
        } else {
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::NextCharacter);
            ui->textEdit->setTextCursor(course);
        }
    }

    ui->textEdit->setTextColor(Qt::black);
    if (KeyInput_English == current_choice) {
        if ((33 == id) || (45 == id)) {  // left or right shift click
            if (true == shiftFlag) {
                ABCShow();
                shiftABC();
            } else {
                setEnglishShow();
                shiftabc();
            }
        } else if (51 == id) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            ui->textEdit->insertPlainText(" ");
        } else if (7 == id) {   // '&'符号单独处理，因为Qt中button按钮'&'有特殊含义，需要2个'&'符号才能显示出“&”
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            if (false == shiftFlag) {
                ui->textEdit->insertPlainText("&");
            } else {
                ui->textEdit->insertPlainText("7");
            }
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::NextCell);
            ui->textEdit->setTextCursor(course);
            setEnglishShow();
            shiftabc();
        }
        else if ((13 != id) && (15 != id) && (17 != id) && (21 != id) && (23 != id)
                 && (24 != id) && (32 != id) && (39 != id) && (44 != id) && (52 != id)) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            ui->textEdit->insertPlainText(groupButtonAll->button(id)->text());
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::NextCell);
            ui->textEdit->setTextCursor(course);
            setEnglishShow();
            shiftabc();
        }
    } else if (KeyInput_Symbol == current_choice) {
        if (8 == id) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            ui->textEdit->insertPlainText("&");
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::NextCell);
            ui->textEdit->setTextCursor(course);
        } else if ((13 != id) && (15 != id) && (17 != id) && (21 != id)
                   && (23 != id) && (32 != id) && (39 != id) && (44 != id) && (52 != id)) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            ui->textEdit->insertPlainText(groupButtonAll->button(id)->text());
            course = ui->textEdit->textCursor();
            course.movePosition(QTextCursor::NextCell);
            ui->textEdit->setTextCursor(course);
        }
    } else if (KeyInput_Chinese == current_choice) {
        if ((10 == id) || (11 == id) || (14 == id) || (20 == id) || (22 == id) || (25 == id)
                || (26 == id) || (27 == id) || (28 == id) || (29 == id) || (30 == id) || (31 == id)
                || (35 == id) || (37 == id) || (38 == id) || (40 == id) || (42 == id) || (43 == id)
                || (46 == id) || (53 == id) || (54 == id) || (55 == id) || (56 == id) || (57 == id)
                || (58 == id) || (59 == id) || (16 == id) || (48 == id) || (60 == id)) {
            list.clear();

            /**************** chineseInout 为true时，数字按钮和标点符号按钮无效 ************/
            chineseInputFlag = true;
            if (true == firstInputLetter) { // 判断是否是第一个字符
                singleLetter = groupButtonAll->button(id)->text().toLower();
                inputLetter = "";
                firstInputLetter = false;
            }
            ui->textEdit_letter->setHidden(false);
            ui->textEdit_letter->insertPlainText(groupButtonAll->button(id)->text());
            inputLetter = ui->textEdit_letter->toPlainText().toLower();
            sqlSelect();
            ui->btn_leftTurn->setEnabled(false);
            listId = 0;
            slotRightTurnClicked();
            setNumShow();
            setChineseShow();
            shiftabc();
        } else if ((0 == id) || (1 == id) || (2 == id) || (3 == id) || (4 == id) || ( 5 == id)
                   ||(6 == id) || (7 == id) || (8 == id) || (9 == id) || (18 == id) || (19 == id)
                   || (34 == id) || (36 == id) ||(41 == id) || (47 ==id)) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            if (true == chineseInputFlag) {
                // do nothing
            } else {
                ui->textEdit->insertPlainText(groupButtonAll->button(id)->text());
                course = ui->textEdit->textCursor();
                course.movePosition(QTextCursor::NextCell);
                ui->textEdit->setTextCursor(course);
                setNumShow();
                setChineseShow();
                shiftabc();
            }
        } else if ((33 == id) || (45 == id)) {
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            if (true == shiftFlag) {
                ABCShow();
                shiftABC();
            } else {
                setNumShow();
                setChineseShow();
                shiftabc();
            }
        } else if (24 == id) {  // enter button pressed
            // do nothing
        } else if ((50 == id) || (51 == id)) { // space button press
            if (firstInputFlag == true) {   // 消除提示信息
                ui->textEdit->setText("");
                firstInputFlag = false;
            }
            if (true == chineseInputFlag) {
                // do nothing
            } else {
                ui->textEdit->insertPlainText(" ");
            }
            setNumShow();
            setChineseShow();
            shiftabc();
        }
    }

    /**************** 文本框为空时，显示提示信息 ************/
    if (ui->textEdit->toPlainText() == "") {
        ui->textEdit->setTextColor(Qt::gray);
        ui->textEdit->setText(" 最多32个字符（全角字符：2）");
        firstInputFlag = true;
    } else {
        ui->textEdit->setTextColor(Qt::black);
    }
}

/*
 * 功能：
 * 	  中文状态下用户选择备选框中的向左翻页按钮时触发该函数
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotLeftTurnClicked()
{
    leftBtnClicked = true;
    if (true == rightBtnClicked) {
        if (0 == (listId % 8)) {
            listId -= 9;
        } else if (1 == (listId % 8)) {
            listId -= 2;
        } else if (2 == (listId % 8)) {
            listId -= 3;
        } else if (3 == (listId % 8)) {
            listId -= 4;
        } else if (4 == (listId % 8)) {
            listId -= 5;
        } else if (5 == (listId % 8)) {
            listId -= 6;
        } else if (6 == (listId % 8)) {
            listId -= 7;
        } else if (7 == (listId % 8)) {
            listId -= 8;
        }
        rightBtnClicked = false;
    }
    if (listId < 9) {
        ui->btn_leftTurn->setEnabled(false);
    } else {
        ui->btn_leftTurn->setEnabled(true);
    }
    ui->btn_rightTurn->setEnabled(true);
    while(!(listId < 0)) {
        groupBtnShow->button(listId % 8)->setText(list.at(listId));
        --listId;
        if ((0 == ((listId+1) % 8)) && (0 != listId))
            break;
    }
    if (listId < 0) {
        listId = 0;
    }
}

/*
 * 功能：
 * 	  重写paintEvent事件，使窗体透明
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(this->rect(),QColor(28, 28, 28, 100));
}

/*
 * 功能：
 * 	  中文状态下用户选择备选框中的向右翻页按钮时触发该函数
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotRightTurnClicked()
{
    rightBtnClicked = true;
    if (leftBtnClicked) {
        listId += 8;
        leftBtnClicked = false;
    } else {
        // do nothing
    }
    if (0 == listCount) {
        /******************** 如果查询不到数据，汉字显示栏不显示 **********************/
        ui->showTxt->setHidden(true);
    } else {
        ui->showTxt->setHidden(false);
        while(listId < listCount) {
            groupBtnShow->button(listId % 8)->setText(list.at(listId));
            if(++listId == listCount) {
                if (0 == (listId % 8)) {
                    // do nothing
                } else if (1 == (listId % 8)) {
                    ui->btn2->setText("");
                    ui->btn3->setText("");
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (2 == (listId % 8)) {
                    ui->btn3->setText("");
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (3 == (listId % 8)) {
                    ui->btn4->setText("");
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (4 == (listId % 8)) {
                    ui->btn5->setText("");
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (5 == (listId % 8)) {
                    ui->btn6->setText("");
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (6 == (listId % 8)) {
                    ui->btn7->setText("");
                    ui->btn8->setText("");
                } else if (7 == (listId % 8)) {
                    ui->btn8->setText("");
                }
                ui->btn_rightTurn->setEnabled(false);
            } else {
                ui->btn_rightTurn->setEnabled(true);
            }
            if (0 == (listId % 8))
                break;
        }
        if (listId < 9) {
            ui->btn_leftTurn->setEnabled(false);
        } else {
            ui->btn_leftTurn->setEnabled(true);
        }
    }
}

/*
 * 功能：
 * 	  中文状态下用户选择备选框中的中文时触发该函数
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotChineseInputClicked(int id)
{
    if (firstInputFlag == true) {   // 消除提示信息
        ui->textEdit->setText("");
        firstInputFlag = false;
    }
    ui->textEdit->insertPlainText(groupBtnShow->button(id)->text());
    ui->textEdit_letter->setText("");
    ui->textEdit_letter->setHidden(true);
    course = ui->textEdit->textCursor();
    course.movePosition(QTextCursor::NextCell);
    ui->textEdit->setTextCursor(course);
    setChineseShow();
    shiftabc();
    list.clear();
    firstInputLetter = true;
    chineseInputFlag = false;
    ui->showTxt->setHidden(true);
}
