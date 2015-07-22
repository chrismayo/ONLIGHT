#include "slidingscreen.h"

/*
 * 功能：
 * 	  构造函数，初始化有限状态机并run之。
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
SlidingScreen::SlidingScreen(QGraphicsView *parent, bool isOneDirection):
        QGraphicsView(parent), m_isOneDirection(isOneDirection)
{
    m_enable = false;
    m_enableSliding = true;
    m_pressPos.setX(0);
    m_pressPos.setY(0);
    m_releasePos.setX(0);
    m_releasePos.setY(0);

    p_frame1 = new QFrame();
    p_frame2 = new QFrame();
    p_frame3 = new QFrame();

    p_layout1 = new QStackedLayout();
    p_layout2 = new QStackedLayout();
    p_layout3 = new QStackedLayout();

    m_layOut[0] = p_layout1;
    m_layOut[1] = p_layout2;
    m_layOut[2] = p_layout3;

    /****初始化窗体指针缓存，索引缓存，索引缓存长度*********/
    p_widgetBuf = new QVector<QWidget*>(BUF_LEN, nullptr);
    p_indexBuf = new QVector<int>();

    p_frame1->resize(DESKTOP_WIDTH,DESKTOP_HEIGHT);
    p_frame2->resize(DESKTOP_WIDTH,DESKTOP_HEIGHT);
    p_frame3->resize(DESKTOP_WIDTH,DESKTOP_HEIGHT);

    p_frame1->setLayout(p_layout1);
    p_frame2->setLayout(p_layout2);
    p_frame3->setLayout(p_layout3);

/**************动画类实例化**********************/
    p_group = new QParallelAnimationGroup;
    p_frame1Animation = new QPropertyAnimation(p_frame1, "pos");
    p_frame2Animation = new QPropertyAnimation(p_frame2, "pos");
    p_frame3Animation = new QPropertyAnimation(p_frame3, "pos");

    p_frame1Animation->setDuration(1200);
    p_frame2Animation->setDuration(1200);
    p_frame3Animation->setDuration(1200);
    p_frame1Animation->setEasingCurve(QEasingCurve::InOutQuad);
    p_frame2Animation->setEasingCurve(QEasingCurve::InOutQuad);
    p_frame3Animation->setEasingCurve(QEasingCurve::InOutQuad);

    p_group->addAnimation(p_frame1Animation);
    p_group->addAnimation(p_frame2Animation);
    p_group->addAnimation(p_frame3Animation);

    connect(p_group, SIGNAL(finished()), this, SLOT(slotAnimationFinish()));
/***********************状态机实例化*******************************/
    p_stateMachine = new QStateMachine(this);
    p_startState = new QState();

    p_leftState1 = new QState(p_startState);
    p_leftState2 = new QState(p_startState);
    p_leftState3 = new QState(p_startState);

    p_rightState1 = new QState(p_startState);
    p_rightState2 = new QState(p_startState);
    p_rightState3 = new QState(p_startState);

    p_upState1 = new QState(p_startState);
    p_upState2 = new QState(p_startState);
    p_upState3 = new QState(p_startState);

    p_downState1 = new QState(p_startState);
    p_downState2 = new QState(p_startState);
    p_downState3 = new QState(p_startState);

