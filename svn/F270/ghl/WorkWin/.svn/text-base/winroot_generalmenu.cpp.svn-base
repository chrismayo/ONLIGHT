#include "winroot_generalmenu.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPalette>

GeneralMenu_Item::GeneralMenu_Item(QWidget *parent) :
    QWidget(parent)
{
/***new出对象和进行布局**/
    vLayout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    button = new QLabel;
    button->setAlignment(Qt::AlignHCenter);
    hLayout->addStretch();
    hLayout->addWidget(button);
    hLayout->addStretch();
    vLayout->addLayout(hLayout);
    text = new QLabel;
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::white);
    text->setPalette(p);

    text->setAlignment(Qt::AlignHCenter);
    vLayout->addWidget(text);

    setLayout(vLayout);
}

/*设置按键下方的文字*/
void GeneralMenu_Item::setItemText(QString itemText)
{
    text->setText(itemText);
}

/*设置按键上的图片*/
void GeneralMenu_Item::setItemPixmap(QPixmap itemPixmap)
{
    itemPixmap = itemPixmap.scaled(90,90,Qt::KeepAspectRatio,Qt::FastTransformation);
    button->setPixmap(itemPixmap);
}

/*设置整个对象的visible属性*/
void GeneralMenu_Item::setItemVisible(bool visible)
{
    button->setVisible(visible);
    text->setVisible(visible);
}

/*鼠标的点击事件,将点击事件集中在按键上,点击按键后对外部发送点击信号*/
void GeneralMenu_Item::mousePressEvent(QMouseEvent *event)
{
    if (event->x() >= button->x() && event->x() <= (button->x() + button->width())
            && event->y() >= button->y() && event->y() <= (button->y() + button->height()))
        emit sgItemPress();
}

/*鼠标的释放事件,将释放事件集中在按键上,点击按键后对外部发送释放信号*/
void GeneralMenu_Item::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->x() >= button->x() && event->x() <= (button->x() + button->width())
            && event->y() >= button->y() && event->y() <= (button->y() + button->height()))
        emit sgItemRelease();
}

/***********窗体****************/
WinRoot_GeneralMenu::WinRoot_GeneralMenu(QWidget *parent) :
    QWidget(parent)
{
    flag = 0;
    getItemFlag();
    initItem();
    getWidgetScale();
    setSlider();
    setItemPixmap();
    connectSgSlot();

}

WinRoot_GeneralMenu::~WinRoot_GeneralMenu()
{
    release();
}

