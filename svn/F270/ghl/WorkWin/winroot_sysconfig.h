#ifndef WINROOT_SYSCONFIG_H
#define WINROOT_SYSCONFIG_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QResizeEvent>
#include <QDebug>
#include <QScrollArea>

#include "../Common/sysconfigslidingscreen.h"
#include "../Common/sysconfignaviwidget.h"
#include "../SysConfigWidgetManager/sysconfigmanageraichannel.h"

class WinRoot_SysConfig : public QWidget
{
    Q_OBJECT
public:
explicit WinRoot_SysConfig(QWidget *parent = 0);
    ~WinRoot_SysConfig();

signals:

public slots:

private slots:
    void slotNavigationSwitch(int widgetIndex);

protected:
    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent *);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();


private:
    QHBoxLayout    *p_hLayout_Main;         //总体布局
    QVBoxLayout    *p_vLayout_Navigation;   //导航布局
    QWidget    *p_vWidget_Navigation;
    QScrollArea    *p_scrollArea;

    QVector<SysConfigNaviWidget *> *p_navWidget;   //导航窗体指针容器

    SysConfigSlidingScreen *p_sysConfigSlidingScreen;
    SysConfigManagerAiChannel *p_manageAiChannel;

};

#endif // WINROOT_SYSCONFIG_H