/*********************move to left state*************************************/
    p_leftState1->assignProperty(p_frame1, "visible", true);
    p_leftState1->assignProperty(p_frame2, "visible", true);
    p_leftState1->assignProperty(p_frame3, "visible", false);
    p_leftState1->assignProperty(p_frame1, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_leftState1->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_leftState1->assignProperty(p_frame3, "pos", QPointF(2*DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_leftState1->assignProperty(p_frame1, "objectName", QString("1"));   //存放当前显示的frame索引号

    p_leftState2->assignProperty(p_frame2, "visible", true);
    p_leftState2->assignProperty(p_frame3, "visible", true);
    p_leftState2->assignProperty(p_frame1, "visible", false);
    p_leftState2->assignProperty(p_frame2, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_leftState2->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_leftState2->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH*2, DESKTOP_HEIGHT));
    p_leftState2->assignProperty(p_frame1, "objectName", QString("2"));

    p_leftState3->assignProperty(p_frame3, "visible", true);
    p_leftState3->assignProperty(p_frame1, "visible", true);
    p_leftState3->assignProperty(p_frame2, "visible", false);
    p_leftState3->assignProperty(p_frame3, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_leftState3->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_leftState3->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH*2, DESKTOP_HEIGHT));
    p_leftState3->assignProperty(p_frame1, "objectName", QString("0"));

/***************move to right state*********************************/
    p_rightState1->assignProperty(p_frame1, "visible", false);
    p_rightState1->assignProperty(p_frame2, "visible", true);
    p_rightState1->assignProperty(p_frame3, "visible", true);
    p_rightState1->assignProperty(p_frame1, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_rightState1->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_rightState1->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH*2, DESKTOP_HEIGHT));
    p_rightState1->assignProperty(p_frame1, "objectName", QString("1"));

    p_rightState2->assignProperty(p_frame2, "visible", false);
    p_rightState2->assignProperty(p_frame3, "visible", true);
    p_rightState2->assignProperty(p_frame1, "visible", true);
    p_rightState2->assignProperty(p_frame2, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_rightState2->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_rightState2->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH*2, DESKTOP_HEIGHT));
    p_rightState2->assignProperty(p_frame1, "objectName", QString("2"));

    p_rightState3->assignProperty(p_frame3, "visible", false);
    p_rightState3->assignProperty(p_frame1, "visible", true);
    p_rightState3->assignProperty(p_frame2, "visible", true);
    p_rightState3->assignProperty(p_frame3, "pos", QPointF(0, DESKTOP_HEIGHT));
    p_rightState3->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_rightState3->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH*2, DESKTOP_HEIGHT));
    p_rightState3->assignProperty(p_frame1, "objectName", QString("0"));

/***********************move to up state******************************************/
    p_upState1->assignProperty(p_frame1, "visible", true);
    p_upState1->assignProperty(p_frame2, "visible", true);
    p_upState1->assignProperty(p_frame3, "visible", false);
    p_upState1->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_upState1->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_upState1->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_upState1->assignProperty(p_frame1, "objectName", QString("1"));

    p_upState2->assignProperty(p_frame2, "visible", true);
    p_upState2->assignProperty(p_frame3, "visible", true);
    p_upState2->assignProperty(p_frame1, "visible", false);
    p_upState2->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_upState2->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_upState2->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_upState2->assignProperty(p_frame1, "objectName", QString("2"));

    p_upState3->assignProperty(p_frame3, "visible", true);
    p_upState3->assignProperty(p_frame1, "visible", true);
    p_upState3->assignProperty(p_frame2, "visible", false);
    p_upState3->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_upState3->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_upState3->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_upState3->assignProperty(p_frame1, "objectName", QString("0"));

/*************************move to down state *************************************/
    p_downState1->assignProperty(p_frame1, "visible", false);
    p_downState1->assignProperty(p_frame2, "visible", true);
    p_downState1->assignProperty(p_frame3, "visible", true);
    p_downState1->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_downState1->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_downState1->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_downState1->assignProperty(p_frame1, "objectName", QString("1"));

    p_downState2->assignProperty(p_frame2, "visible", false);
    p_downState2->assignProperty(p_frame3, "visible", true);
    p_downState2->assignProperty(p_frame1, "visible", true);
    p_downState2->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_downState2->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_downState2->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_downState2->assignProperty(p_frame1, "objectName", QString("2"));

    p_downState3->assignProperty(p_frame3, "visible", false);
    p_downState3->assignProperty(p_frame1, "visible", true);
    p_downState3->assignProperty(p_frame2, "visible", true);
    p_downState3->assignProperty(p_frame3, "pos", QPointF(DESKTOP_WIDTH, 0));
    p_downState3->assignProperty(p_frame1, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT));
    p_downState3->assignProperty(p_frame2, "pos", QPointF(DESKTOP_WIDTH, DESKTOP_HEIGHT*2));
    p_downState3->assignProperty(p_frame1, "objectName", QString("0"));

