#include "winroot_generalwin.h"
#include <QPainter>


WinRoot_GeneralWin::WinRoot_GeneralWin(QWidget *parent) :
    QWidget(parent)
{
    flag = 0;
    getItemFlag();
    initItem();
    setItemPixmap();
    connectSgSlot();
    setMainLayout();
}

WinRoot_GeneralWin::~WinRoot_GeneralWin()
{
    release();
}

/*flag是一个32位的数，每一位对于list中button的显示与否,这个函数还需要到时再重写，现在先目前测试用*/
void WinRoot_GeneralWin::getItemFlag()
{
    flag = 0xfffff;
}

/*初始化窗体,new出各个对象,将所有按键全部放入list中*/
void WinRoot_GeneralWin::initItem()
{
    gLayout = new QGridLayout;
    map= new QPixmap;

    item_Trend = new GeneralMenu_Item(this);
    item_Trend->setItemText(tr("Trend"));

    item_Digital = new GeneralMenu_Item(this);
    item_Digital->setItemText(tr("Digital"));

    item_Bar = new GeneralMenu_Item(this);
    item_Bar->setItemText(tr("Bar"));

    item_Overview = new GeneralMenu_Item(this);
    item_Overview->setItemText(tr("Overview"));

    item_Alert = new GeneralMenu_Item(this);
    item_Alert->setItemText(tr("Alert"));

    item_Information = new GeneralMenu_Item(this);
    item_Information->setItemText(tr("Information"));

    item_Ram = new GeneralMenu_Item(this);
    item_Ram->setItemText(tr("Ram"));

    item_ReportForm = new GeneralMenu_Item(this);
    item_ReportForm->setItemText(tr("Report Form"));

    item_ModbusClient = new GeneralMenu_Item(this);
    item_ModbusClient->setItemText(tr("Modbus Client"));

    item_Journal = new GeneralMenu_Item(this);
    item_Journal->setItemText(tr("Journal"));

    item_MultiScreen = new GeneralMenu_Item(this);
    item_MultiScreen->setItemText(tr("Multi Screen"));

    item_Setting = new GeneralMenu_Item(this);
    item_Setting->setItemText(tr("Setting"));

    item_SaveLoading = new GeneralMenu_Item(this);
    item_SaveLoading->setItemText(tr("Save Loading"));

    item_InternetInfo = new GeneralMenu_Item(this);
    item_InternetInfo->setItemText(tr("Internet Information"));

    item_SystemInfo = new GeneralMenu_Item(this);
    item_SystemInfo->setItemText(tr("System Information"));

    item_InitValueCorrection = new GeneralMenu_Item(this);
    item_InitValueCorrection->setItemText(tr("Init Value Correction"));

    item_CustomScreen = new GeneralMenu_Item(this);
    item_CustomScreen->setItemText(tr("Custom Screen"));

    item_InternalSwitch = new GeneralMenu_Item(this);
    item_InternalSwitch->setItemText(tr("Internal Switch"));

    itemList.push_back(item_Trend);
    itemList.push_back(item_Digital);
    itemList.push_back(item_Bar);
    itemList.push_back(item_Overview);
    itemList.push_back(item_Alert);

    itemList.push_back(item_Information);
    itemList.push_back(item_Ram);
    itemList.push_back(item_ReportForm);
    itemList.push_back(item_ModbusClient);
    itemList.push_back(item_Journal);

    itemList.push_back(item_MultiScreen);
    itemList.push_back(item_Setting);
    itemList.push_back(item_SaveLoading);
    itemList.push_back(item_InternetInfo);
    itemList.push_back(item_SystemInfo);

    itemList.push_back(item_InitValueCorrection);
    itemList.push_back(item_CustomScreen);
    itemList.push_back(item_InternalSwitch);

}

/*绑定每个按键的点击信号和槽函数,在点击槽函数中进行切图,在释放槽函数中做具体的处理*/
void WinRoot_GeneralWin::connectSgSlot()
{
    connect(item_Trend, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Trend()));
    connect(item_Trend, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Trend()));

    connect(item_Digital, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Digital()));
    connect(item_Digital, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Digital()));

    connect(item_Bar, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Bar()));
    connect(item_Bar, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Bar()));

    connect(item_Overview, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Overview()));
    connect(item_Overview, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Overview()));

    connect(item_Alert, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Alert()));
    connect(item_Alert, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Alert()));

    connect(item_Information, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Information()));
    connect(item_Information, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Information()));

    connect(item_Ram, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Ram()));
    connect(item_Ram, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Ram()));

    connect(item_ReportForm, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ReportForm()));
    connect(item_ReportForm, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ReportForm()));

    connect(item_ModbusClient, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ModbusClient()));
    connect(item_ModbusClient, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ModbusClient()));

    connect(item_Journal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Journal()));
    connect(item_Journal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Journal()));

    connect(item_MultiScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_MultiScreen()));
    connect(item_MultiScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_MultiScreen()));

    connect(item_Setting, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Setting()));
    connect(item_Setting, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Setting()));

    connect(item_SaveLoading, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_SaveLoading()));
    connect(item_SaveLoading, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_SaveLoading()));

    connect(item_InternetInfo, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InternetInfo()));
    connect(item_InternetInfo, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InternetInfo()));

    connect(item_SystemInfo, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_SystemInfo()));
    connect(item_SystemInfo, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_SystemInfo()));

    connect(item_InitValueCorrection, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InitValueCorrection()));
    connect(item_InitValueCorrection, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InitValueCorrection()));

    connect(item_CustomScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_CustomScreen()));
    connect(item_CustomScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_CustomScreen()));

    connect(item_InternalSwitch, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InternalSwitch()));
    connect(item_InternalSwitch, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InternalSwitch()));
}

