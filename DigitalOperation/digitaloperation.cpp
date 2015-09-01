/*********************************************************************
 * Copyright(c) 2015, 温光自动化技术有限公司
 *
 * All Rights reserved
 *
 * 文件名称：DigitalOperation.cpp
 * 概   要：DigitalOperation提供一个数字输入的窗体，可以选择科学计数发
 *          法和非科学计数法两中界面
 *
 * 当前版本：V1.0.0
 * 作   者：葛 海 浪
 * 完成日期：2015-8-11
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "digitaloperation.h"
#include <QDebug>
#include <QPushButton>
#include <QTextEdit>
#include <QButtonGroup>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QTextCursor>
#include <QLineEdit>

/*
 * 功能：
 * 	  构造函数，初始化有限状态机并run之。
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
DigitalOperation::DigitalOperation(QWidget *parent)
    : QWidget(parent)
    , textEdit(NULL)
    , lineEdit(NULL)
    , buttonGroup(NULL)
    , BSButton(NULL)
    , DELButton(NULL)
    , leftMoveButton(NULL)
    , rightMoveButton(NULL)
    , digitalOneButton(NULL)
    , digitalTwoButton(NULL)
    , digitalThreeButton(NULL)
    , digitalFourButton(NULL)
    , digitalFiveButton(NULL)
    , digitalSixButton(NULL)
    , digitalSevenButton(NULL)
    , digitalEightButton(NULL)
    , digitalNineButton(NULL)
    , pointButton(NULL)
    , digitalZeroButton(NULL)
    , digitalDoubleZeroButton(NULL)
    , reduceButton(NULL)
    , plusButton(NULL)
    , EButton(NULL)
    , enterButton(NULL)
    , cancelButton(NULL)
    , OKButton(NULL)
    , heightWindows(0)
    , widthWindows(0)
    , digital_Maximum(0)
    , digital_Min(0)
    , digital_Length(0)
    , firstInput(false)
    , digital_science(false)
    , digital_result(true)
    , Inputresult(0)
{
    setSizeOfWindows();
    setAttribute(Qt::WA_TranslucentBackground, true);
    layoutWindows();
    addButtonGroup();
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotButtonClicked(int)));
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
DigitalOperation::~DigitalOperation()
{

}

/*
 * 功能：
 * 	  重写show()函数
 *
 * 参数：
 * 	  float min, float max, int lengh, bool science
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::show(float min, float max, int lengh, bool science)
{
    digital_Min = min;
    digital_Maximum = max;
    digital_Length = lengh;
    digital_science = science;
    textEdit->insertPlainText(tr("Allow setting range\n"));
    if (!digital_science) {
        EButton->setHidden(true);
        textEdit->insertPlainText(QString(QString::number(min, 'f', lengh) + "/" + QString::number(max, 'f', lengh)));
    } else {
        EButton->setHidden(false);
        textEdit->insertPlainText(QString(QString::number(min, 'E', lengh) + "/" + QString::number(max, 'E', lengh)));
    }

    QWidget::show();
}

/*
 * 功能：
 * 	  一个可供用户调用的接口，把结果赋值给行参
 *
 * 参数：
 * 	  float *number
 *
 * 返回值：
 * 	  bool
 */
bool DigitalOperation::getInputNumber(float *number)
{
    if (digital_result) {
        *number = Inputresult;
        return true;
    } else {
        return false;
    }
}

