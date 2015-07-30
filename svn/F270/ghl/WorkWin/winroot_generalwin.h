/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：winroot_generalmenu.h
 * 概   要：画面变更画面，画面里包含一些按键选项，点击按键做出相应的处理（如画面的跳转等）。
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
#ifndef WINROOT_GENERALWIN_H
#define WINROOT_GENERALWIN_H

#include <QWidget>
#include "winroot_generalmenu.h"

#define BUTTON_NUM 18

class WinRoot_GeneralWin : public QWidget
{
    Q_OBJECT
public:
    explicit WinRoot_GeneralWin(QWidget *parent = 0);
    ~WinRoot_GeneralWin();

    void getItemFlag();
    void initItem();
    void connectSgSlot();
    void setItemPixmap();
    void setMainLayout();
    void release();


protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

    void slotItemPress_Trend();
    void slotItemRelease_Trend();

    void slotItemPress_Digital();
    void slotItemRelease_Digital();

    void slotItemPress_Bar();
    void slotItemRelease_Bar();

    void slotItemPress_Overview();
    void slotItemRelease_Overview();

    void slotItemPress_Alert();
    void slotItemRelease_Alert();

    void slotItemPress_Information();
    void slotItemRelease_Information();

    void slotItemPress_Ram();
    void slotItemRelease_Ram();

    void slotItemPress_ReportForm();
    void slotItemRelease_ReportForm();

    void slotItemPress_ModbusClient();
    void slotItemRelease_ModbusClient();

    void slotItemPress_Journal();
    void slotItemRelease_Journal();

    void slotItemPress_MultiScreen();
    void slotItemRelease_MultiScreen();

    void slotItemPress_Setting();
    void slotItemRelease_Setting();

    void slotItemPress_SaveLoading();
    void slotItemRelease_SaveLoading();

    void slotItemPress_InternetInfo();
    void slotItemRelease_InternetInfo();

    void slotItemPress_SystemInfo();
    void slotItemRelease_SystemInfo();

    void slotItemPress_InitValueCorrection();
    void slotItemRelease_InitValueCorrection();

    void slotItemPress_CustomScreen();
    void slotItemRelease_CustomScreen();

    void slotItemPress_InternalSwitch();
    void slotItemRelease_InternalSwitch();


protected:

    QGridLayout *gLayout;
    QPixmap *map;
    QList<GeneralMenu_Item *> itemList;
    quint32 flag;

    GeneralMenu_Item *item_Trend;
    GeneralMenu_Item *item_Digital;
    GeneralMenu_Item *item_Bar;
    GeneralMenu_Item *item_Overview;
    GeneralMenu_Item *item_Alert;

    GeneralMenu_Item *item_Information;
    GeneralMenu_Item *item_Ram;
    GeneralMenu_Item *item_ReportForm;
    GeneralMenu_Item *item_ModbusClient;
    GeneralMenu_Item *item_Journal;

    GeneralMenu_Item *item_MultiScreen;
    GeneralMenu_Item *item_Setting;
    GeneralMenu_Item *item_SaveLoading;
    GeneralMenu_Item *item_InternetInfo;
    GeneralMenu_Item *item_SystemInfo;

    GeneralMenu_Item *item_InitValueCorrection;
    GeneralMenu_Item *item_CustomScreen;
    GeneralMenu_Item *item_InternalSwitch;


};

#endif // WINROOT_GENERALWIN_H
