#include "widget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVector>

#include "sinechartwidget.h"
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
    // 正弦曲线窗口
    m_pSineChartWidget = new SineChartWidget;

    bool frameState = Global::GetFrameState();

    m_pSineChartWidget->move(Global::GetSineChartPos());
    m_pSineChartWidget->resize(Global::GetSineChartSize());

    if(frameState)
    {
        m_pSineChartWidget->show();
    }
    else
    {
        m_pSineChartWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        m_pSineChartWidget->setAttribute(Qt::WA_TranslucentBackground);
        m_pSineChartWidget->setBackgroundTransparent();
        m_pSineChartWidget->show();
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
