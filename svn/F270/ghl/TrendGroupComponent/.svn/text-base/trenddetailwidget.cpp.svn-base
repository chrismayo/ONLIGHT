#include "trenddetailwidget.h"

TrendDetailWidget::TrendDetailWidget(QGraphicsView *parent) :
    QGraphicsView(parent)
{
    initialize();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

TrendDetailWidget::~TrendDetailWidget()
{
    release();
}

void TrendDetailWidget::slotPaperPosChange(bool stat)
{
    if (stat  == true)
    {
        switch (m_paperPosState) {
        case 123:  //123
            m_paperPosState = 231;
            p_recordPaper1->move(p_recordPaper3->pos().x()+p_recordPaper3->width(), 0);
            break;
        case 312: //312
            m_paperPosState = 123;
            p_recordPaper3->move(p_recordPaper2->pos().x()+p_recordPaper2->width(), 0);
            break;
        case 231://231
            m_paperPosState = 312;
            p_recordPaper2->move(p_recordPaper1->pos().x()+p_recordPaper1->width(), 0);
            break;
        default:
            break;
        }
    }
    if (stat == false)
    {
        switch (m_paperPosState) {
        case 123:  //123
            m_paperPosState = 312;
            p_recordPaper3->move(p_recordPaper1->pos().x()-p_recordPaper1->width(), 0);
            break;
        case 312: //312
            m_paperPosState = 231;
            p_recordPaper2->move(p_recordPaper3->pos().x()-p_recordPaper3->width(), 0);
            break;
        case 231://231
            m_paperPosState = 123;
            p_recordPaper1->move(p_recordPaper2->pos().x()-p_recordPaper2->width(), 0);
            break;
        default:
            break;
    }
    }
}

void TrendDetailWidget::initialize()
{
    m_isPress = false;
    m_paperMoveStep = 0;
    m_prePoint = QPoint(0,0);
    m_paperPosState = 123;
    p_pb_overviewTrend = new QPushButton(this);
    p_pb_inforChar = new QPushButton(this);
    p_pb_inforHand = new QPushButton(this);
    p_pb_moveEnd = new QPushButton(this);
    p_pb_moveStart = new QPushButton(this);
    p_pb_moveLeftStep = new QPushButton(this);
    p_pb_moveRightStep = new QPushButton(this);
    p_qt_pbTimer = new QTimer();
    p_qt_pbTimer->setSingleShot(true);

    p_graphicScene = new QGraphicsScene();
    p_recordPaper1 = new TrendRecordPaper(0, 1);
    p_recordPaper2 = new TrendRecordPaper(0, 2);
    p_recordPaper3 = new TrendRecordPaper(0, 3);
    p_handInforPaper = new TrendHandWritingPaper();

    slotPBTimerOut();
}
void TrendDetailWidget::release()
{
    delete p_pb_overviewTrend;
    delete p_pb_inforChar;
    delete p_pb_inforHand;
    delete p_pb_moveEnd;
    delete p_pb_moveStart;
    delete p_pb_moveLeftStep;
    delete p_pb_moveRightStep;

    delete p_qt_pbTimer;

    delete p_graphicScene;
    delete p_recordPaper1;
    delete p_recordPaper2;
    delete p_recordPaper3;
    delete p_handInforPaper;
}

void TrendDetailWidget::setUserDefineStyle()
{
    p_pb_moveEnd->resize(150,40);
    p_pb_moveLeftStep->resize(150, 40);
    p_pb_moveRightStep->resize(150, 40);
    p_pb_moveStart->resize(150,40);
    p_pb_overviewTrend->move(0, rect().height()/3);
    p_pb_inforChar->move(0, rect().height()/3+p_pb_overviewTrend->size().height());
    p_pb_inforHand->move(0, rect().height()/3+p_pb_overviewTrend->size().height()+p_pb_inforChar->size().height());

    p_pb_moveEnd->move(rect().width()/3, rect().height()-p_pb_moveEnd->height());
    p_pb_moveLeftStep->move(rect().width()/3+p_pb_moveEnd->size().width(), rect().height()-p_pb_moveLeftStep->height());
    p_pb_moveRightStep->move(rect().width()/3+p_pb_moveEnd->size().width()+p_pb_moveLeftStep->size().width(),  rect().height()-p_pb_moveRightStep->height());
    p_pb_moveStart->move(rect().width()/3+p_pb_moveEnd->size().width()+p_pb_moveLeftStep->size().width()+p_pb_moveRightStep->size().width(), rect().height()-p_pb_moveStart->height());

    p_recordPaper1->resize(rect().width()*3, rect().height());
    p_recordPaper2->resize(rect().width()*3, rect().height());
    p_recordPaper3->resize(rect().width()*3, rect().height());

    p_recordPaper1->move(0,0);
    p_recordPaper2->move(p_recordPaper1->width(), 0);
    p_recordPaper3->move(p_recordPaper1->width()*2, 0);
    p_handInforPaper->moveBy(0, 0);

    m_watchPoint = p_recordPaper1->width();
    p_graphicScene->setSceneRect(p_recordPaper1->width(),0, rect().width(), rect().height());
}

void TrendDetailWidget::setUserDefineContent()
{
    p_pb_overviewTrend->setText(QString("overviewTrend"));
    p_pb_inforChar->setText(QString("inforChar"));
    p_pb_inforHand->setText(QString("inforHand"));

    p_pb_moveEnd->setText(QString("toEnd"));
    p_pb_moveStart->setText(QString("toStart"));
    p_pb_moveLeftStep->setText(QString("moveLeftStep"));
    p_pb_moveRightStep->setText(QString("moveRightStep"));

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TrendDetailWidget::setWinLayout()
{
    p_graphicScene->addWidget(p_recordPaper1);
    p_graphicScene->addWidget(p_recordPaper2);
    p_graphicScene->addWidget(p_recordPaper3);
    p_graphicScene->addItem(p_handInforPaper); //绘制 手写信息图层

    setScene(p_graphicScene);
}

void TrendDetailWidget::sigAndSlotConnect()
{
    connect(p_qt_pbTimer, SIGNAL(timeout()), this, SLOT(slotPBTimerOut()));

    connect(p_pb_overviewTrend, SIGNAL(clicked()), this, SLOT(slotPBOverviewTrendIsClicked()));
    connect(p_pb_inforChar, SIGNAL(clicked()), this, SLOT(slotPBInforCharIsClicked()));
    connect(p_pb_inforHand, SIGNAL(clicked()), this, SLOT(slotPBInforHandIsClicked()));
    connect(p_pb_moveEnd, SIGNAL(clicked()), this, SLOT(slotPBMoveEndIsClicked()));
    connect(p_pb_moveRightStep, SIGNAL(clicked()), this, SLOT(slotPBMoveRightIsClicked()));
    connect(p_pb_moveLeftStep, SIGNAL(clicked()), this, SLOT(slotPBMoveLeftIsClicked()));
    connect(p_pb_moveStart, SIGNAL(clicked()), this, SLOT(slotPBMoveStartIsClicked()));
}

void TrendDetailWidget::showControlPB()
{
    p_pb_overviewTrend->show();
    p_pb_inforChar->show();
    p_pb_inforHand->show();
    p_pb_moveEnd->show();
    p_pb_moveLeftStep->show();
    p_pb_moveRightStep->show();
    p_pb_moveStart->show();
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::paperMove(int stepX)
{
    p_recordPaper1->move(p_recordPaper1->x()+stepX, p_recordPaper1->y());
    p_recordPaper2->move(p_recordPaper2->x()+stepX, p_recordPaper2->y());
    p_recordPaper3->move(p_recordPaper3->x()+stepX, p_recordPaper3->y());
}

void TrendDetailWidget::slotPBTimerOut()
{
    p_pb_overviewTrend->hide();
    p_pb_inforChar->hide();
    p_pb_inforHand->hide();
    p_pb_moveEnd->hide();
    p_pb_moveLeftStep->hide();
    p_pb_moveRightStep->hide();
    p_pb_moveStart->hide();
}

void TrendDetailWidget::slotPBOverviewTrendIsClicked()
{
    emit(sigOverviewTrend());
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBInforHandIsClicked()
{
    emit(sigInforHand());
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBInforCharIsClicked()
{
    emit(sigInforChar());
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBMoveStartIsClicked()
{
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBMoveEndIsClicked()
{
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBMoveLeftIsClicked()
{
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::slotPBMoveRightIsClicked()
{
    p_qt_pbTimer->start(PB_Show_Time);
}

void TrendDetailWidget::resizeEvent(QResizeEvent *e)
{
    setUserDefineStyle();
    QGraphicsView::resizeEvent(e);
}

void TrendDetailWidget::mousePressEvent(QMouseEvent *event)
{
    if (p_pb_inforChar->isHidden())
        showControlPB();
    m_isPress = true;
    m_prePoint = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void TrendDetailWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPress = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void TrendDetailWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_isPress == true)
    {
        m_watchPoint = m_watchPoint-(e->pos().x() - m_prePoint.x());
        m_paperMoveStep = m_paperMoveStep +(e->pos().x() - m_prePoint.x());
//        paperMove(e->pos().x() - m_prePoint.x());
         p_graphicScene->setSceneRect(m_watchPoint,0, rect().width(), rect().height());
        m_prePoint = e->pos();
    }
    QGraphicsView::mouseMoveEvent(e);
}

void TrendDetailWidget::paintEvent(QPaintEvent *e)
{
    QGraphicsView::paintEvent(e);
}
