#include "sinechartwidget.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSize>
#include <QPoint>
#include <QMoveEvent>
#include <QResizeEvent>
#include "global.h"
#include "sinecurve.h"

SineChartWidget::SineChartWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pMainHLayout = new QHBoxLayout;

    m_pSineCurve = new SineCurve;
    m_pMainHLayout->addWidget(m_pSineCurve);

    this->setLayout(m_pMainHLayout);
}

void SineChartWidget::setBackgroundTransparent()
{
    setAttribute(Qt::WA_TranslucentBackground);
    m_pSineCurve->setBackgroundTransparent();
}

void SineChartWidget::mousePressEvent(QMouseEvent *event)
{
    m_bMove = true;
    m_spanPoint = event->globalPos() - this->pos();
}

void SineChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        this->move(event->globalPos() - m_spanPoint);
    }

}

void SineChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void SineChartWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetSineChartSize(this->size());
}

void SineChartWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetSineChartPos(this->pos());
}