/*************************收到向右滑动信号*********************绑定状态切换转换和动画效果***/  
    QSignalTransition *rightTransition = p_rightState1->addTransition(this, SIGNAL(sigMoveRight()), p_rightState3);
    rightTransition->addAnimation(p_group);
    rightTransition = p_rightState2->addTransition(this, SIGNAL(sigMoveRight()), p_rightState1);
    rightTransition->addAnimation(p_group);
    rightTransition = p_rightState3->addTransition(this, SIGNAL(sigMoveRight()), p_rightState2);
    rightTransition->addAnimation(p_group);

    rightTransition = p_leftState1->addTransition(this, SIGNAL(sigMoveRight()), p_rightState3);
    rightTransition->addAnimation(p_group);
    rightTransition = p_leftState2->addTransition(this, SIGNAL(sigMoveRight()), p_rightState1);
    rightTransition->addAnimation(p_group);
    rightTransition = p_leftState3->addTransition(this, SIGNAL(sigMoveRight()), p_rightState2);
    rightTransition->addAnimation(p_group);

    p_upState1->addTransition(this, SIGNAL(sigMoveRight()), p_rightState1);
    p_upState2->addTransition(this, SIGNAL(sigMoveRight()), p_rightState2);
    p_upState3->addTransition(this, SIGNAL(sigMoveRight()), p_rightState3);

    p_downState1->addTransition(this, SIGNAL(sigMoveRight()), p_rightState1);
    p_downState2->addTransition(this, SIGNAL(sigMoveRight()), p_rightState2);
    p_downState3->addTransition(this, SIGNAL(sigMoveRight()), p_rightState3);

   /*************************收到向左滑动信号*********************绑定状态切换转换和动画效果***/
    QSignalTransition *leftTransition = p_leftState1->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState2);
    leftTransition->addAnimation(p_group);
    leftTransition = p_leftState2->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState3);
    leftTransition->addAnimation(p_group);
    leftTransition = p_leftState3->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState1);
    leftTransition->addAnimation(p_group);

    leftTransition = p_rightState1->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState2);
    leftTransition->addAnimation(p_group);
    leftTransition = p_rightState2->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState3);
    leftTransition->addAnimation(p_group);
    leftTransition = p_rightState3->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState1);
    leftTransition->addAnimation(p_group);

    p_upState1->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState1);
    p_upState2->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState2);
    p_upState3->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState3);

    p_downState1->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState1);
    p_downState2->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState2);
    p_downState3->addTransition(this, SIGNAL(sigMoveLeft()), p_leftState3);

    /*************************收到向上滑动信号*********************绑定状态切换转换和动画效果***/
    QSignalTransition *upTransition = p_upState1->addTransition(this, SIGNAL(sigMoveUp()), p_upState2);
    upTransition->addAnimation(p_group);
    upTransition = p_upState2->addTransition(this, SIGNAL(sigMoveUp()), p_upState3);
    upTransition->addAnimation(p_group);
    upTransition = p_upState3->addTransition(this, SIGNAL(sigMoveUp()), p_upState1);
    upTransition->addAnimation(p_group);

    upTransition = p_downState1->addTransition(this, SIGNAL(sigMoveUp()), p_upState2);
    upTransition->addAnimation(p_group);
    upTransition = p_downState2->addTransition(this, SIGNAL(sigMoveUp()), p_upState3);
    upTransition->addAnimation(p_group);
    upTransition = p_downState3->addTransition(this, SIGNAL(sigMoveUp()), p_upState1);
    upTransition->addAnimation(p_group);

    p_leftState1->addTransition(this, SIGNAL(sigMoveUp()), p_upState1);
    p_leftState2->addTransition(this, SIGNAL(sigMoveUp()), p_upState2);
    p_leftState3->addTransition(this, SIGNAL(sigMoveUp()), p_upState3);

    p_rightState1->addTransition(this, SIGNAL(sigMoveUp()), p_upState1);
    p_rightState2->addTransition(this, SIGNAL(sigMoveUp()), p_upState2);
    p_rightState3->addTransition(this, SIGNAL(sigMoveUp()), p_upState3);

    /*************************收到向下滑动信号*********************绑定状态切换转换和动画效果***/
    QSignalTransition *downTransition = p_downState1->addTransition(this, SIGNAL(sigMoveDown()), p_downState3);
    downTransition->addAnimation(p_group);
    downTransition = p_downState2->addTransition(this, SIGNAL(sigMoveDown()), p_downState1);
    downTransition->addAnimation(p_group);
    downTransition = p_downState3->addTransition(this, SIGNAL(sigMoveDown()), p_downState2);
    downTransition->addAnimation(p_group);

    downTransition = p_upState1->addTransition(this, SIGNAL(sigMoveDown()), p_downState3);
    downTransition->addAnimation(p_group);
    downTransition = p_upState2->addTransition(this, SIGNAL(sigMoveDown()), p_downState1);
    downTransition->addAnimation(p_group);
    downTransition = p_upState3->addTransition(this, SIGNAL(sigMoveDown()), p_downState2);
    downTransition->addAnimation(p_group);


    p_leftState1->addTransition(this, SIGNAL(sigMoveDown()), p_downState1);
    p_leftState2->addTransition(this, SIGNAL(sigMoveDown()), p_downState2);
    p_leftState3->addTransition(this, SIGNAL(sigMoveDown()), p_downState3);

    p_rightState1->addTransition(this, SIGNAL(sigMoveDown()), p_downState1);
    p_rightState2->addTransition(this, SIGNAL(sigMoveDown()), p_downState2);
    p_rightState3->addTransition(this, SIGNAL(sigMoveDown()), p_downState3);

    /**************************收到恢复初始状态信号*******************************************/
    p_leftState1->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_leftState2->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_leftState3->addTransition(this, SIGNAL(sigInitState()), p_leftState1);

    p_rightState1->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_rightState2->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_rightState3->addTransition(this, SIGNAL(sigInitState()), p_leftState1);

    p_upState1->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_upState2->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_upState3->addTransition(this, SIGNAL(sigInitState()), p_leftState1);

    p_downState1->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_downState2->addTransition(this, SIGNAL(sigInitState()), p_leftState1);
    p_downState3->addTransition(this, SIGNAL(sigInitState()), p_leftState1);

    /************************初始化状态机和场景并关联之***********************************/
    p_scene = new QGraphicsScene(this);
    p_scene->addWidget(p_frame1);
    p_scene->addWidget(p_frame2);
    p_scene->addWidget(p_frame3);
    p_scene->setSceneRect(DESKTOP_WIDTH,DESKTOP_HEIGHT, DESKTOP_WIDTH, DESKTOP_HEIGHT);
    setScene(p_scene);

    p_startState->setInitialState(p_leftState1);
    m_isXDirection = true;
    m_currentWidgetIndex = 1;         //这个值跟初始状态当前显示索引有关
    m_currentFrameIndexl = 1;
    p_stateMachine->addState(p_startState);
    p_stateMachine->setInitialState(p_startState);
    p_stateMachine->start();
    connect(p_frame1, SIGNAL(objectNameChanged(QString)), this, SLOT(slotSendCurrentWidgetPointer(QString)));
}

