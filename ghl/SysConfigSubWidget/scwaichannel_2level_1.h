#ifndef SCWAICHANNEL_2LEVEL_1_H
#define SCWAICHANNEL_2LEVEL_1_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "./Common/sysconfigoptionwidget.h"

class SCWAiChannel_2Level_1: public QWidget
{
    Q_OBJECT
public:
    explicit SCWAiChannel_2Level_1(QWidget *parent = 0);
    ~SCWAiChannel_2Level_1();

signals:
    void sigNextWidgetIndex(int index, QString content);

private slots:
    void slotNextSendWidgetIndex(int index, QString content);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QVBoxLayout *p_vlayout;
    SysConfigOptionWidget *p_settingOption;
};

#endif // SCWAICHANNEL_2LEVEL_1_H