/*
 * 功能：
 * 	  重写paintEvent事件，使窗体透明
 *
 * 参数：
 * 	  QPaintEvent *
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(28, 28, 28, 100));
}

/*
 * 功能：
 * 	  界面按钮下押时触发该函数, 根据不同的id进行不同的操作
 *
 * 参数：
 * 	  int id
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::slotButtonClicked(int id)
{
    switch (id) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 18:
    case 12:
    case 13:
        lineEdit->insert(buttonGroup->button(id)->text());
        firstInput = true;
        break;

    case 11:
        if (firstInput) {
            lineEdit->insert(buttonGroup->button(id)->text());
        } else {
            /**************** 如果第一个字符是‘.’，自动补充一个‘0’在前面 ************/
            lineEdit->insert("0.");
            firstInput = true;
        }
        break;

    case 14:
        /**************** 删除前一个字符 ************/
        deletePreviousChar();
        break;

    case 15:
        /**************** 删除后一个字符 ************/
        deleteNextChar();
        break;

    case 16:
        /**************** 光标左移 ************/
        moveLeft();
        break;

    case 17:
        /**************** 光标右移 ************/
        moveRight();
        break;

    case 19:
    case 21:
        /**************** 提取文本框内容 ************/
        sortOutText();
        /**************** 发送输入结束信号 ************/
        emit sigInputOver();
        break;
    case 20:
        this->close();
        break;
    default:
        break;
    }
}

