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

class softKeyPad : public QWidget
{
    Q_OBJECT
    
public:
    explicit softKeyPad(QWidget *parent = 0);

    QString getInputStr();
    ~softKeyPad();

signals:
    void okPressSignal();

  protected:
    // 重写paintEvent事件
    void paintEvent(QPaintEvent *);

    enum {
        KeyInput_English = 0,
        KeyInput_Chinese,
        KeyInput_Symbol
    };

private slots:

    void numPressed(int id);
    void numReleased(int id);
    void keyInputClicked(int id);
    void leftTurnClicked();
    void rightTurnClicked();
    void chineseInputClicked(int id);

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
