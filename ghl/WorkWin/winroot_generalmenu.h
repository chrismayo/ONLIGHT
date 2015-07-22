#ifndef WINROOT_GENERALMENU_H
#define WINROOT_GENERALMENU_H

#include <QWidget>

class WinRoot_GeneralMenu : public QWidget
{
    Q_OBJECT
public:
    explicit WinRoot_GeneralMenu(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // WINROOT_GENERALMENU_H