/*
 * 功能：
 * 	  添加需展示窗体。
 * 参数：
 * 	  int widgetIndex p_widgetBuf空闲索引号
 *    QWidget *pw  窗体指针
 * 返回值：
 * 	  int
 *    1 索引不正确，或者 位置已填
 *    0 成功
 */
int SlidingScreen::addWidgetItem(int widgetIndex, QWidget *pw)
{
    if (widgetIndex > 50 || widgetIndex < 0 || p_widgetBuf->at(widgetIndex) != nullptr)  //不允许覆盖
        return 1;    //该位置已满。
    p_widgetBuf->operator [](widgetIndex) = pw;
    p_indexBuf->append(widgetIndex);

    if (!m_enable)            //打开使能标志
        m_enable = true;

    return 0;
}

/*
 * 功能：
 * 	  移除需展示窗体。
 * 参数：
 * 	  int widgetIndex p_widgetBuf空闲索引号
 * 返回值：
 * 	  int
 *    1 索引不正确，或者 位置已空
 *    2 enable位false
 *    0 移除成功
 */
int SlidingScreen::removeWidgetItem(int widgetIndex)  //该函数不会释放传递进来的指针对象。
{
    if (!m_enable)
        return 2;
    if ((widgetIndex > 50 || widgetIndex < 0) || p_widgetBuf->at(widgetIndex) == nullptr)
        return 1;       //该位置已空
    p_indexBuf->remove(p_indexBuf->indexOf(widgetIndex));
    p_widgetBuf->operator [](widgetIndex) = nullptr;

    if (p_indexBuf->isEmpty())
        m_enable = false;


    return 0;
}

int SlidingScreen::removeAllWidget()
{
    if (p_widgetBuf->isEmpty() || p_indexBuf->isEmpty())
        return 0;
    p_indexBuf->clear();
    int i = p_widgetBuf->length()-1;
    while ( i>=0 )
    {
        p_widgetBuf->operator [](i) = nullptr;
        --i;
    }
    return 0;
}

