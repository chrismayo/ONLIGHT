#ifndef CHANNELBUTTON_H
#define CHANNELBUTTON_H

#include <QPushButton>

class ChannelButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ChannelButton(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *e);
signals:
    void sigMouseMove(int x, int y);

public slots:

};

#endif // CHANNELBUTTON_H
