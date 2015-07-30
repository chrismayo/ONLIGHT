/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：winroot_generalmenu.h
 * 概   要：通用菜单画面，画面里包含一些按键选项，点击按键做出相应的处理（如画面的跳转等）。
 *
 * 当前版本：V1.5.8
 * 作   者：马志刚
 * 完成日期：2015-7-24
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#ifndef WINROOT_GENERALMENU_H
#define WINROOT_GENERALMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QSlider>

#define BUTTON_NUM 32

/*****这个外部类将每个按键和按键下面的文字做成一个控件,方便画面进行网格布局.******/
class GeneralMenu_Item : public QWidget
{
    Q_OBJECT
public:
    GeneralMenu_Item (QWidget *parent = 0);

    void setItemText(QString itemText);
    void setItemPixmap(QPixmap itemPixmap);
    void setItemVisible(bool visible);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sgItemPress();
    void sgItemRelease();

public slots:

public:
    QLabel *button;
    QLabel *text;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
};

class WinRoot_GeneralMenu : public QWidget
{
    Q_OBJECT
public:
    explicit WinRoot_GeneralMenu(QWidget *parent = 0);
    ~WinRoot_GeneralMenu();

    void initItem();
    void connectSgSlot();
    void setItemPixmap();
    void setSlider();
    void getItemFlag();
    void getWidgetScale();
    void release();


protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

    void setMenuLayout(int value);

    void slotItemPress_Buzzer();
    void slotItemRelease_Buzzer();

    void slotItemPress_ManualSampling();
    void slotItemRelease_ManualSampling();

    void slotItemPress_DataSave();
    void slotItemRelease_DataSave();

    void slotItemPress_Information();
    void slotItemRelease_Information();

    void slotItemPress_FreeInformation();
    void slotItemRelease_FreeInformation();

    void slotItemPress_UsrFunction1();
    void slotItemRelease_UsrFunction1();

    void slotItemPress_UsrFunction2();
    void slotItemRelease_UsrFunction2();

    void slotItemPress_TimeSetting();
    void slotItemRelease_TimeSetting();

    void slotItemPress_PrintTest();
    void slotItemRelease_PrintTest();

    void slotItemPress_ShowData();
    void slotItemRelease_ShowData();

    void slotItemPress_DigitalLabel();
    void slotItemRelease_DigitalLabel();

    void slotItemPress_DataRetriveal();
    void slotItemRelease_DataRetriveal();

    void slotItemPress_HandwrittenData();
    void slotItemRelease_HandwrittenData();

    void slotItemPress_Journal();
    void slotItemRelease_Journal();

    void slotItemPress_Alert();
    void slotItemRelease_Alert();

    void slotItemPress_Digital();
    void slotItemRelease_Digital();

    void slotItemPress_Trend();
    void slotItemRelease_Trend();

    void slotItemPress_FTPTest();
    void slotItemRelease_FTPTest();

    void slotItemPress_TimeAdjustment();
    void slotItemRelease_TimeAdjustment();

    void slotItemPress_EMAL();
    void slotItemRelease_EMAL();

    void slotItemPress_eventTrigger();
    void slotItemRelease_eventTrigger();

    void slotItemPress_mailTest();
    void slotItemRelease_mailTest();

    void slotItemPress_removeFavourites();
    void slotItemRelease_removeFavourites();

    void slotItemPress_standardScreen();
    void slotItemRelease_standardScreen();

    void slotItemPress_saveDisplay();
    void slotItemRelease_saveDisplay();

    void slotItemPress_textArea();
    void slotItemRelease_textArea();

    void slotItemPress_batch();
    void slotItemRelease_batch();

    void slotItemPress_saveAborted();
    void slotItemRelease_saveAborted();

    void slotItemPress_resetTimer();
    void slotItemRelease_resetTimer();

    void slotItemPress_matchTimer();
    void slotItemRelease_matchTimer();

    void slotItemPress_pendingCertification();
    void slotItemRelease_pendingCertification();

    void slotItemPress_screenStorage();
    void slotItemRelease_screenStorage();

protected:
    QGridLayout *gLayout;
    QPixmap *map;
    QSlider *slider;
    QWidget *widget;
    int value;
    QPoint startPos,endPos;
    quint64 flag;
    QList<GeneralMenu_Item *> itemList;
    int showItemNum;
    float widgetScale;
    float widgetHeight;
    float widgetMoveHeight;


    GeneralMenu_Item *item_Buzzer;
    GeneralMenu_Item *item_ManualSampling;
    GeneralMenu_Item *item_DataSave;
    GeneralMenu_Item *item_Information;
    GeneralMenu_Item *item_FreeInformation;

    GeneralMenu_Item *item_UsrFunction1;
    GeneralMenu_Item *item_UsrFunction2;
    GeneralMenu_Item *item_TimeSetting;
    GeneralMenu_Item *item_PrintTest;
    GeneralMenu_Item *item_ShowData;

    GeneralMenu_Item *item_DigitalLabel;
    GeneralMenu_Item *item_DataRetriveal;
    GeneralMenu_Item *item_HandwrittenData;
    GeneralMenu_Item *item_Journal;
    GeneralMenu_Item *item_Alert;

    GeneralMenu_Item *item_Digital;
    GeneralMenu_Item *item_Trend;
    GeneralMenu_Item *item_FTPTest;
    GeneralMenu_Item *item_TimeAdjustment;
    GeneralMenu_Item *item_EMAL;

//    GeneralMenu_Item *item_client;
    GeneralMenu_Item *item_eventTrigger;
//    GeneralMenu_Item *item_initValueCorrection;
//    GeneralMenu_Item *item_internalSwitch;
//    GeneralMenu_Item *item_internetInfo;

    GeneralMenu_Item *item_mailTest;
//    GeneralMenu_Item *item_multiScreen;
    GeneralMenu_Item *item_removeFavourites;
    GeneralMenu_Item *item_standardScreen;
//    GeneralMenu_Item *item_systemInfo;

//    GeneralMenu_Item *item_showRate;
//    GeneralMenu_Item *item_saveLoading;
    GeneralMenu_Item *item_saveDisplay;
    GeneralMenu_Item *item_textArea;
//    GeneralMenu_Item *item_updataCycle;

//    GeneralMenu_Item *item_reportForm;
    GeneralMenu_Item *item_batch;
    GeneralMenu_Item *item_saveAborted;
    GeneralMenu_Item *item_resetTimer;
    GeneralMenu_Item *item_matchTimer;
    GeneralMenu_Item *item_pendingCertification;
    GeneralMenu_Item *item_screenStorage;
};

#endif // WINROOT_GENERALMENU_H
