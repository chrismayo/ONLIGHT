#ifndef CHANNELSELECT_H
#define CHANNELSELECT_H

#include <QWidget>
#include <QMap>
#include <QLabel>
class QPushButton;
class QScrollArea;
class QScrollBar;
class QButtonGroup;
class ChannelSelect : public QWidget
{
    Q_OBJECT

public:
    ChannelSelect(QWidget *parent = 0);
    ~ChannelSelect();

signals:
    void sigChannelOKCLicked();
private:
    enum {
        SelectAI = 0,
        SelectDI,
        SelectDO,
        SelectMATH,
        SelectCOMM
    };

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private slots:
    void slotAIButtonClicked();
    void slotDIButtonClicked();
    void slotDOButtonClicked();
    void slotMATHButtonClicked();
    void slotCOMMButtonClicked();
    void slotUpPageClicked();
    void slotDownPageClicked();
    void slotAIChannelClicked(int id);
    void slotDIChannelClicked(int id);
    void slotDOChannelClicked(int id);
    void slotMATHChannelClicked(int id);
    void slotCOMMChannelClicked(int id);
    void slotAIGroupPressed(int id);
    void slotDIGroupPressed(int id);
    void slotDOGroupPressed(int id);
    void slotCOMMGroupPressed(int id);
    void slotMATHGroupPressed(int id);
    void slotCancelClicked();
    void slotOKClicked();
    void slotMouseMove(int x, int y);

private:
    void setWindowsSize();
    void initialWindows();
    void getChannelNum();
    void setAllhiden();
    void AILayout();
    void DILayout();
    void DOLayout();
    void MATHLayout();
    void COMMLayout();
    void setDefaultStyle();
    void setIntoShow();

    void connectFunC();

private:
    int current_width;
    int current_height;
    int current_select;
    int AI_Num;
    int DI_Num;
    int DO_Num;
    int AIGroupID;
    int DIGroupID;
    int DOGroupID;
    int MATHGroupID;
    int COMMGroupID;
    int numSequence;
    int AIHight;
    int DIHight;
    int DOHight;
    bool boolSequence;
    bool boolAI[500];
    bool boolDI[500];
    bool boolDO[500];
    bool boolMATH[100];
    bool boolCOMM[300];
    QWidget* channelButtonWidget;
    QWidget* channelShowWidget;
    QWidget* AIWidget;
    QWidget* DIWidget;
    QWidget* DOWidget;
    QWidget* MATHWidget;
    QWidget* COMMWidget;
    QPushButton* buttonAIChannel;
    QPushButton* buttonDIChannel;
    QPushButton* buttonDOChannel;
    QPushButton* buttonMathChannel;
    QPushButton* buttonCommChannel;
    QPushButton* buttonUpPage;
    QPushButton* buttonDownPage;
    QPushButton* buttonCancel;
    QPushButton* buttonOK;
    QScrollArea* channelAIArea;
    QScrollArea* channelDIArea;
    QScrollArea* channelDOArea;
    QScrollArea* channelMATHArea;
    QScrollArea* channelCOMMArea;
    QScrollBar* AIScrollBar;
    QScrollBar* DIScrollBar;
    QScrollBar* DOScrollBar;
    QScrollBar* MATHScrollBar;
    QScrollBar* COMMScrollBar;

    QButtonGroup* AIGroup;
    QButtonGroup* DIGroup;
    QButtonGroup* DOGroup;
    QButtonGroup* MATHGroup;
    QButtonGroup* COMMGroup;

    QList<QLabel*> listAI;
    QList<QLabel*> listDI;
    QList<QLabel*> listDO;
    QList<QLabel*> listMATH;
    QList<QLabel*> listCOMM;

    QList<QLabel*> listSaveClicked;

    QList<quint32> listEffectiveChannel;

    QMap<QString, quint32>  m_map_AI;       //实际存在的AI通道映射，Key--Value : 默认通道字符串---通道编码
    QMap<QString, quint32>  m_map_DI;       //实际存在的DI通道映射，Key--Value : 默认通道字符串---通道编码
    QMap<QString, quint32>  m_map_DO;      //实际存在的DO通道映射，Key--Value : 默认通道字符串---通道编码
    QMap<QString, quint32>  m_map_MATH; //运算通道，Key--Value : 默认通道字符串---通道编码
    QMap<QString, quint32>  m_map_COMM;//通信通道，Key--Value : 默认通道字符串---通道编码

    QMap<QString, quint32>::iterator it;

};

#endif // CHANNELSELECT_H
