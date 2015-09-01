/*********************************************************************
 * Copyright(c) 2015, 温光自动化技术有限公司
 *
 * All Rights reserved
 *
 * 文件名称：DigitalOperation.h
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
#ifndef DIGITALOPERATION_H
#define DIGITALOPERATION_H

#define ERROR 0.0001
#include <QWidget>
#include <QCursor>
class QTextEdit;
class QLineEdit;
class QPushButton;
class QButtonGroup;
class DigitalOperation : public QWidget
{
    Q_OBJECT

public:
    DigitalOperation(QWidget *parent = 0);
    ~DigitalOperation();

    /*
     * 重写show()函数, 第一个参数是输入最大值，
     * 第二个参数是输入最小值，第三个参数是保
     * 留的小数点位数，第四个参数是是否使用科学计数法
     */
    void show(float min, float max, int lengh, bool science = false);

    /*
     * 提供一个供调用者使用的接口，如果输入有效，返回true，
     * 并将有效值传递给行参，输入值无效返回false
     */
    bool getInputNumber(float * number);

signals:
    /*
     * enter 、确认按钮下押时发送该信号
     */
    void sigInputOver();

protected:
    /*
     * 重写paintEvent事件.
     */
    void paintEvent(QPaintEvent *);

private slots:  
    /*
     * 界面按钮下押时触发该函数.
     */
    void slotButtonClicked(int id);

private:
    void setSizeOfWindows();       // 根据当前屏幕的分辨率设置窗体的大小
    void layoutWindows();          // 画面布局
    void addButtonGroup();         // 添加按钮组

    void deletePreviousChar();     // 删除前一个字符
    void deleteNextChar();         // 删除后一个字符
    void moveRight();              // 光标右移
    void moveLeft();               // 光标左移
    void sortOutText();            // 提取文本框内容
private:
    QTextEdit* textEdit;    // 输入框
    QLineEdit* lineEdit;
    QButtonGroup* buttonGroup;
    QPushButton* BSButton;
    QPushButton* DELButton;
    QPushButton* leftMoveButton;
    QPushButton* rightMoveButton;
    QPushButton* digitalOneButton;
    QPushButton* digitalTwoButton;
    QPushButton* digitalThreeButton;
    QPushButton* digitalFourButton;
    QPushButton* digitalFiveButton;
    QPushButton* digitalSixButton;
    QPushButton* digitalSevenButton;
    QPushButton* digitalEightButton;
    QPushButton* digitalNineButton;
    QPushButton* pointButton;
    QPushButton* digitalZeroButton;
    QPushButton* digitalDoubleZeroButton;
    QPushButton* reduceButton;
    QPushButton* plusButton;
    QPushButton* EButton;
    QPushButton* enterButton;
    QPushButton* cancelButton;
    QPushButton* OKButton;
    int heightWindows;          // 绘制窗体的高度
    int widthWindows;           // 绘制窗体的宽度
    int digital_Maximum;        // 最大值
    int digital_Min;            // 最小值
    int digital_Length;         // 保留的小数点位数
    QCursor cursor;
    bool firstInput;            // 第一次输入
    bool digital_science;       // 是否是科学计数法
    bool digital_result;        // 结果是否正确
    float Inputresult;          // 最终结果

};

#endif // DIGITALOPERATION_H