/*初始化窗体,new出各个对象,将所有按键全部放入list中*/
void WinRoot_GeneralMenu::initItem()
{
    gLayout = new QGridLayout;
    map= new QPixmap;
    slider = new QSlider(this);
    widget = new QWidget(this);
    showItemNum = 0;

    item_Buzzer = new GeneralMenu_Item(widget);
    item_Buzzer->setItemText(tr("Buzzer ACK"));

    item_ManualSampling = new GeneralMenu_Item(widget);
    item_ManualSampling->setItemText(tr("Manual sampling"));


    item_DataSave = new GeneralMenu_Item(widget);
    item_DataSave->setItemText(tr("Saving data"));

    item_Information = new GeneralMenu_Item(widget);
    item_Information->setItemText(tr("Information"));

    item_FreeInformation = new GeneralMenu_Item(widget);
    item_FreeInformation->setItemText(tr("Free Info"));

    item_UsrFunction1 = new GeneralMenu_Item(widget);
    item_UsrFunction1->setItemText(tr("User Function 1"));

    item_UsrFunction2 = new GeneralMenu_Item(widget);
    item_UsrFunction2->setItemText(tr("User Function 2"));

    item_TimeSetting = new GeneralMenu_Item(widget);
    item_TimeSetting->setItemText(tr("Time Setting"));

    item_PrintTest = new GeneralMenu_Item(widget);
    item_PrintTest->setItemText(tr("Print Test"));

    item_ShowData = new GeneralMenu_Item(widget);
    item_ShowData->setItemText(tr("Show all data"));

    item_DigitalLabel = new GeneralMenu_Item(widget);
    item_DigitalLabel->setItemText(tr("Digital label"));

    item_DataRetriveal = new GeneralMenu_Item(widget);
    item_DataRetriveal->setItemText(tr("Data Retrieval"));

    item_HandwrittenData = new GeneralMenu_Item(widget);
    item_HandwrittenData->setItemText(tr("Handwritten data"));

    item_Journal = new GeneralMenu_Item(widget);
    item_Journal->setItemText(tr("Journal"));

    item_Alert = new GeneralMenu_Item(widget);
    item_Alert->setItemText(tr("Alert"));

    item_Digital = new GeneralMenu_Item(widget);
    item_Digital->setItemText(tr("Digital"));

    item_Trend = new GeneralMenu_Item(widget);
    item_Trend->setItemText(tr("Trend"));

    item_FTPTest = new GeneralMenu_Item(widget);
    item_FTPTest->setItemText(tr("FTP test"));

    item_TimeAdjustment = new GeneralMenu_Item(widget);
    item_TimeAdjustment->setItemText(tr("Time Adjustment"));

    item_EMAL = new GeneralMenu_Item(widget);
    item_EMAL->setItemText(tr("EMAL"));

    item_eventTrigger = new GeneralMenu_Item(widget);
    item_eventTrigger->setItemText(tr("Event Trigger"));

    item_mailTest = new GeneralMenu_Item(widget);
    item_mailTest->setItemText(tr("Mail Test"));

    item_removeFavourites = new GeneralMenu_Item(widget);
    item_removeFavourites->setItemText(tr("Remove Favourites"));

    item_standardScreen = new GeneralMenu_Item(widget);
    item_standardScreen->setItemText(tr("Standard Screen"));

    item_saveDisplay = new GeneralMenu_Item(widget);
    item_saveDisplay->setItemText(tr("Save Display"));

    item_textArea = new GeneralMenu_Item(widget);
    item_textArea->setItemText(tr("Text Area"));

    item_batch = new GeneralMenu_Item(widget);
    item_batch->setItemText(tr("Batch"));

    item_saveAborted = new GeneralMenu_Item(widget);
    item_saveAborted->setItemText(tr("Save Aborted"));

    item_resetTimer = new GeneralMenu_Item(widget);
    item_resetTimer->setItemText(tr("Reset Timer"));

    item_matchTimer = new GeneralMenu_Item(widget);
    item_matchTimer->setItemText(tr("Match Timer"));

    item_pendingCertification = new GeneralMenu_Item(widget);
    item_pendingCertification->setItemText(tr("Pending Certification"));

    item_screenStorage = new GeneralMenu_Item(widget);
    item_screenStorage->setItemText(tr("Screen Storage"));


    itemList.push_back(item_Buzzer);
    itemList.push_back(item_ManualSampling);
    itemList.push_back(item_DataSave);
    itemList.push_back(item_Information);
    itemList.push_back(item_FreeInformation);

    itemList.push_back(item_UsrFunction1);
    itemList.push_back(item_UsrFunction2);
    itemList.push_back(item_TimeSetting);
    itemList.push_back(item_PrintTest);
    itemList.push_back(item_ShowData);

    itemList.push_back(item_DigitalLabel);
    itemList.push_back(item_DataRetriveal);
    itemList.push_back(item_HandwrittenData);
    itemList.push_back(item_Journal);
    itemList.push_back(item_Alert);

    itemList.push_back(item_Digital);
    itemList.push_back(item_Trend);
    itemList.push_back(item_FTPTest);
    itemList.push_back(item_TimeAdjustment);
    itemList.push_back(item_EMAL);

    itemList.push_back(item_eventTrigger);

    itemList.push_back(item_mailTest);
    itemList.push_back(item_removeFavourites);
    itemList.push_back(item_standardScreen);

    itemList.push_back(item_saveDisplay);
    itemList.push_back(item_textArea);

    itemList.push_back(item_batch);
    itemList.push_back(item_saveAborted);
    itemList.push_back(item_resetTimer);
    itemList.push_back(item_matchTimer);
    itemList.push_back(item_pendingCertification);
    itemList.push_back(item_screenStorage);



}

