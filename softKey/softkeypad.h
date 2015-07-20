/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：SoftKey.h
 * 概   要：SoftKey提供一个软件盘的字符输入功能，有英文、中文以及符号等输入方式
 * 当前版本：V1.0.0
 * 作   者：葛 海 浪
 * 完成日期：2015-7-17
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
    * 当接收到用户输入完毕的信号后，可以调用该函数，
    * 获取当前文本框中的文字。
    */
    QString getInputStr();
    ~SoftKeyPad();

signals:

    /*
     * 当输入完毕或者用户取消输入时，发送该信号。
     */
    void sigOkPressSignal();

protected:

    /*
     * 重写paintEvent事件，使窗体透明。
     */
    void paintEvent(QPaintEvent *);

private:

    /*
     * 定义一组枚举值，判断当前的输入状态是英文、中文
     * 还是符号。
     */
    enum {
        KeyInput_English = 0,
        KeyInput_Chinese,
        KeyInput_Symbol
    };

private slots:

    void slotNumPressed(int id);
    void slotNumReleased(int id);
    void slotKeyInputClicked(int id);
    void slotLeftTurnClicked();
    void slotRightTurnClicked();
    void slotChineseInputClicked(int id);

private:
    Ui::softKeyPad *ui;

    bool tipFlag;
    bool inputChoiceFlag;
    bool firstInputFlag;
    bool shiftFlag;
    bool firstInputLetter;
    bool leftBtnClicked;
    bool rightBtnClicked;
    bool chineseInputFlag;
    int current_choice;
    int listId;      //list列表的id
    int listCount;  //list中string的数目
    QString inputLetter;
    QString singleLetter;
    QButtonGroup* groupBtnShow;
    QButtonGroup* groupButtonAll;
    QTextCursor course;
    QSqlDatabase db;
    QSqlQuery query;
    QList<QString> list;
    QString inputStr;

private:
    void addGroupButtonAll();
    void connectFunc();
    void setChineseShow();
    void setEnglishShow();
    void setSymbolShow();
    void setNumShow();
    void setDefaultShow();
    void englishPressed();
    void ABCShow();
    void englishButtonClicked();
    void shiftABC();
    void shiftabc();
    void connectDatabase();
    void addGroupButtonShow();
    void sqlSelect();
};

#endif // SOFTKEYPAD_H