SlidingScreen::~SlidingScreen()
{

    delete p_layout1;
    delete p_layout2;
    delete p_layout3;

    delete p_frame1;
    delete p_frame2;
    delete p_frame3;

    delete p_widgetBuf;
    delete p_indexBuf;

    delete p_leftState1;delete p_leftState2;delete p_leftState3;
    delete p_rightState1;delete p_rightState2;delete p_rightState3;
    delete p_upState1;delete p_upState2; delete p_upState3;
    delete p_downState1;delete p_downState2;delete p_downState3;

    delete p_frame1Animation;
    delete p_frame2Animation;
    delete p_frame3Animation;
    delete p_group;

    delete p_startState;
    delete p_stateMachine;
}

/*
 * 功能：
 * 	  满屏显示用户视角区域
 * 参数：
 * 返回值：
 */
void SlidingScreen::resizeEvent(QResizeEvent *event)
{
    if (!m_enable)
        return;
    fitInView(sceneRect(), Qt::IgnoreAspectRatio);
    QGraphicsView::resizeEvent(event);
}

/*
 * 功能：
 * 	  鼠标按下记录坐标
 * 参数：
 * 返回值：
 */
void SlidingScreen::mousePressEvent(QMouseEvent *event)
{
    if (!m_enable)
    {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    m_pressPos = event->pos();
    QGraphicsView::mousePressEvent(event);
}

/*
 * 功能：
 * 	  判断滑动距离滑动方向，并发射信号激活激活状态
 * 参数：
 * 返回值：
 */
void SlidingScreen::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_enable || !m_enableSliding || p_indexBuf->length() == 1)
    {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }

    m_releasePos = event->pos();
    if ((qAbs(m_releasePos.x() - m_pressPos.x()) < 100)&& m_isOneDirection == false) //means y轴上的移动
    {
        if ((m_releasePos.y() - m_pressPos.y())>20)
        {
            if (m_isXDirection == false)
            {
            updateFrame(false);
            emit sigMoveDown();
            }
            else if (m_isXDirection == true)//如果是x轴和y轴方向切换 则发两次信号 即做两次状态切换。
            {
                emit sigMoveDown();
                updateFrame(false);
                emit sigMoveDown();
            }
            m_isXDirection = false;
            m_enableSliding = false;
        }
        else if ((m_releasePos.y() - m_pressPos.y())< -20)
        {
            if (m_isXDirection == false)
            {
            updateFrame(true);
            emit sigMoveUp();
            }
            else if (m_isXDirection == true) //如果是x轴和y轴方向切换 则发两次信号 即做两次状态切换。
            {
                emit sigMoveUp();            //第一次信号调整方向至水平方向无动画效果
                updateFrame(true);
                emit sigMoveUp();            //第二次信号移动窗体
            }
            m_isXDirection = false;
            m_enableSliding = false;
        }
    }
    else //x轴上的移动
    {
        if ((m_releasePos.x() - m_pressPos.x())>20)
        {
            if (m_isXDirection == true)
            {
            updateFrame(false);
            emit sigMoveRight();
            }
            else if (m_isXDirection == false)//如果是x轴和y轴方向切换 则发两次信号 即做两次状态切换。
            {
                emit sigMoveRight();
                updateFrame(false);
                emit sigMoveRight();
            }
            m_isXDirection = true;
            m_enableSliding = false;
        }
        else if ((m_releasePos.x() - m_pressPos.x())< -20)
        {
            if (m_isXDirection == true)
            {
            updateFrame(true);
            emit sigMoveLeft();
            }
            else if (m_isXDirection == false)//如果是x轴和y轴方向切换 则发两次信号 即做两次状态切换。
            {
                emit sigMoveLeft();
                updateFrame(true);
                emit sigMoveLeft();
            }
            m_isXDirection = true;
            m_enableSliding = false;
        }
    }
      QGraphicsView::mouseReleaseEvent(event);
}

/*
 * 功能：
 * 	  当show事件发生时，重新设定三个frame，装载widget，重新show该页面设置才会生效
 * 参数：
 * 返回值：
 */
void SlidingScreen::showEvent(QShowEvent *event)
{
    initSlidingScreenFrame();
    QGraphicsView::showEvent(event);
}

/*
 * 功能：
 * 	  计算下一个状态下三个frame各自需要存放的窗体指针，并装载之。
 * 参数：
 *    bool indexAdd  指明当前p_indexBuf内元素索引变化方向（递增or递减)
 * 返回值：
 * 	  int
 *    0 成功
 */
