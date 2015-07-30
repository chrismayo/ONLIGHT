/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：WinMainFrame.h
 * 概   要：主窗体类，垂直布局，包括WinMainStatus和QStackedWidget，
 *      ----WinMainStatus类对象用于系统状态显示
 *      ----QStackedWidget类对象作为各个窗体的堆栈容器
 *
 *
 * 当前版本：V1.0.0
 * 作   者：王 品
 * 完成日期：2015-6-30
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#ifndef WINMAINFRAME_H
#define WINMAINFRAME_H

#include <QWidget>
#include <QStackedWidget>
#include <QLayout>

class WinMainStatus : public QWidget
{
    Q_OBJECT
public:
    explicit WinMainStatus(QWidget *parent = 0);

signals:

public slots:

};

class WinMainFrame : public QWidget
{
    Q_OBJECT
public:
    static WinMainFrame *instance();
    void addWorkWin(QWidget *workWin);

private:
    explicit WinMainFrame(QWidget *parent = 0);

signals:

public slots:

private:
    void initialize();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    WinMainStatus   m_statusBar;
    QStackedWidget  m_workWinStacked;
    QVBoxLayout *p_mainLayout;
};

#endif // WINMAINFRAME_H
