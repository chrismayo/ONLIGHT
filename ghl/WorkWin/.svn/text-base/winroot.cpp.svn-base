/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：WinRoot.h
 * 概   要：根目录窗体框架，用于容纳：系统设置窗体、通用菜单窗体以及画面变更窗体
 *
 * 当前版本：V1.0.0
 * 作   者：
 * 完成日期：
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include "winroot.h"

WinRoot::WinRoot(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setWinLayout();
    setUserDefineStyle();
    setUserDefineContent();
    sigAndSlotConnect();
}

void WinRoot::initialize()
{
    p_mainLayout = new QVBoxLayout();
    p_horLayout = new QHBoxLayout();
    p_buttonSystemSet = new QPushButton(tr("Setting"));
    p_buttonGeneralMenu = new QPushButton(tr("Universal"));
    p_buttonGeneralWin = new QPushButton(tr("Browse"));
//    p_buttonSystemSet = new QPushButton(tr("系统设置"));
//    p_buttonGeneralMenu = new QPushButton(tr("通用菜单"));
//    p_buttonGeneralWin = new QPushButton(tr("画面变更"));
    p_buttonGroup = new QButtonGroup();

    p_buttonSystemSet->setObjectName(QString("Setting"));
    p_buttonSystemSet->setCheckable(true);
    p_buttonGeneralMenu->setObjectName(QString("Universal"));
    p_buttonGeneralMenu->setCheckable(true);
    p_buttonGeneralWin->setObjectName(QString("Browse"));
    p_buttonGeneralWin->setCheckable(true);

    p_buttonSystemSet->setChecked(true);

    p_winSetting = new WinRoot_SysConfig();
    p_winUniversal = new WinRoot_GeneralMenu();
    p_winBrowse = new WinRoot_GeneralWin();
}

void WinRoot::setWinLayout()
{
    p_buttonGroup->addButton(p_buttonSystemSet);
    p_buttonGroup->addButton(p_buttonGeneralMenu);
    p_buttonGroup->addButton(p_buttonGeneralWin);

    p_horLayout->addWidget(p_buttonSystemSet);
    p_horLayout->addWidget(p_buttonGeneralMenu);
    p_horLayout->addWidget(p_buttonGeneralWin);

    m_rootWinStacked.addWidget(p_winSetting);
    m_rootWinStacked.addWidget(p_winUniversal);
    m_rootWinStacked.addWidget(p_winBrowse);
    p_mainLayout->addLayout(p_horLayout);
    p_mainLayout->addWidget(&m_rootWinStacked);

    setLayout(p_mainLayout);
}

void WinRoot::setUserDefineStyle()
{
    setContentsMargins(0,0,0,0);

    p_horLayout->setContentsMargins(50,0,0,0);
    p_horLayout->setSpacing(0);
    p_horLayout->setStretchFactor(p_buttonSystemSet, 10);
    p_horLayout->setStretchFactor(p_buttonGeneralMenu, 10);
    p_horLayout->setStretchFactor(p_buttonGeneralWin, 10);
    p_horLayout->addStretch(50);

    p_mainLayout->setContentsMargins(0,0,0,0);
    p_mainLayout->setSpacing(20);
}

void WinRoot::setUserDefineContent()
{
    setStyleSheet("QPushButton#Setting{\
                  border-top-left-radius:5px;\
                  border-bottom-left-radius:5px;\
                  background-color:#0000ff;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton#Setting:checked{\
                  border-top-left-radius:5px;\
                  border-bottom-left-radius:5px;\
                  background-color:#00ff00;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton#Universal{\
                  border-top-left-radius:0px;\
                  border-bottom-left-radius:0px;\
                  background-color:#0000ff;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton#Universal:checked{\
                  border-top-left-radius:0px;\
                  border-bottom-left-radius:0px;\
                  background-color:#00ff00;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton#Browse{\
                  border-top-right-radius:5px;\
                  border-bottom-right-radius:5px;\
                  background-color:#0000ff;\
                  height:20px;\
                  outline:none;\
                  }\
                  QPushButton#Browse:checked{\
                  border-top-right-radius:5px;\
                  border-bottom-right-radius:5px;\
                  background-color:#00ff00;\
                  height:20px;\
                  outline:none;\
                  }");
}

void WinRoot::sigAndSlotConnect()
{
    connect(p_buttonSystemSet, SIGNAL(clicked()), this, SLOT(slotSettingClicked()));
    connect(p_buttonGeneralMenu, SIGNAL(clicked()), this, SLOT(slotUniversalClicked()));
    connect(p_buttonGeneralWin, SIGNAL(clicked()), this, SLOT(slotBrowseClicked()));
}

void WinRoot::slotSettingClicked()
{
    p_buttonSystemSet->setChecked(true);
    m_rootWinStacked.setCurrentWidget(p_winSetting);
}

void WinRoot::slotUniversalClicked()
{
    p_buttonGeneralMenu->setChecked(true);
    m_rootWinStacked.setCurrentWidget(p_winUniversal);
}

void WinRoot::slotBrowseClicked()
{
    p_buttonGeneralWin->setChecked(true);
    m_rootWinStacked.setCurrentWidget(p_winBrowse);
}
