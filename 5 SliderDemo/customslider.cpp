#include "customslider.h"

#include "handlewidget.h"

#include <QMouseEvent>
#include <QRect>
#include <QPainter>
#include <QDebug>

CustomSlider::CustomSlider(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    createConnections();
}

void CustomSlider::setRange(int min, int max)
{
    m_iMin = min;
    m_iMax = max;
}

void CustomSlider::showDial(bool state)
{
    m_bShowDial = state;
    this->update();
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    QPoint pos1 = event->pos();
    QPoint pos2 = m_pHandleWidget->mapFromParent(pos1);
    bool state = m_pHandleWidget->containPos(pos2);
    if(state)
    {
        m_bMove = true;
    }
    else
    {
        m_bMove = false;
    }
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        QPoint pos = event->pos();
        int mouseX = pos.x();
        if(mouseX >= 0 && mouseX <= this->width())
        {
            m_iMouseX = mouseX;
            updatePosition();
            this->update();
        }
    }
}

void CustomSlider::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updatePosition();
}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

//    int side = qMin(width(), height());
//    int x = (width() - side) / 2;
//    int y = (height() - side) / 2;
    // 设置ViewPort
//    painter.setViewport(QRect(x, y, side, side));
    // 设置窗口 逻辑坐标
//    painter.setWindow(QRect(0, 0, 2 * m_iRadius, 2 * m_iRadius));
    painter.setRenderHint(QPainter::Antialiasing);

    drawDial(painter);

    this->update();
}

void CustomSlider::wheelEvent(QWheelEvent *event)
{
//    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    int delta = numDegrees.y();
    if(delta > 0)
    {
        if(m_iMouseX >= 0 && m_iMouseX <= this->width())
            m_iMouseX += m_iMouseX + 1;
        else if(m_iMouseX >= this->width())
            m_iMouseX = this->width();
        else if(m_iMouseX <= 0)
            m_iMouseX = 0;
    }
    else
    {
        if(m_iMouseX >= 0 && m_iMouseX <= this->width())
            m_iMouseX -= m_iMouseX + 1;
        else if(m_iMouseX >= this->width())
            m_iMouseX = this->width();
        else if(m_iMouseX <= 0)
            m_iMouseX = 0;

    }
    this->updatePosition();
}

void CustomSlider::initialize()
{
    m_iMin = 0;
    m_iMax = 100;
    m_pHandleWidget = new HandleWidget(this);
    m_pHandleWidget->setFixedSize(100, 50);
    m_bShowDial = true;
    m_iRadius = 300;
    m_iEdgeLength = 200;
    m_dialColor = "#BC1CEA";
    m_bMove = false;

    m_iX = 50;
    m_iMouseX = this->width() / 2;
    updatePosition();
}

void CustomSlider::createConnections()
{

}

void CustomSlider::updatePosition()
{
    QRect rect = this->geometry();
    // int width = rect.width();
    int height = rect.height();
    int width1 = m_pHandleWidget->width();
    int height1 = m_pHandleWidget->height();

    int y = height / 2 - height1 / 2;
    m_pHandleWidget->move(m_iMouseX - width1 / 2, y);
}

void CustomSlider::drawDial(QPainter &painter)
{
    painter.save();

    // painter.setBrush(m_dialColor);
    painter.setPen(m_dialColor);

    painter.drawRect(0, 0, this->width(), this->height());

    painter.restore();
}