/*绑定每个按键的点击信号和槽函数,在点击槽函数中进行切图,在释放槽函数中做具体的处理*/
void WinRoot_GeneralMenu::connectSgSlot()
{
    connect(item_Buzzer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Buzzer()));
    connect(item_Buzzer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Buzzer()));

    connect(item_ManualSampling, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ManualSampling()));
    connect(item_ManualSampling, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ManualSampling()));

    connect(item_DataSave, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DataSave()));
    connect(item_DataSave, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DataSave()));

    connect(item_Information, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Information()));
    connect(item_Information, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Information()));

    connect(item_FreeInformation, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_FreeInformation()));
    connect(item_FreeInformation, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_FreeInformation()));

    connect(item_UsrFunction1, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_UsrFunction1()));
    connect(item_UsrFunction1, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_UsrFunction1()));

    connect(item_UsrFunction2, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_UsrFunction2()));
    connect(item_UsrFunction2, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_UsrFunction2()));

    connect(item_TimeSetting, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_TimeSetting()));
    connect(item_TimeSetting, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_TimeSetting()));

    connect(item_PrintTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_PrintTest()));
    connect(item_PrintTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_PrintTest()));

    connect(item_ShowData, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ShowData()));
    connect(item_ShowData, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ShowData()));

    connect(item_DigitalLabel, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DigitalLabel()));
    connect(item_DigitalLabel, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DigitalLabel()));

    connect(item_DataRetriveal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DataRetriveal()));
    connect(item_DataRetriveal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DataRetriveal()));

    connect(item_HandwrittenData, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_HandwrittenData()));
    connect(item_HandwrittenData, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_HandwrittenData()));

    connect(item_Journal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Journal()));
    connect(item_Journal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Journal()));

    connect(item_Alert, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Alert()));
    connect(item_Alert, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Alert()));

    connect(item_Digital, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Digital()));
    connect(item_Digital, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Digital()));

    connect(item_Trend, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Trend()));
    connect(item_Trend, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Trend()));

    connect(item_FTPTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_FTPTest()));
    connect(item_FTPTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_FTPTest()));

    connect(item_TimeAdjustment, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_TimeAdjustment()));
    connect(item_TimeAdjustment, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_TimeAdjustment()));

    connect(item_EMAL, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_EMAL()));
    connect(item_EMAL, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_EMAL()));


    connect(item_eventTrigger, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_eventTrigger()));
    connect(item_eventTrigger, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_eventTrigger()));

    connect(item_mailTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_mailTest()));
    connect(item_mailTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_mailTest()));

    connect(item_removeFavourites, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_removeFavourites()));
    connect(item_removeFavourites, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_removeFavourites()));

    connect(item_standardScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_standardScreen()));
    connect(item_standardScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_standardScreen()));

    connect(item_saveDisplay, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_saveDisplay()));
    connect(item_saveDisplay, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_saveDisplay()));

    connect(item_textArea, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_textArea()));
    connect(item_textArea, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_textArea()));

    connect(item_batch, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_batch()));
    connect(item_batch, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_batch()));

    connect(item_saveAborted, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_saveAborted()));
    connect(item_saveAborted, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_saveAborted()));

    connect(item_resetTimer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_resetTimer()));
    connect(item_resetTimer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_resetTimer()));

    connect(item_matchTimer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_matchTimer()));
    connect(item_matchTimer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_matchTimer()));

    connect(item_pendingCertification, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_pendingCertification()));
    connect(item_pendingCertification, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_pendingCertification()));

    connect(item_screenStorage, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_screenStorage()));
    connect(item_screenStorage, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_screenStorage()));

}

/*设置每个按键上的图片*/
void WinRoot_GeneralMenu::setItemPixmap()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Buzzer->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/manual_sampling.png");
    item_ManualSampling->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/event_data_save.png");
    item_DataSave->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/info.png");
    item_Information->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/freeden_info.png");
    item_FreeInformation->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/user_function1.png");
    item_UsrFunction1->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/user_function2.png");
    item_UsrFunction2->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/time_data_setting.png");
    item_TimeSetting->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/print_test.png");
    item_PrintTest->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/show_all_data.png");
    item_ShowData->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/digital_label.png");
    item_DigitalLabel->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/data_retrieval.png");
    item_DataRetriveal->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/handwritten_info.png");
    item_HandwrittenData->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/journal.png");
    item_Journal->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/alert.png");
    item_Alert->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/digital.png");
    item_Digital->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/trend.png");
    item_Trend->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/FTP_test.png");
    item_FTPTest->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/time_adjust.png");
    item_TimeAdjustment->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/EMAL.png");
    item_EMAL->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/event_trigger.png");
    item_eventTrigger->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/mail_test.png");
    item_mailTest->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/remove_favorites.png");
    item_removeFavourites->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/standard_screen.png");
    item_standardScreen->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/save_display.png");
    item_saveDisplay->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/text_area.png");
    item_textArea->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_batch->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_saveAborted->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_resetTimer->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_matchTimer->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_pendingCertification->setItemPixmap(*map);

    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_screenStorage->setItemPixmap(*map);

}

