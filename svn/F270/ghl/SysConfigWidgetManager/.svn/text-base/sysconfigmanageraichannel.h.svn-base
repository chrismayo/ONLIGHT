#ifndef SYSCONFIGMANAGERAICHANNEL_H
#define SYSCONFIGMANAGERAICHANNEL_H

#include <QObject>

#include "../Common/sysconfigslidingscreen.h"

#include "../SysConfigSubWidget/scwaichannel_1level.h"
#include "../SysConfigSubWidget/scwaichannel_2level_1.h"
#include "../SysConfigSubWidget/scwaichannel_3level_1.h"

class SysConfigManagerAiChannel : public QObject
{
    Q_OBJECT
public:
    explicit SysConfigManagerAiChannel(QObject *parent = 0, SysConfigSlidingScreen * sliding = nullptr);
    ~SysConfigManagerAiChannel();

    void setSlidingScreen(SysConfigSlidingScreen * sp);

signals:

public slots:
    void slotSlidingWidget(int index, QString content);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QVector<QWidget *> *p_leve1Widget, *p_leve2Widget, *p_leve3Widget;

    SCWAiChannel_1Level *p_widget_1Level_1;
    SCWAiChannel_2Level_1 *p_widget_2Level_1;
    SCWAiChannel_3Level_1 *p_widget_3Level_1;

    SysConfigSlidingScreen *p_sliding;

};

#endif // SYSCONFIGMANAGERAICHANNEL_H
