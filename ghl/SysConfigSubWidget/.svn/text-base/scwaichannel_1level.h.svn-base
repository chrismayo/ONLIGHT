#ifndef SCWAICHANNEL_1LEVEL_H
#define SCWAICHANNEL_1LEVEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "./Common/sysconfigoptionwidget.h"

class SCWAiChannel_1Level : public QWidget
{
    Q_OBJECT
public:
    explicit SCWAiChannel_1Level(QWidget *parent = 0);
    ~SCWAiChannel_1Level();

signals:
    void sigNextWidgetIndex(int index, QString content);

public slots:
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

#endif // SCWAICHANNEL_1LEVEL_H