/*定义拉选条,使用样式表来设置风格*/
void WinRoot_GeneralMenu::setSlider()
{
    slider->setGeometry(width() - 30,40,5,height() - 80);
    slider->setRange(0,height()/widgetScale);
    slider->setValue(height()/widgetScale);

    slider->setStyleSheet("  \
                          QSlider\
                          {\
                              background-color: rgb(25, 38, 58);\
                              min-width:5px;\
                              max-width:5px;\
                              border:1px solid rgb(25, 38, 58);\
                          }\
                          QSlider::add-page:vertical\
                          {     \
                             background-color: rgb(0, 21, 184);\
                             width:4px;\
                          }\
                           QSlider::sub-page:vertical \
                          {\
                              background-color: rgb(0, 71, 254);\
                              width:4px;\
                           }\
                          QSlider::groove:vertical \
                          {\
                              background:transparent;\
                              width:6px;\
                          }\
                          QSlider::handle:vertical \
                          {\
                               height: 13px;\
                              width:13px;\
                              border-image: url(:/images/ic_volume_thumb.png);\
                               margin: -0 -4px; \
                           }\
                          ");
    //connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setMenuLayout(int)));

    setMenuLayout(widgetMoveHeight);
}

/*flag是一个64位的数，每一位对于list中button的显示与否,这个函数还需要到时再重写，现在先目前测试用*/
void WinRoot_GeneralMenu::getItemFlag()
{
    flag = 0xfffffffff;
}

/*获取网格布局的显示尺寸*/
void WinRoot_GeneralMenu::getWidgetScale()
{
    quint64 tmp_flag = flag;

    for(int tmp = 0;tmp < BUTTON_NUM;tmp++) {
        if ((tmp_flag>>tmp & 0x1)) {
            showItemNum++;
        }
    }

    if (showItemNum <= 20) {
        widgetHeight = height();
    }
    else {
        widgetScale = 4.0/((showItemNum - 15) / 5);
        widgetMoveHeight = height()/widgetScale;
        widgetHeight = height() + widgetMoveHeight;
    }

}

