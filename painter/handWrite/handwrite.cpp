#include "handwrite.h"
#include <QImage>
#include <QRgb>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QButtonGroup>
HandWrite::HandWrite(QWidget *parent)
    : QWidget(parent)
    , paletteGroup(NULL)
    , frameWidget(NULL)
    , paletteWidget(NULL)
    , cancelButton(NULL)
    , penButton(NULL)
    , paletteButton(NULL)
    , eraserButton(NULL)
    , undoButton(NULL)
    , tempNameButton1(NULL)
    , tempNameButton2(NULL)
    , blackSlim(NULL)
    , blackCommon(NULL)
    , blackThick(NULL)
    , redSlim(NULL)
    , redCommon(NULL)
    , redThick(NULL)
    , blueSlim(NULL)
    , blueCommon(NULL)
    , blueThick(NULL)
    , paletteChoice(1)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setSizeOfWindows();
    drawImage();
    setFrameWidget();
    setPaletteWidget();
    setPaletteGroup();
    paletteWidget->setHidden(true);
    connect(paletteGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotSelectPalette(int)));
    connect(paletteButton, SIGNAL(clicked()), this, SLOT(slotPaletteButtonClicked()));
}

HandWrite::~HandWrite()
{

}

void HandWrite::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),QColor(28, 28, 28, 100));
    painter.drawImage(0, (int)(current_heigh * 0.1),image);

}

void HandWrite::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint.setX(event->x());
        lastPoint.setY(event->y() - (int)(current_heigh * 0.1));
    }
}

void HandWrite::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton) {
        endPoint.setX(event->x());
        endPoint.setY(event->y() - (int)(current_heigh * 0.1));
        paint(image);
    }
}

void HandWrite::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        endPoint.setX(event->x());
        endPoint.setY(event->y() - (int)(current_heigh * 0.1));
        paint(image);
    }
}

void HandWrite::paint(QImage &theImage)
{
    QPainter draw(&theImage);
    draw.setRenderHint(QPainter::Antialiasing, true);
    draw.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    switch (paletteChoice) {
    case Choice_BlackSlim:
        draw.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_BlackCommon:
        draw.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_BlackThick:
        draw.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_RedSlim:
        draw.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_RedCommon:
        draw.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_RedThick:
        draw.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_BlueSlim:
        draw.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_BlueCommon:
        draw.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_BlueThick:
        draw.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap));
        break;
    case Choice_Eraser:
        draw.setPen(QPen(Qt::white, 6, Qt::SolidLine, Qt::RoundCap));
        break;
    default:
        break;
    }
    if ((endPoint.x() < (int)(current_width * 0.8))) {

        draw.drawLine(lastPoint, endPoint);
        lastPoint = endPoint;
        update();
    } else {
        // do nothing
    }
}

void HandWrite::slotSelectPalette(int id)
{
    paletteWidget->setHidden(true);
    switch (id) {
    case 0:
        paletteChoice = Choice_BlackSlim;
        qDebug() << "0";
        break;
    case 1:
        paletteChoice = Choice_BlackCommon;
        break;
    case 2:
        paletteChoice = Choice_BlackThick;
        break;
    case 3:
        paletteChoice = Choice_RedSlim;
        break;
    case 4:
        paletteChoice = Choice_RedCommon;
        break;
    case 5:
        paletteChoice = Choice_RedThick;
        break;
    case 6:
        paletteChoice = Choice_BlueSlim;
        break;
    case 7:
        paletteChoice = Choice_BlueCommon;
        break;
    case 8:
        paletteChoice = Choice_BlueThick;
        break;
    case 9:
        paletteChoice = Choice_Eraser;
        break;
    default:
        break;
    }
}

void HandWrite::slotPaletteButtonClicked()
{
    paletteWidget->setHidden(false);
}

void HandWrite::drawImage()
{
    image = QImage((int)(current_width * 0.8), (int)(current_heigh * 0.9), QImage::Format_RGB32);
    image.fill(Qt::white);
}

void HandWrite::setSizeOfWindows()
{
    current_width = QApplication::desktop()->width();
    current_heigh = QApplication::desktop()->height();
    resize(current_width, current_heigh);
}

