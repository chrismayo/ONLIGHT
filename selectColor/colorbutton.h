#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QLabel>
#include <QMouseEvent>
class ColorButton : public QLabel
{
    Q_OBJECT
public:
     ColorButton(QWidget *parent = 0);

protected:
     void mousePressEvent(QMouseEvent *ev);

signals:
     void sigLabelClicked();

public slots:

};

#endif // COLORBUTTON_H