/*取消信号槽绑定，delete对象，在析构函数中使用*/
void WinRoot_GeneralMenu::release()
{
    disconnect(item_Buzzer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Buzzer()));
    disconnect(item_Buzzer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Buzzer()));

    disconnect(item_ManualSampling, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ManualSampling()));
    disconnect(item_ManualSampling, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ManualSampling()));

    disconnect(item_DataSave, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DataSave()));
    disconnect(item_DataSave, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DataSave()));

    disconnect(item_Information, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Information()));
    disconnect(item_Information, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Information()));

    disconnect(item_FreeInformation, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_FreeInformation()));
    disconnect(item_FreeInformation, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_FreeInformation()));

    disconnect(item_UsrFunction1, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_UsrFunction1()));
    disconnect(item_UsrFunction1, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_UsrFunction1()));

    disconnect(item_UsrFunction2, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_UsrFunction2()));
    disconnect(item_UsrFunction2, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_UsrFunction2()));

    disconnect(item_TimeSetting, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_TimeSetting()));
    disconnect(item_TimeSetting, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_TimeSetting()));

    disconnect(item_PrintTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_PrintTest()));
    disconnect(item_PrintTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_PrintTest()));

    disconnect(item_ShowData, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_ShowData()));
    disconnect(item_ShowData, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_ShowData()));

    disconnect(item_DigitalLabel, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DigitalLabel()));
    connect(item_DigitalLabel, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DigitalLabel()));

    disconnect(item_DataRetriveal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_DataRetriveal()));
    disconnect(item_DataRetriveal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_DataRetriveal()));

    disconnect(item_HandwrittenData, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_HandwrittenData()));
    disconnect(item_HandwrittenData, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_HandwrittenData()));

    disconnect(item_Journal, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Journal()));
    disconnect(item_Journal, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Journal()));

    disconnect(item_Alert, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Alert()));
    disconnect(item_Alert, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Alert()));

    disconnect(item_Digital, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Digital()));
    disconnect(item_Digital, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Digital()));

    disconnect(item_Trend, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_Trend()));
    disconnect(item_Trend, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_Trend()));

    disconnect(item_FTPTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_FTPTest()));
    disconnect(item_FTPTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_FTPTest()));

    disconnect(item_TimeAdjustment, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_TimeAdjustment()));
    disconnect(item_TimeAdjustment, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_TimeAdjustment()));

    disconnect(item_EMAL, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_EMAL()));
    disconnect(item_EMAL, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_EMAL()));


    disconnect(item_eventTrigger, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_eventTrigger()));
    disconnect(item_eventTrigger, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_eventTrigger()));

    disconnect(item_mailTest, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_mailTest()));
    disconnect(item_mailTest, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_mailTest()));

    disconnect(item_removeFavourites, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_removeFavourites()));
    disconnect(item_removeFavourites, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_removeFavourites()));

    disconnect(item_standardScreen, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_standardScreen()));
    disconnect(item_standardScreen, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_standardScreen()));

    disconnect(item_saveDisplay, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_saveDisplay()));
    disconnect(item_saveDisplay, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_saveDisplay()));

    disconnect(item_textArea, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_textArea()));
    disconnect(item_textArea, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_textArea()));

    disconnect(item_batch, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_batch()));
    disconnect(item_batch, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_batch()));

    disconnect(item_saveAborted, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_saveAborted()));
    disconnect(item_saveAborted, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_saveAborted()));

    disconnect(item_resetTimer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_resetTimer()));
    disconnect(item_resetTimer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_resetTimer()));

    disconnect(item_matchTimer, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_matchTimer()));
    disconnect(item_matchTimer, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_matchTimer()));

    disconnect(item_pendingCertification, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_pendingCertification()));
    disconnect(item_pendingCertification, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_pendingCertification()));

    disconnect(item_screenStorage, SIGNAL(sgItemPress()), this, SLOT(slotItemPress_screenStorage()));
    disconnect(item_screenStorage, SIGNAL(sgItemRelease()), this, SLOT(slotItemRelease_screenStorage()));

    delete item_Buzzer;
    delete item_ManualSampling;
    delete item_DataSave;
    delete item_Information;
    delete item_FreeInformation;

    delete item_UsrFunction1;
    delete item_UsrFunction2;
    delete item_TimeSetting;
    delete item_PrintTest;
    delete item_ShowData;

    delete item_DigitalLabel;
    delete item_DataRetriveal;
    delete item_HandwrittenData;
    delete item_Journal;
    delete item_Alert;

    delete item_Digital;
    delete item_Trend;
    delete item_FTPTest;
    delete item_TimeAdjustment;
    delete item_EMAL;

    delete item_eventTrigger;
    delete item_mailTest;
    delete item_removeFavourites;
    delete item_standardScreen;
    delete item_saveDisplay;

    delete item_textArea;
    delete item_batch;
    delete item_saveAborted;
    delete item_resetTimer;
    delete item_matchTimer;

    delete item_pendingCertification;
    delete item_screenStorage;

    delete gLayout;
    delete map;
    delete slider;
    delete widget;

}

/*网格布局按键的添加,根据flag的值来决定每个按键的添加与否*/
void WinRoot_GeneralMenu::setMenuLayout(int value)
{
    quint64 tmp_flag = flag;
    int itemBit = 0;
    int column,row,tmp_column,tmp_row;

    QList<GeneralMenu_Item *> tmp_itemList = itemList;

    widget->setGeometry(0,0 + value - widgetMoveHeight, width() - 10,widgetHeight);

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


    widget->setLayout(gLayout);

}
/*
 * 功能：
 * 	  QWidget::paintEvent()重新实现。
 */
