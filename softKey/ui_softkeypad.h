/********************************************************************************
** Form generated from reading UI file 'softkeypad.ui'
**
** Created: Thu Jul 16 11:38:37 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTKEYPAD_H
#define UI_SOFTKEYPAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_softKeyPad
{
public:
    QWidget *widget;
    QTextEdit *textEdit;
    QPushButton *pushButton_7;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_1;
    QPushButton *pushButton_9;
    QPushButton *pushButton_6;
    QPushButton *pushButton_left;
    QPushButton *pushButton_BS;
    QPushButton *pushButton_DEL;
    QPushButton *pushButton_0;
    QPushButton *pushButton_right;
    QPushButton *pushButton_less;
    QPushButton *pushButton_T;
    QPushButton *pushButton_W;
    QPushButton *pushButton_Y;
    QPushButton *pushButton_E;
    QPushButton *pushButton_Q;
    QPushButton *pushButton_U;
    QPushButton *pushButton_R;
    QPushButton *pushButton_I;
    QPushButton *pushButton_more;
    QPushButton *pushButton_O;
    QPushButton *pushButton_P;
    QPushButton *pushButton_A;
    QPushButton *pushButton_J;
    QPushButton *pushButton_S;
    QPushButton *pushButton_D;
    QPushButton *pushButton_H;
    QPushButton *pushButton_G;
    QPushButton *pushButton_K;
    QPushButton *pushButton_L;
    QPushButton *pushButton_F;
    QPushButton *pushButton_slash;
    QPushButton *pushButton_backSlash;
    QPushButton *pushButton_Enter;
    QPushButton *pushButton_M;
    QPushButton *pushButton_B;
    QPushButton *pushButton_X;
    QPushButton *pushButton_V;
    QPushButton *pushButton_N;
    QPushButton *pushButton_Period;
    QPushButton *pushButton_Z;
    QPushButton *pushButton_C;
    QPushButton *pushButton_Comma;
    QPushButton *pushButton_Semicolon;
    QPushButton *pushButton_Colon;
    QPushButton *pushButton_ZH;
    QPushButton *pushButton_SH;
    QPushButton *pushButton_CH;
    QPushButton *pushButton_Space;
    QPushButton *pushButton_LeftShift;
    QPushButton *pushButton_RightShift;
    QPushButton *pushButton_China;
    QPushButton *pushButton_Symbol;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_English;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Space_e;
    QWidget *showTxt;
    QPushButton *btn8;
    QPushButton *btn4;
    QPushButton *btn7;
    QPushButton *btn6;
    QPushButton *btn_leftTurn;
    QPushButton *btn5;
    QPushButton *btn1;
    QPushButton *btn3;
    QPushButton *btn2;
    QPushButton *btn_rightTurn;
    QTextEdit *textEdit_letter;

    void setupUi(QWidget *softKeyPad)
    {
        if (softKeyPad->objectName().isEmpty())
            softKeyPad->setObjectName(QString::fromUtf8("softKeyPad"));
        softKeyPad->resize(1064, 800);
        widget = new QWidget(softKeyPad);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 113, 1065, 685));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/image/beij.png);"));
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(54, 24, 781, 158));
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai HK"));
        font.setPointSize(22);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(582, 188, 76, 76));
        pushButton_7->setFocusPolicy(Qt::NoFocus);
        pushButton_7->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_7->setFlat(true);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(142, 188, 76, 76));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        pushButton_2->setFont(font1);
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_2->setFlat(true);
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(230, 188, 76, 76));
        pushButton_3->setFocusPolicy(Qt::NoFocus);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_3->setFlat(true);
        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(406, 188, 76, 76));
        pushButton_5->setFocusPolicy(Qt::NoFocus);
        pushButton_5->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_5->setFlat(true);
        pushButton_8 = new QPushButton(widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(670, 188, 76, 76));
        pushButton_8->setFocusPolicy(Qt::NoFocus);
        pushButton_8->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_8->setFlat(true);
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(318, 188, 76, 76));
        pushButton_4->setFocusPolicy(Qt::NoFocus);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_4->setFlat(true);
        pushButton_1 = new QPushButton(widget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(54, 188, 76, 76));
        pushButton_1->setFocusPolicy(Qt::NoFocus);
        pushButton_1->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_1->setFlat(true);
        pushButton_9 = new QPushButton(widget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(758, 188, 76, 76));
        pushButton_9->setFocusPolicy(Qt::NoFocus);
        pushButton_9->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_9->setFlat(true);
        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(494, 188, 76, 76));
        pushButton_6->setFocusPolicy(Qt::NoFocus);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_6->setFlat(true);
        pushButton_left = new QPushButton(widget);
        pushButton_left->setObjectName(QString::fromUtf8("pushButton_left"));
        pushButton_left->setGeometry(QRect(846, 106, 76, 76));
        pushButton_left->setFocusPolicy(Qt::NoFocus);
        pushButton_left->setStyleSheet(QString::fromUtf8("background-image: url(:/image/zuo.png);"));
        pushButton_left->setFlat(true);
        pushButton_BS = new QPushButton(widget);
        pushButton_BS->setObjectName(QString::fromUtf8("pushButton_BS"));
        pushButton_BS->setGeometry(QRect(846, 24, 76, 76));
        pushButton_BS->setFont(font1);
        pushButton_BS->setFocusPolicy(Qt::NoFocus);
        pushButton_BS->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        pushButton_BS->setFlat(true);
        pushButton_DEL = new QPushButton(widget);
        pushButton_DEL->setObjectName(QString::fromUtf8("pushButton_DEL"));
        pushButton_DEL->setGeometry(QRect(934, 24, 76, 76));
        pushButton_DEL->setFocusPolicy(Qt::NoFocus);
        pushButton_DEL->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_DEL->setFlat(true);
        pushButton_0 = new QPushButton(widget);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setGeometry(QRect(846, 188, 76, 76));
        pushButton_0->setFocusPolicy(Qt::NoFocus);
        pushButton_0->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_0->setFlat(true);
        pushButton_right = new QPushButton(widget);
        pushButton_right->setObjectName(QString::fromUtf8("pushButton_right"));
        pushButton_right->setGeometry(QRect(934, 106, 76, 76));
        pushButton_right->setFocusPolicy(Qt::NoFocus);
        pushButton_right->setStyleSheet(QString::fromUtf8("background-image: url(:/image/YOU.png);"));
        pushButton_right->setFlat(true);
        pushButton_less = new QPushButton(widget);
        pushButton_less->setObjectName(QString::fromUtf8("pushButton_less"));
        pushButton_less->setGeometry(QRect(934, 188, 76, 76));
        pushButton_less->setFocusPolicy(Qt::NoFocus);
        pushButton_less->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_less->setFlat(true);
        pushButton_T = new QPushButton(widget);
        pushButton_T->setObjectName(QString::fromUtf8("pushButton_T"));
        pushButton_T->setGeometry(QRect(406, 270, 76, 76));
        pushButton_T->setFocusPolicy(Qt::NoFocus);
        pushButton_T->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_T->setFlat(true);
        pushButton_W = new QPushButton(widget);
        pushButton_W->setObjectName(QString::fromUtf8("pushButton_W"));
        pushButton_W->setGeometry(QRect(142, 270, 76, 76));
        pushButton_W->setFocusPolicy(Qt::NoFocus);
        pushButton_W->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_W->setFlat(true);
        pushButton_Y = new QPushButton(widget);
        pushButton_Y->setObjectName(QString::fromUtf8("pushButton_Y"));
        pushButton_Y->setGeometry(QRect(494, 270, 76, 76));
        pushButton_Y->setFocusPolicy(Qt::NoFocus);
        pushButton_Y->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Y->setFlat(true);
        pushButton_E = new QPushButton(widget);
        pushButton_E->setObjectName(QString::fromUtf8("pushButton_E"));
        pushButton_E->setGeometry(QRect(230, 270, 76, 76));
        pushButton_E->setFocusPolicy(Qt::NoFocus);
        pushButton_E->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_E->setFlat(true);
        pushButton_Q = new QPushButton(widget);
        pushButton_Q->setObjectName(QString::fromUtf8("pushButton_Q"));
        pushButton_Q->setGeometry(QRect(54, 270, 76, 76));
        pushButton_Q->setFocusPolicy(Qt::NoFocus);
        pushButton_Q->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px"));
        pushButton_Q->setFlat(true);
        pushButton_U = new QPushButton(widget);
        pushButton_U->setObjectName(QString::fromUtf8("pushButton_U"));
        pushButton_U->setGeometry(QRect(582, 270, 76, 76));
        pushButton_U->setFocusPolicy(Qt::NoFocus);
        pushButton_U->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_U->setFlat(true);
        pushButton_R = new QPushButton(widget);
        pushButton_R->setObjectName(QString::fromUtf8("pushButton_R"));
        pushButton_R->setGeometry(QRect(318, 270, 76, 76));
        pushButton_R->setFocusPolicy(Qt::NoFocus);
        pushButton_R->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_R->setFlat(true);
        pushButton_I = new QPushButton(widget);
        pushButton_I->setObjectName(QString::fromUtf8("pushButton_I"));
        pushButton_I->setGeometry(QRect(670, 270, 76, 76));
        pushButton_I->setFocusPolicy(Qt::NoFocus);
        pushButton_I->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_I->setFlat(true);
        pushButton_more = new QPushButton(widget);
        pushButton_more->setObjectName(QString::fromUtf8("pushButton_more"));
        pushButton_more->setGeometry(QRect(934, 270, 76, 76));
        pushButton_more->setFocusPolicy(Qt::NoFocus);
        pushButton_more->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_more->setFlat(true);
        pushButton_O = new QPushButton(widget);
        pushButton_O->setObjectName(QString::fromUtf8("pushButton_O"));
        pushButton_O->setGeometry(QRect(758, 270, 76, 76));
        pushButton_O->setFocusPolicy(Qt::NoFocus);
        pushButton_O->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_O->setFlat(true);
        pushButton_P = new QPushButton(widget);
        pushButton_P->setObjectName(QString::fromUtf8("pushButton_P"));
        pushButton_P->setGeometry(QRect(846, 270, 76, 76));
        pushButton_P->setFocusPolicy(Qt::NoFocus);
        pushButton_P->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_P->setFlat(true);
        pushButton_A = new QPushButton(widget);
        pushButton_A->setObjectName(QString::fromUtf8("pushButton_A"));
        pushButton_A->setGeometry(QRect(54, 352, 76, 76));
        pushButton_A->setFocusPolicy(Qt::NoFocus);
        pushButton_A->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px"));
        pushButton_A->setFlat(true);
        pushButton_J = new QPushButton(widget);
        pushButton_J->setObjectName(QString::fromUtf8("pushButton_J"));
        pushButton_J->setGeometry(QRect(582, 352, 76, 76));
        pushButton_J->setFocusPolicy(Qt::NoFocus);
        pushButton_J->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_J->setFlat(true);
        pushButton_S = new QPushButton(widget);
        pushButton_S->setObjectName(QString::fromUtf8("pushButton_S"));
        pushButton_S->setGeometry(QRect(142, 352, 76, 76));
        pushButton_S->setFocusPolicy(Qt::NoFocus);
        pushButton_S->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_S->setFlat(true);
        pushButton_D = new QPushButton(widget);
        pushButton_D->setObjectName(QString::fromUtf8("pushButton_D"));
        pushButton_D->setGeometry(QRect(230, 352, 76, 76));
        pushButton_D->setFocusPolicy(Qt::NoFocus);
        pushButton_D->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_D->setFlat(true);
        pushButton_H = new QPushButton(widget);
        pushButton_H->setObjectName(QString::fromUtf8("pushButton_H"));
        pushButton_H->setGeometry(QRect(494, 352, 76, 76));
        pushButton_H->setFocusPolicy(Qt::NoFocus);
        pushButton_H->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_H->setFlat(true);
        pushButton_G = new QPushButton(widget);
        pushButton_G->setObjectName(QString::fromUtf8("pushButton_G"));
        pushButton_G->setGeometry(QRect(406, 352, 76, 76));
        pushButton_G->setFocusPolicy(Qt::NoFocus);
        pushButton_G->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_G->setFlat(true);
        pushButton_K = new QPushButton(widget);
        pushButton_K->setObjectName(QString::fromUtf8("pushButton_K"));
        pushButton_K->setGeometry(QRect(670, 352, 76, 76));
        pushButton_K->setFocusPolicy(Qt::NoFocus);
        pushButton_K->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_K->setFlat(true);
        pushButton_L = new QPushButton(widget);
        pushButton_L->setObjectName(QString::fromUtf8("pushButton_L"));
        pushButton_L->setGeometry(QRect(758, 352, 76, 76));
        pushButton_L->setFocusPolicy(Qt::NoFocus);
        pushButton_L->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_L->setFlat(true);
        pushButton_F = new QPushButton(widget);
        pushButton_F->setObjectName(QString::fromUtf8("pushButton_F"));
        pushButton_F->setGeometry(QRect(318, 352, 76, 76));
        pushButton_F->setFocusPolicy(Qt::NoFocus);
        pushButton_F->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_F->setFlat(true);
        pushButton_slash = new QPushButton(widget);
        pushButton_slash->setObjectName(QString::fromUtf8("pushButton_slash"));
        pushButton_slash->setGeometry(QRect(846, 352, 76, 76));
        pushButton_slash->setFocusPolicy(Qt::NoFocus);
        pushButton_slash->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_slash->setFlat(true);
        pushButton_backSlash = new QPushButton(widget);
        pushButton_backSlash->setObjectName(QString::fromUtf8("pushButton_backSlash"));
        pushButton_backSlash->setGeometry(QRect(934, 352, 76, 76));
        pushButton_backSlash->setFocusPolicy(Qt::NoFocus);
        pushButton_backSlash->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_backSlash->setFlat(true);
        pushButton_Enter = new QPushButton(widget);
        pushButton_Enter->setObjectName(QString::fromUtf8("pushButton_Enter"));
        pushButton_Enter->setGeometry(QRect(846, 352, 163, 76));
        pushButton_Enter->setFocusPolicy(Qt::NoFocus);
        pushButton_Enter->setStyleSheet(QString::fromUtf8("background-image: url(:/image/enter.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Enter->setFlat(true);
        pushButton_M = new QPushButton(widget);
        pushButton_M->setObjectName(QString::fromUtf8("pushButton_M"));
        pushButton_M->setGeometry(QRect(582, 434, 76, 76));
        pushButton_M->setFocusPolicy(Qt::NoFocus);
        pushButton_M->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_M->setFlat(true);
        pushButton_B = new QPushButton(widget);
        pushButton_B->setObjectName(QString::fromUtf8("pushButton_B"));
        pushButton_B->setGeometry(QRect(406, 434, 76, 76));
        pushButton_B->setFocusPolicy(Qt::NoFocus);
        pushButton_B->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_B->setFlat(true);
        pushButton_X = new QPushButton(widget);
        pushButton_X->setObjectName(QString::fromUtf8("pushButton_X"));
        pushButton_X->setGeometry(QRect(142, 434, 76, 76));
        pushButton_X->setFocusPolicy(Qt::NoFocus);
        pushButton_X->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_X->setFlat(true);
        pushButton_V = new QPushButton(widget);
        pushButton_V->setObjectName(QString::fromUtf8("pushButton_V"));
        pushButton_V->setGeometry(QRect(318, 434, 76, 76));
        pushButton_V->setFocusPolicy(Qt::NoFocus);
        pushButton_V->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_V->setFlat(true);
        pushButton_N = new QPushButton(widget);
        pushButton_N->setObjectName(QString::fromUtf8("pushButton_N"));
        pushButton_N->setGeometry(QRect(494, 434, 76, 76));
        pushButton_N->setFocusPolicy(Qt::NoFocus);
        pushButton_N->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_N->setFlat(true);
        pushButton_Period = new QPushButton(widget);
        pushButton_Period->setObjectName(QString::fromUtf8("pushButton_Period"));
        pushButton_Period->setGeometry(QRect(758, 434, 76, 76));
        pushButton_Period->setFocusPolicy(Qt::NoFocus);
        pushButton_Period->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Period->setFlat(true);
        pushButton_Z = new QPushButton(widget);
        pushButton_Z->setObjectName(QString::fromUtf8("pushButton_Z"));
        pushButton_Z->setGeometry(QRect(54, 434, 76, 76));
        pushButton_Z->setFocusPolicy(Qt::NoFocus);
        pushButton_Z->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px"));
        pushButton_Z->setFlat(true);
        pushButton_C = new QPushButton(widget);
        pushButton_C->setObjectName(QString::fromUtf8("pushButton_C"));
        pushButton_C->setGeometry(QRect(230, 434, 76, 76));
        pushButton_C->setFocusPolicy(Qt::NoFocus);
        pushButton_C->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_C->setFlat(true);
        pushButton_Comma = new QPushButton(widget);
        pushButton_Comma->setObjectName(QString::fromUtf8("pushButton_Comma"));
        pushButton_Comma->setGeometry(QRect(670, 434, 76, 76));
        pushButton_Comma->setFocusPolicy(Qt::NoFocus);
        pushButton_Comma->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Comma->setFlat(true);
        pushButton_Semicolon = new QPushButton(widget);
        pushButton_Semicolon->setObjectName(QString::fromUtf8("pushButton_Semicolon"));
        pushButton_Semicolon->setGeometry(QRect(846, 434, 76, 76));
        pushButton_Semicolon->setFocusPolicy(Qt::NoFocus);
        pushButton_Semicolon->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Semicolon->setFlat(true);
        pushButton_Colon = new QPushButton(widget);
        pushButton_Colon->setObjectName(QString::fromUtf8("pushButton_Colon"));
        pushButton_Colon->setGeometry(QRect(934, 434, 76, 76));
        pushButton_Colon->setFocusPolicy(Qt::NoFocus);
        pushButton_Colon->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Colon->setFlat(true);
        pushButton_ZH = new QPushButton(widget);
        pushButton_ZH->setObjectName(QString::fromUtf8("pushButton_ZH"));
        pushButton_ZH->setGeometry(QRect(758, 516, 76, 76));
        pushButton_ZH->setFocusPolicy(Qt::NoFocus);
        pushButton_ZH->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_ZH->setFlat(true);
        pushButton_SH = new QPushButton(widget);
        pushButton_SH->setObjectName(QString::fromUtf8("pushButton_SH"));
        pushButton_SH->setGeometry(QRect(670, 516, 76, 76));
        pushButton_SH->setFocusPolicy(Qt::NoFocus);
        pushButton_SH->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_SH->setFlat(true);
        pushButton_CH = new QPushButton(widget);
        pushButton_CH->setObjectName(QString::fromUtf8("pushButton_CH"));
        pushButton_CH->setGeometry(QRect(582, 516, 76, 76));
        pushButton_CH->setFocusPolicy(Qt::NoFocus);
        pushButton_CH->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_CH->setFlat(true);
        pushButton_Space = new QPushButton(widget);
        pushButton_Space->setObjectName(QString::fromUtf8("pushButton_Space"));
        pushButton_Space->setGeometry(QRect(230, 516, 340, 76));
        pushButton_Space->setFocusPolicy(Qt::NoFocus);
        pushButton_Space->setStyleSheet(QString::fromUtf8("background-image: url(:/image/space.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Space->setFlat(true);
        pushButton_LeftShift = new QPushButton(widget);
        pushButton_LeftShift->setObjectName(QString::fromUtf8("pushButton_LeftShift"));
        pushButton_LeftShift->setGeometry(QRect(54, 516, 164, 76));
        pushButton_LeftShift->setFocusPolicy(Qt::NoFocus);
        pushButton_LeftShift->setStyleSheet(QString::fromUtf8("background-image: url(:/image/enter.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_LeftShift->setFlat(true);
        pushButton_RightShift = new QPushButton(widget);
        pushButton_RightShift->setObjectName(QString::fromUtf8("pushButton_RightShift"));
        pushButton_RightShift->setGeometry(QRect(846, 516, 164, 76));
        pushButton_RightShift->setFocusPolicy(Qt::NoFocus);
        pushButton_RightShift->setStyleSheet(QString::fromUtf8("background-image: url(:/image/enter.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_RightShift->setFlat(true);
        pushButton_China = new QPushButton(widget);
        pushButton_China->setObjectName(QString::fromUtf8("pushButton_China"));
        pushButton_China->setGeometry(QRect(474, 618, 117, 52));
        pushButton_China->setFocusPolicy(Qt::NoFocus);
        pushButton_China->setStyleSheet(QString::fromUtf8("background-image: url(:/image/zhong.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;\n"
"color:white"));
        pushButton_China->setFlat(true);
        pushButton_Symbol = new QPushButton(widget);
        pushButton_Symbol->setObjectName(QString::fromUtf8("pushButton_Symbol"));
        pushButton_Symbol->setGeometry(QRect(591, 618, 119, 52));
        pushButton_Symbol->setFocusPolicy(Qt::NoFocus);
        pushButton_Symbol->setStyleSheet(QString::fromUtf8("background-image: url(:/image/fuhao.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;\n"
"color:white"));
        pushButton_Symbol->setFlat(true);
        pushButton_Cancel = new QPushButton(widget);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(54, 618, 124, 57));
        pushButton_Cancel->setFont(font1);
        pushButton_Cancel->setFocusPolicy(Qt::NoFocus);
        pushButton_Cancel->setStyleSheet(QString::fromUtf8("background-image: url(:/image/OK.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;\n"
"color:white"));
        pushButton_Cancel->setFlat(true);
        pushButton_English = new QPushButton(widget);
        pushButton_English->setObjectName(QString::fromUtf8("pushButton_English"));
        pushButton_English->setGeometry(QRect(354, 618, 120, 52));
        pushButton_English->setFocusPolicy(Qt::NoFocus);
        pushButton_English->setStyleSheet(QString::fromUtf8("background-image: url(:/image/ying.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;\n"
"color:white"));
        pushButton_English->setFlat(true);
        pushButton_OK = new QPushButton(widget);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(886, 618, 124, 52));
        pushButton_OK->setFocusPolicy(Qt::NoFocus);
        pushButton_OK->setStyleSheet(QString::fromUtf8("background-image: url(:/image/OK.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;\n"
"color:white"));
        pushButton_OK->setFlat(true);
        pushButton_Space_e = new QPushButton(widget);
        pushButton_Space_e->setObjectName(QString::fromUtf8("pushButton_Space_e"));
        pushButton_Space_e->setGeometry(QRect(230, 516, 604, 76));
        pushButton_Space_e->setFocusPolicy(Qt::NoFocus);
        pushButton_Space_e->setStyleSheet(QString::fromUtf8("background-image: url(:/image/space_e.bmp);\n"
"font-family:Microsoft YaHei;\n"
"font-size:30px;"));
        pushButton_Space_e->setFlat(true);
        showTxt = new QWidget(widget);
        showTxt->setObjectName(QString::fromUtf8("showTxt"));
        showTxt->setGeometry(QRect(70, 100, 771, 81));
        btn8 = new QPushButton(showTxt);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        btn8->setGeometry(QRect(614, 0, 70, 70));
        btn8->setFocusPolicy(Qt::NoFocus);
        btn8->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn8->setFlat(true);
        btn4 = new QPushButton(showTxt);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(310, 0, 70, 70));
        btn4->setFocusPolicy(Qt::NoFocus);
        btn4->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn4->setFlat(true);
        btn7 = new QPushButton(showTxt);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setGeometry(QRect(538, 0, 70, 70));
        btn7->setFocusPolicy(Qt::NoFocus);
        btn7->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn7->setFlat(true);
        btn6 = new QPushButton(showTxt);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setGeometry(QRect(462, 0, 70, 70));
        btn6->setFocusPolicy(Qt::NoFocus);
        btn6->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn6->setFlat(true);
        btn_leftTurn = new QPushButton(showTxt);
        btn_leftTurn->setObjectName(QString::fromUtf8("btn_leftTurn"));
        btn_leftTurn->setGeometry(QRect(6, 0, 70, 70));
        btn_leftTurn->setFocusPolicy(Qt::NoFocus);
        btn_leftTurn->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn_leftTurn->setFlat(true);
        btn5 = new QPushButton(showTxt);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setGeometry(QRect(386, 0, 70, 70));
        btn5->setFocusPolicy(Qt::NoFocus);
        btn5->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn5->setFlat(true);
        btn1 = new QPushButton(showTxt);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(82, 0, 70, 70));
        btn1->setFocusPolicy(Qt::NoFocus);
        btn1->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn1->setFlat(true);
        btn3 = new QPushButton(showTxt);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(234, 0, 70, 70));
        btn3->setFocusPolicy(Qt::NoFocus);
        btn3->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn3->setFlat(true);
        btn2 = new QPushButton(showTxt);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(158, 0, 70, 70));
        btn2->setFocusPolicy(Qt::NoFocus);
        btn2->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn2->setFlat(true);
        btn_rightTurn = new QPushButton(showTxt);
        btn_rightTurn->setObjectName(QString::fromUtf8("btn_rightTurn"));
        btn_rightTurn->setGeometry(QRect(690, 0, 70, 70));
        btn_rightTurn->setFocusPolicy(Qt::NoFocus);
        btn_rightTurn->setStyleSheet(QString::fromUtf8("background-image: url(:/image/shuzi.bmp);\n"
"font-family:'Microsoft YaHei';font-size:30px;"));
        btn_rightTurn->setFlat(true);
        textEdit_letter = new QTextEdit(widget);
        textEdit_letter->setObjectName(QString::fromUtf8("textEdit_letter"));
        textEdit_letter->setGeometry(QRect(70, 60, 761, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Ubuntu"));
        font2.setPointSize(22);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        textEdit_letter->setFont(font2);
        textEdit_letter->setStyleSheet(QString::fromUtf8(""));
        textEdit_letter->setFrameShape(QFrame::Box);
        textEdit_letter->setFrameShadow(QFrame::Sunken);
        textEdit_letter->setLineWidth(1);
        textEdit_letter->setMidLineWidth(0);
        textEdit_letter->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit_letter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit_letter->setReadOnly(true);

        retranslateUi(softKeyPad);

        QMetaObject::connectSlotsByName(softKeyPad);
    } // setupUi

    void retranslateUi(QWidget *softKeyPad)
    {
        softKeyPad->setWindowTitle(QApplication::translate("softKeyPad", "softKeyPad", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("softKeyPad", "7", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("softKeyPad", "2", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("softKeyPad", "3", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("softKeyPad", "5", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("softKeyPad", "8", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("softKeyPad", "4", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("softKeyPad", "1", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("softKeyPad", "9", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("softKeyPad", "6", 0, QApplication::UnicodeUTF8));
        pushButton_left->setText(QString());
        pushButton_BS->setText(QApplication::translate("softKeyPad", "BS", 0, QApplication::UnicodeUTF8));
        pushButton_DEL->setText(QApplication::translate("softKeyPad", "DEL", 0, QApplication::UnicodeUTF8));
        pushButton_0->setText(QApplication::translate("softKeyPad", "0", 0, QApplication::UnicodeUTF8));
        pushButton_right->setText(QString());
        pushButton_less->setText(QApplication::translate("softKeyPad", "-", 0, QApplication::UnicodeUTF8));
        pushButton_T->setText(QApplication::translate("softKeyPad", "T", 0, QApplication::UnicodeUTF8));
        pushButton_W->setText(QApplication::translate("softKeyPad", "W", 0, QApplication::UnicodeUTF8));
        pushButton_Y->setText(QApplication::translate("softKeyPad", "Y", 0, QApplication::UnicodeUTF8));
        pushButton_E->setText(QApplication::translate("softKeyPad", "E", 0, QApplication::UnicodeUTF8));
        pushButton_Q->setText(QApplication::translate("softKeyPad", "Q", 0, QApplication::UnicodeUTF8));
        pushButton_U->setText(QApplication::translate("softKeyPad", "U", 0, QApplication::UnicodeUTF8));
        pushButton_R->setText(QApplication::translate("softKeyPad", "R", 0, QApplication::UnicodeUTF8));
        pushButton_I->setText(QApplication::translate("softKeyPad", "I", 0, QApplication::UnicodeUTF8));
        pushButton_more->setText(QApplication::translate("softKeyPad", "+", 0, QApplication::UnicodeUTF8));
        pushButton_O->setText(QApplication::translate("softKeyPad", "O", 0, QApplication::UnicodeUTF8));
        pushButton_P->setText(QApplication::translate("softKeyPad", "P", 0, QApplication::UnicodeUTF8));
        pushButton_A->setText(QApplication::translate("softKeyPad", "A", 0, QApplication::UnicodeUTF8));
        pushButton_J->setText(QApplication::translate("softKeyPad", "J", 0, QApplication::UnicodeUTF8));
        pushButton_S->setText(QApplication::translate("softKeyPad", "S", 0, QApplication::UnicodeUTF8));
        pushButton_D->setText(QApplication::translate("softKeyPad", "D", 0, QApplication::UnicodeUTF8));
        pushButton_H->setText(QApplication::translate("softKeyPad", "H", 0, QApplication::UnicodeUTF8));
        pushButton_G->setText(QApplication::translate("softKeyPad", "G", 0, QApplication::UnicodeUTF8));
        pushButton_K->setText(QApplication::translate("softKeyPad", "K", 0, QApplication::UnicodeUTF8));
        pushButton_L->setText(QApplication::translate("softKeyPad", "L", 0, QApplication::UnicodeUTF8));
        pushButton_F->setText(QApplication::translate("softKeyPad", "F", 0, QApplication::UnicodeUTF8));
        pushButton_slash->setText(QApplication::translate("softKeyPad", "/", 0, QApplication::UnicodeUTF8));
        pushButton_backSlash->setText(QApplication::translate("softKeyPad", "\\", 0, QApplication::UnicodeUTF8));
        pushButton_Enter->setText(QApplication::translate("softKeyPad", "Enter", 0, QApplication::UnicodeUTF8));
        pushButton_M->setText(QApplication::translate("softKeyPad", "M", 0, QApplication::UnicodeUTF8));
        pushButton_B->setText(QApplication::translate("softKeyPad", "B", 0, QApplication::UnicodeUTF8));
        pushButton_X->setText(QApplication::translate("softKeyPad", "X", 0, QApplication::UnicodeUTF8));
        pushButton_V->setText(QApplication::translate("softKeyPad", "V", 0, QApplication::UnicodeUTF8));
        pushButton_N->setText(QApplication::translate("softKeyPad", "N", 0, QApplication::UnicodeUTF8));
        pushButton_Period->setText(QApplication::translate("softKeyPad", "\343\200\202", 0, QApplication::UnicodeUTF8));
        pushButton_Z->setText(QApplication::translate("softKeyPad", "Z", 0, QApplication::UnicodeUTF8));
        pushButton_C->setText(QApplication::translate("softKeyPad", "C", 0, QApplication::UnicodeUTF8));
        pushButton_Comma->setText(QApplication::translate("softKeyPad", "\357\274\214", 0, QApplication::UnicodeUTF8));
        pushButton_Semicolon->setText(QApplication::translate("softKeyPad", "\357\274\233", 0, QApplication::UnicodeUTF8));
        pushButton_Colon->setText(QApplication::translate("softKeyPad", "\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_ZH->setText(QApplication::translate("softKeyPad", "ZH", 0, QApplication::UnicodeUTF8));
        pushButton_SH->setText(QApplication::translate("softKeyPad", "SH", 0, QApplication::UnicodeUTF8));
        pushButton_CH->setText(QApplication::translate("softKeyPad", "CH", 0, QApplication::UnicodeUTF8));
        pushButton_Space->setText(QApplication::translate("softKeyPad", "SPACE", 0, QApplication::UnicodeUTF8));
        pushButton_LeftShift->setText(QApplication::translate("softKeyPad", "Shift", 0, QApplication::UnicodeUTF8));
        pushButton_RightShift->setText(QApplication::translate("softKeyPad", "Shift", 0, QApplication::UnicodeUTF8));
        pushButton_China->setText(QApplication::translate("softKeyPad", "\344\270\255", 0, QApplication::UnicodeUTF8));
        pushButton_Symbol->setText(QApplication::translate("softKeyPad", "\347\254\246\345\217\267", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("softKeyPad", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton_English->setText(QApplication::translate("softKeyPad", "\350\213\261", 0, QApplication::UnicodeUTF8));
        pushButton_OK->setText(QApplication::translate("softKeyPad", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_Space_e->setText(QApplication::translate("softKeyPad", "SPACE", 0, QApplication::UnicodeUTF8));
        btn8->setText(QString());
        btn4->setText(QString());
        btn7->setText(QString());
        btn6->setText(QString());
        btn_leftTurn->setText(QApplication::translate("softKeyPad", "<<", 0, QApplication::UnicodeUTF8));
        btn5->setText(QString());
        btn1->setText(QString());
        btn3->setText(QString());
        btn2->setText(QString());
        btn_rightTurn->setText(QApplication::translate("softKeyPad", ">>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class softKeyPad: public Ui_softKeyPad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTKEYPAD_H
