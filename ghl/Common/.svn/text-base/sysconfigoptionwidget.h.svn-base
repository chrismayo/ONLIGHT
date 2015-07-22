#ifndef SYSCONFIGOPTIONWIDGET_H
#define SYSCONFIGOPTIONWIDGET_H

#include <QPushButton>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QLabel>

class SysConfigOptionWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit SysConfigOptionWidget(QPushButton *parent = 0, int index = 0);
    ~SysConfigOptionWidget();

    int setTargetWidgetIndex(int index);
    int setTitle(QString title);
    int setContent(QString content);

signals:
    void sigTargetWidgetIndex(int index, QString content);

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

private:
    QLabel m_labelModified, m_labelTitle, m_labelContent;
    QHBoxLayout *p_hLayOut;
    int m_targetIndex;



};

#endif // SYSCONFIGOPTIONWIDGET_H