void WinRoot_GeneralMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pm;
    pm.load(":/commonMenus/Image/commonMenus/BG.bmp");
    painter.fillRect(QRect(0,0,this->width(), this->height()), QBrush(pm));

    //painter.fillRect(0,0,this->width(), this->height(), Qt::blue);
}


void WinRoot_GeneralMenu::resizeEvent(QResizeEvent *event)
{
    if (showItemNum <= 20) {
        widgetHeight = height();
    }
    else {
        widgetScale = 4.0/((showItemNum - 15) / 5);
        widgetMoveHeight = height()/widgetScale;
        widgetHeight = height() + widgetMoveHeight;
    }
    slider->setGeometry(width() - 30,40,5,height() - 80);
    slider->setRange(0,widgetMoveHeight);
    slider->setValue(widgetMoveHeight);
    setMenuLayout(widgetMoveHeight);

}


/*属于鼠标来控制屏幕的上下滚动显示*/
void WinRoot_GeneralMenu::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
}

void WinRoot_GeneralMenu::mouseMoveEvent(QMouseEvent *event)
{
    if (showItemNum > 20) {
        endPos = event->globalPos();
        value = endPos.y() - startPos.y();
        slider->setValue(widgetMoveHeight - 2*value);
        setMenuLayout(slider->value());
    }
}

