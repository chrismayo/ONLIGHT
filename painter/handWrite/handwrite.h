#ifndef HANDWRITE_H
#define HANDWRITE_H

#include <QMouseEvent>
#include <QWidget>
class QPushButton;
class QButtonGroup;
class HandWrite : public QWidget
{
    Q_OBJECT

public:
    HandWrite(QWidget *parent = 0);
    ~HandWrite();

private:
    enum {
        Choice_BlackSlim = 0,
        Choice_BlackCommon,
        Choice_BlackThick,
        Choice_RedSlim,
        Choice_RedCommon,
        Choice_RedThick,
        Choice_BlueSlim,
        Choice_BlueCommon,
        Choice_BlueThick,
        Choice_Eraser
    };
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void slotSelectPalette(int id);
    void slotPaletteButtonClicked();
    void slotCancelButtonClicked();
    void slotIndividualSave();
    void slotCommonSave();
    void slotPenButtonClicked();
private:
    void drawImage();
    void setSizeOfWindows();
    void setFrameWidget();
    void setPaletteWidget();
    void setPaletteGroup();
    void paint(QImage& theImage);
private:
    QImage  image;
    QPoint lastPoint,endPoint;
    QButtonGroup* paletteGroup;
    QWidget* frameWidget;
    QWidget* paletteWidget;
    QPushButton* cancelButton;
    QPushButton* penButton;
    QPushButton* paletteButton;
    QPushButton* eraserButton;
    QPushButton* undoButton;
    QPushButton* individualSave;
    QPushButton* commonSave;
    QPushButton* blackSlim;
    QPushButton* blackCommon;
    QPushButton* blackThick;
    QPushButton* redSlim;
    QPushButton* redCommon;
    QPushButton* redThick;
    QPushButton* blueSlim;
    QPushButton* blueCommon;
    QPushButton* blueThick;
    int current_heigh;
    int current_width;
    int paletteChoice;
    int paletteChoice_bak;
};

#endif // HANDWRITE_H
