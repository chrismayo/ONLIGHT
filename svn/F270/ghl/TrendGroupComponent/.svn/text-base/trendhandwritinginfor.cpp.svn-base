#include "trendhandwritinginfor.h"

TrendHandWritingInfor::TrendHandWritingInfor(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
    m_flag = true;
}

TrendHandWritingInfor::~TrendHandWritingInfor()
{
    release();
}

void TrendHandWritingInfor::slotHide()
{
    this->hide();
    p_picture->clear();
    p_pictures->clear();
}

void TrendHandWritingInfor::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
}

void TrendHandWritingInfor::paintEvent(QPaintEvent *e)
{
    QPen backPen;

    backPen.setStyle(Qt::SolidLine);
    backPen.setColor(Qt::red);
    backPen.setWidth(10);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(backPen);
    if (!p_pictures->isEmpty())
    {
        for (int i = 0; i < p_pictures->length(); ++i)
        {
            for(int j = 0; j<p_pictures->at(i).length()-1; ++j)
                painter.drawLine(p_pictures->at(i).at(j), p_pictures->at(i).at(j+1));
        }
    }

    if (!p_picture->isEmpty())
    {
        for(int i = 0; i<p_picture->length()-1; ++i)
            painter.drawLine(p_picture->at(i), p_picture->at(i+1));
    }
    if (m_flag)
    {
    QPainter painter2(p_imageFile);
     painter2.fillRect(0, 0, rect().width(), rect().height(), QBrush(QColor("white")));
     m_flag = false;
    }
    QWidget::paintEvent(e);

}

void TrendHandWritingInfor::mouseMoveEvent(QMouseEvent *e)
{
    QPointF point2 = e->pos();
    p_picture->append(point2);
    repaint();
    QWidget::mouseMoveEvent(e);
}

void TrendHandWritingInfor::mouseReleaseEvent(QMouseEvent *e)
{
    if (!p_picture->isEmpty())
    {
        p_pictures->append(*p_picture);
        p_picture->clear();
        this->render(p_imageFile);
        qDebug()<<"is save ok"<<p_imageFile->save(QString("hand"),"JPG");
    }
    QWidget::mouseReleaseEvent(e);
}

void TrendHandWritingInfor::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}


void TrendHandWritingInfor::initialize()
{
    p_gLayout = new QGridLayout();
    p_picture = new QVector<QPointF>();
    p_pictures = new QVector<QVector<QPointF>>();
    p_imageFile = new QImage(800,600,QImage::Format_RGB32);

    m_close.setText(QString("close"));
    m_close.setParent(this);
    setMouseTracking(false);

}

void TrendHandWritingInfor::release()
{
    delete p_gLayout;
    delete p_picture;
    delete p_pictures;
    delete p_imageFile;
}

void TrendHandWritingInfor::setUserDefineStyle()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
//    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint);
//    setWindowOpacity(0.1);
//    setAttribute(Qt::WA_TranslucentBackground, true);

//    setWindowFlags(Qt::WindowStaysOnTopHint);
//    setStyleSheet("QWidget#main {background-color: rgba(0, 0, 0, 4%)}");
}

void TrendHandWritingInfor::setUserDefineContent()
{
}

void TrendHandWritingInfor::setWinLayout()
{
//    p_pButton_handle->show();
//    p_gLayout->addWidget(p_pButton_handle, 0,0, 1, 1);
//    p_gLayout->addWidget(p_pButton_over, 0, 1, 1, 1);
//    setLayout(p_gLayout);
}

void TrendHandWritingInfor::sigAndSlotConnect()
{
    connect(&m_close, SIGNAL(clicked()), this, SLOT(slotHide()));
}