int SlidingScreen::updateFrame(bool indexAdd)
{ 
    m_currentFrameIndexl = p_frame1->objectName().toInt();
    m_currentWidgetIndex = p_indexBuf->indexOf(m_layOut[m_currentFrameIndexl]->objectName().toInt());

    int newWidgetIndex = m_currentWidgetIndex;   //新的窗体的索引在p_indexBuf中的index号。
    int needUpdateFrameIndex = m_currentFrameIndexl;

    int step = 2;
    if (p_indexBuf->length() == 2)       //如果是2屏下则三屏动，show 2屏内容。
    {
        indexAdd = !indexAdd;
        step = 1;
    }

    if (indexAdd == true){  //indexAdd = true means 滑屏方向为 索引递增方向
        newWidgetIndex = (m_currentWidgetIndex+step) % p_indexBuf->length(); //后一位
        needUpdateFrameIndex = (m_currentFrameIndexl+2) % 3;
    }
    else if(indexAdd == false){ //indexAdd = false means 滑屏方向为 索引递减方向
        newWidgetIndex = (m_currentWidgetIndex+p_indexBuf->length()-step) % p_indexBuf->length(); // 前两位
        needUpdateFrameIndex = (m_currentFrameIndexl+1) % 3;
    }

    if (p_indexBuf->length() == 2)     //2屏模式下有两屏内容完全一样。
    {
        int otherFrameIndex = 3 - needUpdateFrameIndex - p_frame1->objectName().toInt();
        if (!m_layOut[otherFrameIndex]->objectName().isEmpty())
            m_layOut[otherFrameIndex]->removeWidget(m_layOut[otherFrameIndex]->currentWidget());
        m_layOut[otherFrameIndex]->addWidget(p_widgetBuf->at(p_indexBuf->at(newWidgetIndex)));
        m_layOut[otherFrameIndex]->setObjectName(QString::number(p_indexBuf->at(newWidgetIndex)));
    }
    m_layOut[needUpdateFrameIndex]->removeWidget(m_layOut[needUpdateFrameIndex]->currentWidget());
    m_layOut[needUpdateFrameIndex]->addWidget(p_widgetBuf->at(p_indexBuf->at(newWidgetIndex)));
    m_layOut[needUpdateFrameIndex]->setObjectName(QString::number(p_indexBuf->at(newWidgetIndex)));
    return 0;
}

/*
 * 功能：
 * 	  当p_indexBuf和p_widgetBuf被改动时，调用该函数重设frame.
 * 参数：
 * 返回值：
 */
void SlidingScreen::initSlidingScreenFrame()
{
    if (p_indexBuf->length() == 0)
        return;

    int i = 0;
    int index = 0;
    int len = p_indexBuf->length() > 3? 3: p_indexBuf->length();
    while(i < len)
    {
        if (0 == i)                             //如果是初始化frame0则放在最后一屏
            index = p_indexBuf->last();
        else
            index = p_indexBuf->at(i-1);
        if (1 == len)                           //如果是单屏模式，则将该屏放置于frame1
            i++;
        m_layOut[i]->removeWidget(m_layOut[i]->currentWidget());
        m_layOut[i]->addWidget(p_widgetBuf->at(index));
        m_layOut[i]->setObjectName(QString::number(index)); //layout的objectName记录着各自保存的widget在widgetBuf中的索引号，并在替换时更新
        ++i;
    }
    emit sigInitState(); //恢复状态机初始状态
}

/*
 * 功能：
 * 	  槽函数，控制m_enableSliding，该标志用来防止快速滑屏时导致屏幕抖动
 * 参数：
 * 返回值：
 */
void SlidingScreen::slotAnimationFinish()
{
    m_enableSliding = true;
}

/*
 * 功能：
 * 	  槽函数, send the pointer of current widget;
 * 参数： QString
 * 返回值： none
 */
void SlidingScreen::slotSendCurrentWidgetPointer(QString currentFrameIndex)
{
    switch (currentFrameIndex.toInt()) {
    case 0:
        emit sigCurrentIndex(p_widgetBuf->at(m_layOut[0]->objectName().toInt())); //objectName().toInt() == addWidgetItem(int widgetIndex, QWidget *pw)
        break;
    case 1:
        emit sigCurrentIndex(p_widgetBuf->at(m_layOut[1]->objectName().toInt()));
        break;
    case 2:
        emit sigCurrentIndex(p_widgetBuf->at(m_layOut[2]->objectName().toInt()));
        break;
    default:
        break;
    }
}
