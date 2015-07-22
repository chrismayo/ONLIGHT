#ifndef WINMULTIPANEL_H
#define WINMULTIPANEL_H

#include <QWidget>
#include <QGridLayout>

class WinMultiPanel : public QWidget
{
    Q_OBJECT
public:
    explicit WinMultiPanel(QWidget *parent = 0);

    bool eventFilter(QObject *, QEvent *);
signals:

public slots:

private:
    QGridLayout *m_gridLayout;
};

#endif // WINMULTIPANEL_H