void WinRoot_GeneralMenu::slotItemPress_Buzzer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_Buzzer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Buzzer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_Buzzer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_ManualSampling()
{
    map->load(":/commonMenus/Image/commonMenus/manual_sampling_p.png");
    item_ManualSampling->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_ManualSampling()
{
    map->load(":/commonMenus/Image/commonMenus/manual_sampling.png");
    item_ManualSampling->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_DataSave()
{
    map->load(":/commonMenus/Image/commonMenus/event_data_save_p.png");
    item_DataSave->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_DataSave()
{
    map->load(":/commonMenus/Image/commonMenus/event_data_save.png");
    item_DataSave->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_Information()
{
    map->load(":/commonMenus/Image/commonMenus/info_p.png");
    item_Information->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Information()
{
    map->load(":/commonMenus/Image/commonMenus/info.png");
    item_Information->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_FreeInformation()
{
    map->load(":/commonMenus/Image/commonMenus/freeden_info_p.png");
    item_FreeInformation->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_FreeInformation()
{
    map->load(":/commonMenus/Image/commonMenus/freeden_info.png");
    item_FreeInformation->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_UsrFunction1()
{
    map->load(":/commonMenus/Image/commonMenus/user_function1_p.png");
    item_UsrFunction1->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_UsrFunction1()
{
    map->load(":/commonMenus/Image/commonMenus/user_function1.png");
    item_UsrFunction1->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_UsrFunction2()
{
    map->load(":/commonMenus/Image/commonMenus/user_function2_p.png");
    item_UsrFunction2->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_UsrFunction2()
{
    map->load(":/commonMenus/Image/commonMenus/user_function2.png");
    item_UsrFunction2->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_TimeSetting()
{
    map->load(":/commonMenus/Image/commonMenus/time_data_setting_p.png");
    item_TimeSetting->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_TimeSetting()
{
    map->load(":/commonMenus/Image/commonMenus/time_data_setting.png");
    item_TimeSetting->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_PrintTest()
{
    map->load(":/commonMenus/Image/commonMenus/print_test_p.png");
    item_PrintTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_PrintTest()
{
    map->load(":/commonMenus/Image/commonMenus/print_test.png");
    item_PrintTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_ShowData()
{
    map->load(":/commonMenus/Image/commonMenus/show_all_data_p.png");
    item_ShowData->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_ShowData()
{
    map->load(":/commonMenus/Image/commonMenus/show_all_data.png");
    item_ShowData->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_DigitalLabel()
{
    map->load(":/commonMenus/Image/commonMenus/digital_label_p.png");
    item_DigitalLabel->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_DigitalLabel()
{
    map->load(":/commonMenus/Image/commonMenus/digital_label.png");
    item_DigitalLabel->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_DataRetriveal()
{
    map->load(":/commonMenus/Image/commonMenus/data_retrieval_p.png");
    item_DataRetriveal->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_DataRetriveal()
{
    map->load(":/commonMenus/Image/commonMenus/data_retrieval.png");
    item_DataRetriveal->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_HandwrittenData()
{
    map->load(":/commonMenus/Image/commonMenus/handwritten_info_p.png");
    item_HandwrittenData->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_HandwrittenData()
{
    map->load(":/commonMenus/Image/commonMenus/handwritten_info.png");
    item_HandwrittenData->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_Journal()
{
    map->load(":/commonMenus/Image/commonMenus/journal_p.png");
    item_Journal->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Journal()
{
    map->load(":/commonMenus/Image/commonMenus/journal.png");
    item_Journal->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_Alert()
{
    map->load(":/commonMenus/Image/commonMenus/alert_p.png");
    item_Alert->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Alert()
{
    map->load(":/commonMenus/Image/commonMenus/alert.png");
    item_Alert->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_Digital()
{
    map->load(":/commonMenus/Image/commonMenus/digital_p.png");
    item_Digital->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Digital()
{
    map->load(":/commonMenus/Image/commonMenus/digital.png");
    item_Digital->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_Trend()
{
    map->load(":/commonMenus/Image/commonMenus/trend_p.png");
    item_Trend->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_Trend()
{
    map->load(":/commonMenus/Image/commonMenus/trend.png");
    item_Trend->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_FTPTest()
{
    map->load(":/commonMenus/Image/commonMenus/FTP_test_p.png");
    item_FTPTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_FTPTest()
{
    map->load(":/commonMenus/Image/commonMenus/FTP_test.png");
    item_FTPTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_TimeAdjustment()
{
    map->load(":/commonMenus/Image/commonMenus/time_adjust_p.png");
    item_TimeAdjustment->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_TimeAdjustment()
{
    map->load(":/commonMenus/Image/commonMenus/time_adjust.png");
    item_TimeAdjustment->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_EMAL()
{
    map->load(":/commonMenus/Image/commonMenus/EMAL_p.png");
    item_EMAL->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_EMAL()
{
    map->load(":/commonMenus/Image/commonMenus/EMAL.png");
    item_EMAL->setItemPixmap(*map);
}


void WinRoot_GeneralMenu::slotItemPress_eventTrigger()
{
    map->load(":/commonMenus/Image/commonMenus/event_trigger_p.png");
    item_eventTrigger->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_eventTrigger()
{
    map->load(":/commonMenus/Image/commonMenus/event_trigger.png");
    item_eventTrigger->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_mailTest()
{
    map->load(":/commonMenus/Image/commonMenus/mail_test_p.png");
    item_mailTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_mailTest()
{
    map->load(":/commonMenus/Image/commonMenus/mail_test.png");
    item_mailTest->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_removeFavourites()
{
    map->load(":/commonMenus/Image/commonMenus/remove_favorites_p.png");
    item_removeFavourites->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_removeFavourites()
{
    map->load(":/commonMenus/Image/commonMenus/remove_favorites.png");
    item_removeFavourites->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_standardScreen()
{
    map->load(":/commonMenus/Image/commonMenus/standard_screen_p.png");
    item_standardScreen->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_standardScreen()
{
    map->load(":/commonMenus/Image/commonMenus/standard_screen.png");
    item_standardScreen->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_saveDisplay()
{
    map->load(":/commonMenus/Image/commonMenus/save_display_p.png");
    item_saveDisplay->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_saveDisplay()
{
    map->load(":/commonMenus/Image/commonMenus/save_display.png");
    item_saveDisplay->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_textArea()
{
    map->load(":/commonMenus/Image/commonMenus/text_area_p.png");
    item_textArea->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_textArea()
{
    map->load(":/commonMenus/Image/commonMenus/text_area.png");
    item_textArea->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_batch()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_batch->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_batch()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_batch->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_saveAborted()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_saveAborted->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_saveAborted()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_saveAborted->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_resetTimer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_resetTimer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_resetTimer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_resetTimer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_matchTimer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_matchTimer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_matchTimer()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_matchTimer->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_pendingCertification()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_pendingCertification->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_pendingCertification()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_pendingCertification->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemPress_screenStorage()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer_p.png");
    item_screenStorage->setItemPixmap(*map);
}

void WinRoot_GeneralMenu::slotItemRelease_screenStorage()
{
    map->load(":/commonMenus/Image/commonMenus/buzzer.png");
    item_screenStorage->setItemPixmap(*map);
}



