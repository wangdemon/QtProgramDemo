#include "widget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVector>

#include "rosechartwidget.h"
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

    // 玫瑰饼状图
    m_pRoseChartWidget = new RoseChartWidget;

    bool frameState = Global::GetFrameState();

    m_pRoseChartWidget->move(Global::GetRoseChartPos());
    m_pRoseChartWidget->resize(Global::GetRoseChartSize());

    if(frameState)
    {
        m_pRoseChartWidget->show();
    }
    else
    {
        m_pRoseChartWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        m_pRoseChartWidget->setAttribute(Qt::WA_TranslucentBackground);
        m_pRoseChartWidget->show();
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
