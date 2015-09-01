#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class myButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
signals:
    void buttonClicked(QResizeEvent * event);
private:
    QResizeEvent* event;

};

#endif // MYBUTTON_H
