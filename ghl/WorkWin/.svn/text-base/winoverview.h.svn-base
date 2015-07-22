#ifndef WINOVERVIEW_H
#define WINOVERVIEW_H

#include <QWidget>
#include <QTableView>
#include <QStackedLayout>
#include <QModelIndex>

class WinOverView : public QWidget
{
    Q_OBJECT
public:
    explicit WinOverView(QWidget *parent = 0);

protected:
    class WinChannelView : public QTableView
    {
       // Q_OBJECT
        friend class WinOverView;
    public:
        explicit WinChannelView(QWidget *parent = 0);
    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        QStyleOptionViewItem viewOptions() const;

    private:
        bool m_pressed;
        QRect m_rect;
    };

protected:
    void paintEvent(QPaintEvent *);

signals:
    void sigNextFrame();                 //下一帧
    void sigPreviousFrame();          //前一帧
    void sigGoTrand();                    //转到趋势图
    void sigGoBack();                      //回退

public slots:
    void slotSwitchFrame(QModelIndex ); //切换显示画面

private:
    WinChannelView *m_allChannelView;
    WinChannelView *m_allGroupView;
    QStackedLayout  *m_layout;
};



#endif // WINOVERVIEW_H
