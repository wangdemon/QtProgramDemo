#include "widget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVector>

#include "roundprogresswidget.h"
#include "global.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initialzie();
    createConnections();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_bMove = true;
    m_spanPoint = event->globalPos() - this->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        this->move(event->globalPos() - m_spanPoint);
    }

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void Widget::initialzie()
{
    m_pMainGLayout = new QGridLayout;

    // 圆形进度条
    m_pRoundWidget = new RoundProgressWidget;

    bool frameState = Global::GetFrameState();

    m_pRoundWidget->move(Global::GetRoundProgressPos());
    m_pRoundWidget->resize(Global::GetRountProgressSize());


    if(frameState)
    {
        m_pRoundWidget->show();
    }
    else
    {
        m_pRoundWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        m_pRoundWidget->setAttribute(Qt::WA_TranslucentBackground);
        m_pRoundWidget->show();
    }

    this->setLayout(m_pMainGLayout);
    this->resize(700, 400);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background:#4461EA;");

    m_bMove = false;
}

void Widget::createConnections()
{
}