/*设置每个按键上的图片*/
void WinRoot_GeneralWin::setItemPixmap()
{
    map->load(":/commonMenus/Image/commonMenus/trend.png");
    item_Trend->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/digital.png");
    item_Digital->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Bar->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Overview->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/alert.png");
    item_Alert->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/info.png");
    item_Information->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Ram->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/report_form.png");
    item_ReportForm->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/client.png");
    item_ModbusClient->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/journal.png");
    item_Journal->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/multi_screen.png");
    item_MultiScreen->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Setting->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/save_loading.png");
    item_SaveLoading->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/internet_info.png");
    item_InternetInfo->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/system_info.png");
    item_SystemInfo->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/init_value_correction.png");
    item_InitValueCorrection->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_CustomScreen->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/internal_switch.png");
    item_InternalSwitch->setItemPixmap(*map);
}

/*网格布局按键的添加,根据flag的值来决定每个按键的添加与否*/
void WinRoot_GeneralWin::setMainLayout()
{
    quint64 tmp_flag = flag;
    int itemBit = 0;
    int column,row,tmp_column,tmp_row;

    QList<GeneralMenu_Item *> tmp_itemList = itemList;

    for (column = 0; column < 8; ++column) {
        for (row = 0; row < 5 ; ++row) {
            tmp_column = column;
            tmp_row = row;
            for (int i = 0; i < tmp_itemList.size(); ++i) {
                if ((tmp_flag>>itemBit & 0x1) != 0) {
                    gLayout->addWidget(tmp_itemList.at(i), column, row);
                    itemBit++;
                    for (int j = 0;j <= i;++j) {
                        tmp_itemList.pop_front();
                    }
                    if (itemBit == BUTTON_NUM) {
                        goto quit;
                    }
                    break;
                }
                tmp_itemList.at(i)->setVisible(false);
                itemBit++;
                if (itemBit == BUTTON_NUM) {
                    goto quit;
                }
            }
        }
    }
quit:

    if (tmp_column == 1) {
        for (int i = tmp_row; i <= 4; ++i) {
            gLayout->addWidget(new GeneralMenu_Item, 0, i);
        }
    }
    for (int i = tmp_column; i <= 3; ++i) {
        gLayout->addWidget(new GeneralMenu_Item, i, 0);
    }

    setLayout(gLayout);
}

/*取消信号槽绑定，delete对象，在析构函数中使用*/
void WinRoot_GeneralWin::release()
{
    disconnect(item_Trend, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Trend()));
    disconnect(item_Trend, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Trend()));

    disconnect(item_Digital, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Digital()));
    disconnect(item_Digital, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Digital()));

    disconnect(item_Bar, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Bar()));
    disconnect(item_Bar, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Bar()));

    disconnect(item_Overview, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Overview()));
    disconnect(item_Overview, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Overview()));

    disconnect(item_Alert, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Alert()));
    disconnect(item_Alert, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Alert()));

    disconnect(item_Information, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Information()));
    disconnect(item_Information, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Information()));

    disconnect(item_Ram, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Ram()));
    disconnect(item_Ram, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Ram()));

    disconnect(item_ReportForm, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ReportForm()));
    disconnect(item_ReportForm, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ReportForm()));

    disconnect(item_ModbusClient, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ModbusClient()));
    disconnect(item_ModbusClient, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ModbusClient()));

    disconnect(item_Journal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Journal()));
    disconnect(item_Journal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Journal()));

    disconnect(item_MultiScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_MultiScreen()));
    disconnect(item_MultiScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_MultiScreen()));

    disconnect(item_Setting, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Setting()));
    disconnect(item_Setting, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Setting()));

    disconnect(item_SaveLoading, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_SaveLoading()));
    disconnect(item_SaveLoading, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_SaveLoading()));

    disconnect(item_InternetInfo, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InternetInfo()));
    disconnect(item_InternetInfo, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InternetInfo()));

    disconnect(item_SystemInfo, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_SystemInfo()));
    disconnect(item_SystemInfo, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_SystemInfo()));

    disconnect(item_InitValueCorrection, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InitValueCorrection()));
    disconnect(item_InitValueCorrection, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InitValueCorrection()));

    disconnect(item_CustomScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_CustomScreen()));
    disconnect(item_CustomScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_CustomScreen()));

    disconnect(item_InternalSwitch, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_InternalSwitch()));
    disconnect(item_InternalSwitch, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_InternalSwitch()));

    delete item_Trend;
    delete item_Digital;
    delete item_Bar;
    delete item_Overview;
    delete item_Alert;

    delete item_Information;
    delete item_Ram;
    delete item_ReportForm;
    delete item_ModbusClient;
    delete item_Journal;

    delete item_MultiScreen;
    delete item_Setting;
    delete item_SaveLoading;
    delete item_InternetInfo;
    delete item_SystemInfo;

    delete item_InitValueCorrection;
    delete item_CustomScreen;
    delete item_InternalSwitch;

    delete map;
    delete gLayout;
}