void HandWrite::setFrameWidget()
{
    frameWidget = new QWidget(this);
    frameWidget->setGeometry((int)(0.9 * current_width), 0, (int)(0.1 * current_width), current_heigh);
    frameWidget->setStyleSheet("background-color: rgb(239, 241, 232)");
    cancelButton = new QPushButton(frameWidget);
    cancelButton->setText(tr("Cancel"));
    cancelButton->setGeometry(0, 0, (int)(0.1 * current_width), (int)(0.06 * current_heigh));

    /////////////////////////////////////////////////////////////////////////////////////////
    tempNameButton1 = new QPushButton(frameWidget);
    tempNameButton1->setText(tr("Save as"));
    tempNameButton1->setGeometry(0, (int)(0.94 * current_heigh), (int)(0.1 * current_width), (int)(0.06 * current_heigh));

    tempNameButton2 = new QPushButton(frameWidget);
    tempNameButton2->setText(tr("Save"));
    tempNameButton2->setGeometry(0, (int)(0.88 * current_heigh), (int)(0.1 * current_width), (int)(0.06 * current_heigh));

    ///////////////////////////////////////////////////////////////////////////////////////////

    penButton = new QPushButton(frameWidget);
    penButton->setText(tr("Brush"));
    penButton->setGeometry(0, (int)(0.3 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));

    paletteButton = new QPushButton(frameWidget);
    paletteButton->setText(tr("Palette"));
    paletteButton->setGeometry(0, (int)(0.38 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));

    eraserButton = new QPushButton(frameWidget);
    eraserButton->setText(tr("Eraser"));
    eraserButton->setGeometry(0, (int)(0.46 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));

    undoButton = new QPushButton(frameWidget);
    undoButton->setText(tr("Undo"));
    undoButton->setGeometry(0, (int)(0.54 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));
}

void HandWrite::setPaletteWidget()
{
    paletteWidget = new QWidget(this);
    paletteWidget->setGeometry((int)(0.6 * current_width), (int)(0.34 * current_heigh), (int)(0.3 * current_width), (int)(0.24 * current_heigh));
    paletteWidget->setStyleSheet("background-color: rgb(239, 241, 232)");

    blackSlim = new QPushButton(paletteWidget);
    blackCommon = new QPushButton(paletteWidget);
    blackThick = new QPushButton(paletteWidget);

    redSlim = new QPushButton(paletteWidget);
    redCommon = new QPushButton(paletteWidget);
    redThick = new QPushButton(paletteWidget);

    blueSlim = new QPushButton(paletteWidget);
    blueCommon = new QPushButton(paletteWidget);
    blueThick = new QPushButton(paletteWidget);

    blackSlim->setText(tr("black slim"));
    blackCommon->setText(tr("black common"));
    blackThick->setText(tr("black thick"));

    redSlim->setText(tr("red slim"));
    redCommon->setText(tr("red common"));
    redThick->setText(tr("red thick"));

    blueSlim->setText(tr("blue slim"));
    blueCommon->setText(tr("blue common"));
    blueThick->setText(tr("blue thick"));

    blackSlim->setGeometry(0, 0, (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    blackCommon->setGeometry((int)(0.1 * current_width), 0, (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    blackThick->setGeometry((int)(0.2 * current_width), 0, (int)(0.1 * current_width), (int)(0.08 * current_heigh));

    redSlim->setGeometry(0, (int)(0.08 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    redCommon->setGeometry((int)(0.1 * current_width), (int)(0.08 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    redThick->setGeometry((int)(0.2 * current_width), (int)(0.08 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));

    blueSlim->setGeometry(0, (int)(0.16 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    blueCommon->setGeometry((int)(0.1 * current_width), (int)(0.16 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));
    blueThick->setGeometry((int)(0.2 * current_width), (int)(0.16 * current_heigh), (int)(0.1 * current_width), (int)(0.08 * current_heigh));

}

void HandWrite::setPaletteGroup()
{
    paletteGroup = new QButtonGroup;
    paletteGroup->addButton(blackSlim, 0);
    paletteGroup->addButton(blackCommon, 1);
    paletteGroup->addButton(blackThick, 2);
    paletteGroup->addButton(redSlim, 3);
    paletteGroup->addButton(redCommon, 4);
    paletteGroup->addButton(redThick, 5);
    paletteGroup->addButton(blueSlim, 6);
    paletteGroup->addButton(blueCommon, 7);
    paletteGroup->addButton(blueThick, 8);
    paletteGroup->addButton(eraserButton, 9);
}
