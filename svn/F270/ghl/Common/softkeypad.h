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

#ifndef SOFTKEYPAD_H
#define SOFTKEYPAD_H

#include <QWidget>
#include <QTextCursor>
#include <QSqlQuery>
#include <QSqlDatabase>

class QButtonGroup;
namespace Ui {
class softKeyPad;
}

class SoftKeyPad : public QWidget
{
    Q_OBJECT

public:
    explicit SoftKeyPad(QWidget *parent = 0);

    /*
     * 当接收到sigOkPressSignal()信号后，可以调用该函数，获取当前文本框中的文字.
     */
    QString getInputStr();

    /*
     * 重写show()函数
     */
    void show(QString info);
    ~SoftKeyPad();

signals:

    /*
     * enter 、确认、取消按钮下押时发送该信号
     */
    void sigOkPressSignal();

protected:

    /*
     * 重写paintEvent事件，使窗体透明.
     */
    void paintEvent(QPaintEvent *);

private:

    /*
     * 定义一组枚举值，判断当前的输入状态是英文、中文还是符号.
     */
    enum {
        KeyInput_English = 0,
        KeyInput_Chinese,
        KeyInput_Symbol
    };

private slots:

    /*
     * 软件盘下押时候触发该函数,改变按钮的背景颜色.
     */
    void slotNumPressed(int id);

    /*
     * 软件盘释放时候触发该函数,改变按钮的背景颜色.
     */
    void slotNumReleased(int id);

    /*
     * 软件盘按钮被点击时会触发该函数，实现文字输入以及其他附加功能
     */
    void slotKeyInputClicked(int id);

    /*
     * 中文状态下用户选择备选框中的向左翻页按钮时触发该函数
     */
    void slotLeftTurnClicked();

    /*
     * 中文状态下用户选择备选框中的向右翻页按钮时触发该函数
     */
    void slotRightTurnClicked();

    /*
     * 中文状态下用户选择备选框中的中文时触发该函数
     */
    void slotChineseInputClicked(int id);

private:
    Ui::softKeyPad *ui;
    bool firstInputFlag;    // 输入判断标识符，如果为true，清空提示信息
    bool shiftFlag;         // 大小写切换标志符
    bool firstInputLetter;  // 首字母输入判断标志符，true说明这是一个汉字的首字母
    bool leftBtnClicked;    // 判断是否向左翻页过
    bool rightBtnClicked;   // 判断是否向右翻页过
    bool chineseInputFlag;  // 判断当前汉字备选框是否有汉字
    int current_choice;     // 一个整形变量，判断当前用户选择的输入发（英文、中文、符号）
    int listId;             // list列表的id
    int listCount;          // list中string的数目
    QString inputLetter;    // 保存用户一次查找中输入的一组字母
    QString singleLetter;   // 保存用户一次查找中输入的第一个字母
    QButtonGroup* groupBtnShow;
    QButtonGroup* groupButtonAll;
    QTextCursor course;
    QSqlDatabase db;    // 定义数据库
    QSqlQuery query;    // 数据库执行
    QList<QString> list; // 保存查询到的汉字
    QString inputStr;    // 返回用户输入字符

private:
    void addGroupButtonAll();       // 把界面所有按钮添加成一个按钮组
    void connectFunc();             // 连接keypad类中所有的槽和信号
    void setChineseShow();          // 设置中文显示界面
    void setEnglishShow();          // 设置英文显示界面
    void setSymbolShow();           // 设置符号显示界面
    void setNumShow();              // 隐藏特定的按钮
    void setDefaultShow();          // 设置中文英文符号这三个按钮的默认背景颜色
    void englishPressed();          // 设置英文状态时按钮的颜色背景
    void ABCShow();                 // 设置字母大写状态下的界面
    void englishButtonClicked();    // 选择英文输入时要显示的界面
    void shiftABC();                // shift下押时显示的背景(大写)
    void shiftabc();                // shift下押时显示的背景(小写)
    void connectDatabase();         // 数据库连接
    void addGroupButtonShow();      // 汉字备选框中的按钮设置为一个按钮组
    void sqlSelect();               // SQL执行语句
};

#endif // SOFTKEYPAD_H