/*
 * 功能：
 * 	  QWidget::paintEvent()重新实现。
 */
void WinRoot_GeneralWin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pm;
    pm.load(":/commonMenus/Image/commonMenus/BG.bmp");
    painter.fillRect(QRect(0,0,this->width(), this->height()), QBrush(pm));

//    painter.fillRect(0,0,this->width(), this->height(), QColor(0,255,255));
}

void WinRoot_GeneralWin::slotItemPress_Trend()
{
    map->load(":/commonMenus/Image/commonMenus/trend_p.png");
    item_Trend->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Trend()
{
    map->load(":/commonMenus/Image/commonMenus/trend.png");
    item_Trend->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Digital()
{
    map->load(":/commonMenus/Image/commonMenus/digital_p.png");
    item_Digital->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Digital()
{
    map->load(":/commonMenus/Image/commonMenus/digital.png");
    item_Digital->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Bar()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_Bar->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Bar()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Bar->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Overview()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_Overview->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Overview()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Overview->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Alert()
{
    map->load(":/commonMenus/Image/commonMenus/alert_p.png");
    item_Alert->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Alert()
{
    map->load(":/commonMenus/Image/commonMenus/alert.png");
    item_Alert->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Information()
{
    map->load(":/commonMenus/Image/commonMenus/info_p.png");
    item_Information->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Information()
{
    map->load(":/commonMenus/Image/commonMenus/info.png");
    item_Information->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Ram()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_Ram->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Ram()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Ram->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_ReportForm()
{
    map->load(":/commonMenus/Image/commonMenus/report_form_p.png");
    item_ReportForm->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_ReportForm()
{
    map->load(":/commonMenus/Image/commonMenus/report_form.png");
    item_ReportForm->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_ModbusClient()
{
    map->load(":/commonMenus/Image/commonMenus/client_p.png");
    item_ModbusClient->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_ModbusClient()
{
    map->load(":/commonMenus/Image/commonMenus/client.png");
    item_ModbusClient->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Journal()
{
    map->load(":/commonMenus/Image/commonMenus/journal_p.png");
    item_Journal->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Journal()
{
    map->load(":/commonMenus/Image/commonMenus/journal.png");
    item_Journal->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_MultiScreen()
{
    map->load(":/commonMenus/Image/commonMenus/multi_screen_p.png");
    item_MultiScreen->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_MultiScreen()
{
    map->load(":/commonMenus/Image/commonMenus/multi_screen.png");
    item_MultiScreen->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_Setting()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_Setting->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_Setting()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Setting->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_SaveLoading()
{
    map->load(":/commonMenus/Image/commonMenus/save_loading_p.png");
    item_SaveLoading->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_SaveLoading()
{
    map->load(":/commonMenus/Image/commonMenus/save_loading.png");
    item_SaveLoading->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_InternetInfo()
{
    map->load(":/commonMenus/Image/commonMenus/internet_info_p.png");
    item_InternetInfo->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_InternetInfo()
{
    map->load(":/commonMenus/Image/commonMenus/internet_info.png");
    item_InternetInfo->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_SystemInfo()
{   map->load(":/commonMenus/Image/commonMenus/system_info_p.png");
    item_SystemInfo->setItemPixmap(*map);

}

void WinRoot_GeneralWin::slotItemRelease_SystemInfo()
{
    map->load(":/commonMenus/Image/commonMenus/system_info.png");
    item_SystemInfo->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_InitValueCorrection()
{
    map->load(":/commonMenus/Image/commonMenus/init_value_correction_p.png");
    item_InitValueCorrection->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_InitValueCorrection()
{
    map->load(":/commonMenus/Image/commonMenus/init_value_correction.png");
    item_InitValueCorrection->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_CustomScreen()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_CustomScreen->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_CustomScreen()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_CustomScreen->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemPress_InternalSwitch()
{
    map->load(":/commonMenus/Image/commonMenus/internal_switch_p.png");
    item_InternalSwitch->setItemPixmap(*map);
}

void WinRoot_GeneralWin::slotItemRelease_InternalSwitch()
{
    map->load(":/commonMenus/Image/commonMenus/internal_switch.png");
    item_InternalSwitch->setItemPixmap(*map);
}
