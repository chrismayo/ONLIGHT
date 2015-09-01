#ifndef ENGLISHINPUT_H
#define ENGLISHINPUT_H

#include <QWidget>

class QTextEdit;
class QLineEdit;
class QButtonGroup;
class EnglishInput : public QWidget
{
    Q_OBJECT

public:
    EnglishInput(QWidget *parent = 0);
    QString getInputStr();
    ~EnglishInput();

signals:
    void sigEnglishInputOver();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void slotGroupABCClicked(int id);
    void slotGroupABCPressed(int id);
    void slotGroupABCReleased(int id);
private:
    void setWindowsSize();
    void centerWidgetLayout();
    void setDefaultStyle();
    void setTextShow();
private:
    QWidget* centerWidget;
    int currentWidth;
    int currentHeight;
    QTextEdit* textEdit;
    QLineEdit* lineEdit;
    QButtonGroup* groupABC;
    QString inputStr;
    bool upLatter;
    bool latterStatus;
};

#endif // ENGLISHINPUT_H