/*
 * 功能：
 * 	  根据当前屏幕的分辨率设置窗体的大小
 *
 * 参数：
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::setSizeOfWindows()
{
    widthWindows = QApplication::desktop()->width();   // 获取当前屏幕的宽度
    heightWindows = QApplication::desktop()->height();  // 获取当前屏幕的高度
    resize(widthWindows, heightWindows);               // 调整窗体整体大小
}

/*
 * 功能：
 * 	  画面布局
 *
 * 参数：
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::layoutWindows()
{
    textEdit = new QTextEdit(this);
    textEdit->setGeometry(20, 20, (int)(0.8 * widthWindows), (int)(0.25 * heightWindows));
    textEdit->setStyleSheet("font-family:'Microsoft YaHei';font-size:15px;");
    textEdit->setFocusPolicy(Qt::NoFocus);

    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(20, (int)(0.17 * heightWindows + 5), (int)(0.8 * widthWindows), (int)(0.083 * heightWindows));
    lineEdit->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;color:#66FFFF");
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setFrame(false);
    lineEdit->setFocus();

    BSButton = new QPushButton(this);
    BSButton->setGeometry((int)(0.8 * widthWindows + 30), 20, (int)(0.1 * widthWindows - 30), (int)(0.125 * heightWindows - 5));
    BSButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    BSButton->setText(tr("BS"));
    BSButton->setFocusPolicy(Qt::NoFocus);

    DELButton = new QPushButton(this);
    DELButton->setGeometry((int)(0.9 * widthWindows + 10), 20, (int)(0.1 * widthWindows - 30), (int)(0.125 * heightWindows - 5));
    DELButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    DELButton->setText(tr("DEL"));
    DELButton->setFocusPolicy(Qt::NoFocus);

    leftMoveButton = new QPushButton(this);
    leftMoveButton->setGeometry((int)(0.8 * widthWindows + 30), (int)(0.125 * heightWindows + 25), (int)(0.1 * widthWindows - 30), (int)(0.125 * heightWindows - 5));
    leftMoveButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    leftMoveButton->setText(tr("←"));
    leftMoveButton->setFocusPolicy(Qt::NoFocus);

    rightMoveButton = new QPushButton(this);
    rightMoveButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    rightMoveButton->setGeometry((int)(0.9 * widthWindows + 10), (int)(0.125 * heightWindows + 25), (int)(0.1 * widthWindows - 30), (int)(0.125 * heightWindows - 5));
    rightMoveButton->setText(tr("→"));
    rightMoveButton->setFocusPolicy(Qt::NoFocus);

    digitalSevenButton = new QPushButton(this);
    digitalSevenButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalSevenButton->setGeometry((int)(0.25 * widthWindows), (int)(0.25 * heightWindows + 40), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalSevenButton->setText(tr("7"));
    digitalSevenButton->setFocusPolicy(Qt::NoFocus);

    digitalEightButton = new QPushButton(this);
    digitalEightButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalEightButton->setGeometry((int)(0.375 * widthWindows), (int)(0.25 * heightWindows + 40), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalEightButton->setText(tr("8"));
    digitalEightButton->setFocusPolicy(Qt::NoFocus);

    digitalNineButton = new QPushButton(this);
    digitalNineButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalNineButton->setGeometry((int)(0.5 * widthWindows + 2.5), (int)(0.25 * heightWindows + 40), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalNineButton->setText(tr("9"));
    digitalNineButton->setFocusPolicy(Qt::NoFocus);

    plusButton = new QPushButton(this);
    plusButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    plusButton->setGeometry((int)(0.625 * widthWindows + 5), (int)(0.25 * heightWindows + 40), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    plusButton->setText(tr("+"));
    plusButton->setFocusPolicy(Qt::NoFocus);

    digitalFourButton = new QPushButton(this);
    digitalFourButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalFourButton->setGeometry((int)(0.25 * widthWindows), (int)(0.375 * heightWindows + 50), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalFourButton->setText(tr("4"));
    digitalFourButton->setFocusPolicy(Qt::NoFocus);

    digitalFiveButton = new QPushButton(this);
    digitalFiveButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalFiveButton->setGeometry((int)(0.375 * widthWindows), (int)(0.375 * heightWindows + 50), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalFiveButton->setText(tr("5"));
    digitalFiveButton->setFocusPolicy(Qt::NoFocus);

    digitalSixButton = new QPushButton(this);
    digitalSixButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalSixButton->setGeometry((int)(0.5 * widthWindows + 2.5), (int)(0.375 * heightWindows + 50), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalSixButton->setText(tr("6"));
    digitalSixButton->setFocusPolicy(Qt::NoFocus);

    reduceButton = new QPushButton(this);
    reduceButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    reduceButton->setGeometry((int)(0.625 * widthWindows + 5), (int)(0.375 * heightWindows + 50), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    reduceButton->setText(tr("-"));
    reduceButton->setFocusPolicy(Qt::NoFocus);

    digitalOneButton = new QPushButton(this);
    digitalOneButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalOneButton->setGeometry((int)(0.25 * widthWindows), (int)(0.5 * heightWindows + 60), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalOneButton->setText(tr("1"));
    digitalOneButton->setFocusPolicy(Qt::NoFocus);

    digitalTwoButton = new QPushButton(this);
    digitalTwoButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalTwoButton->setGeometry((int)(0.375 * widthWindows), (int)(0.5 * heightWindows + 60), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalTwoButton->setText(tr("2"));
    digitalTwoButton->setFocusPolicy(Qt::NoFocus);

    digitalThreeButton = new QPushButton(this);
    digitalThreeButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalThreeButton->setGeometry((int)(0.5 * widthWindows + 2.5), (int)(0.5 * heightWindows + 60), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalThreeButton->setText(tr("3"));
    digitalThreeButton->setFocusPolicy(Qt::NoFocus);

    EButton = new QPushButton(this);
    EButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    EButton->setGeometry((int)(0.625 * widthWindows + 5), (int)(0.5 * heightWindows + 60), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    EButton->setText(tr("E"));
    EButton->setFocusPolicy(Qt::NoFocus);

    digitalZeroButton = new QPushButton(this);
    digitalZeroButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalZeroButton->setGeometry((int)(0.25 * widthWindows), (int)(0.625 * heightWindows + 70), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalZeroButton->setText(tr("0"));
    digitalZeroButton->setFocusPolicy(Qt::NoFocus);

    digitalDoubleZeroButton = new QPushButton(this);
    digitalDoubleZeroButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    digitalDoubleZeroButton->setGeometry((int)(0.375 * widthWindows), (int)(0.625 * heightWindows + 70), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    digitalDoubleZeroButton->setText(tr("00"));
    digitalDoubleZeroButton->setFocusPolicy(Qt::NoFocus);

    pointButton = new QPushButton(this);
    pointButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    pointButton->setGeometry((int)(0.5 * widthWindows + 2.5), (int)(0.625 * heightWindows + 70), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    pointButton->setText(tr("."));
    pointButton->setFocusPolicy(Qt::NoFocus);

    enterButton = new QPushButton(this);
    enterButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    enterButton->setGeometry((int)(0.625 * widthWindows + 5), (int)(0.625 * heightWindows + 70), (int)(0.125 * widthWindows - 7.5), (int)(0.125 * heightWindows));
    enterButton->setText(tr("Enter"));
    enterButton->setFocusPolicy(Qt::NoFocus);

    cancelButton = new QPushButton(this);
    cancelButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    cancelButton->setGeometry(10, (int)(0.9375 * heightWindows - 10), (int)(0.25 * heightWindows - 15), (int)(0.0625 * heightWindows));
    cancelButton->setText(tr("Cancel"));
    cancelButton->setFocusPolicy(Qt::NoFocus);

    OKButton = new QPushButton(this);
    OKButton->setStyleSheet("font-family:'Microsoft YaHei';font-size:30px;");
    OKButton->setGeometry((int)(widthWindows - 0.25 * heightWindows + 5), (int)(0.9375 * heightWindows - 10), (int)(0.25 * heightWindows - 15), (int)(0.0625 * heightWindows));
    OKButton->setText(tr("OK"));
    OKButton->setFocusPolicy(Qt::NoFocus);

}

/*
 * 功能：
 * 	  添加按钮组
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::addButtonGroup()
{
    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(digitalZeroButton, 0);
    buttonGroup->addButton(digitalOneButton, 1);
    buttonGroup->addButton(digitalTwoButton, 2);
    buttonGroup->addButton(digitalThreeButton, 3);
    buttonGroup->addButton(digitalFourButton, 4);
    buttonGroup->addButton(digitalFiveButton, 5);
    buttonGroup->addButton(digitalSixButton, 6);
    buttonGroup->addButton(digitalSevenButton, 7);
    buttonGroup->addButton(digitalEightButton, 8);
    buttonGroup->addButton(digitalNineButton, 9);
    buttonGroup->addButton(digitalDoubleZeroButton, 10);
    buttonGroup->addButton(pointButton, 11);
    buttonGroup->addButton(reduceButton, 12);
    buttonGroup->addButton(plusButton, 13);
    buttonGroup->addButton(BSButton, 14);
    buttonGroup->addButton(DELButton, 15);
    buttonGroup->addButton(leftMoveButton, 16);
    buttonGroup->addButton(rightMoveButton, 17);
    buttonGroup->addButton(EButton, 18);
    buttonGroup->addButton(enterButton, 19);
    buttonGroup->addButton(cancelButton, 20);
    buttonGroup->addButton(OKButton, 21);
}

/*
 * 功能：
 * 	  删除前一个字符
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::deletePreviousChar()
{
    lineEdit->backspace();
}

/*
 * 功能：
 * 	  删除后一个字符
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::deleteNextChar()
{
    lineEdit->del();
}

/*
 * 功能：
 * 	  光标右移
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::moveRight()
{
    int i = lineEdit->cursorPosition();
    lineEdit->setCursorPosition(++i);
}

/*
 * 功能：
 * 	  光标左移
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::moveLeft()
{
    int i = lineEdit->cursorPosition();
    lineEdit->setCursorPosition(--i);
}

/*
 * 功能：
 * 	  提取文本框内容
 *
 * 参数：
 *    无
 *
 * 返回值：
 * 	  无
 */
void DigitalOperation::sortOutText()
{
    QString str = lineEdit->text();
    if ("0" == str) {
        Inputresult = 0;
        digital_result = true;
    } else {
        Inputresult = str.toFloat();
        if (0 == Inputresult) {
            digital_result = false;
        } else {
            digital_result = true;
        }
    }
}
