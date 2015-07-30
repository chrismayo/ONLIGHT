#include "sysconfigoptionwidget.h"

SysConfigOptionWidget::SysConfigOptionWidget(QPushButton *parent, int index) :
    QPushButton(parent), m_targetIndex(index)
{
    setFixedHeight(QDesktopWidget().height() * 0.1);
    setFixedWidth(QDesktopWidget().width() * 0.75);
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();
}

SysConfigOptionWidget::~SysConfigOptionWidget()
{
    release();
}

int SysConfigOptionWidget::setTargetWidgetIndex(int index)
{
    if (index > 4050 || index < -4050)
        return 1;

    m_targetIndex = index;
    return 0;
}

int SysConfigOptionWidget::setTitle(QString title)
{
    m_labelTitle.setText(title);
    return 0;
}

int SysConfigOptionWidget::setContent(QString content)
{
    m_labelContent.setText(content);
    return 0;
}

void SysConfigOptionWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit(sigTargetWidgetIndex(m_targetIndex, m_labelContent.text()));
    QPushButton::mouseReleaseEvent(e);
}

void SysConfigOptionWidget::initialize()
{
    p_hLayOut = new QHBoxLayout();
}

void SysConfigOptionWidget::release()
{
    delete p_hLayOut;
}

void SysConfigOptionWidget::setUserDefineStyle()
{
    p_hLayOut->addWidget(&m_labelModified);
    p_hLayOut->addWidget(&m_labelTitle);
    p_hLayOut->addWidget(&m_labelContent);

    setLayout(p_hLayOut);
}

void SysConfigOptionWidget::setUserDefineContent()
{

}

void SysConfigOptionWidget::setWinLayout()
{

}

void SysConfigOptionWidget::sigAndSlotConnect()
{

}
