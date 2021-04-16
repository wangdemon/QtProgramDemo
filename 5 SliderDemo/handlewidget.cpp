#include "handlewidget.h"

#include <QPainter>
#include <QDebug>

HandleWidget::HandleWidget(QWidget *parent)
    : QWidget(parent)
{
    initialize();
}

bool HandleWidget::containPos(QPoint pos)
{
//    QRect rect = this->geometry();
    QRect rect(0, 0, this->width(), this->height());
//    qDebug() << "rect:" << rect;
    if(rect.contains(pos))
        return true;
    else
        return false;
}

void HandleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int side = qMin(width(), height());
    int x = (width() - side) / 2;
    int y = (height() - side) / 2;

    // 设置ViewPort
    painter.setViewport(QRect(x, y, side, side));
    // 设置窗口 逻辑坐标
    painter.setWindow(QRect(0, 0, 2 * m_iRadius, 2 * m_iRadius));
    painter.setRenderHint(QPainter::Antialiasing);

    drawRectangleBg(painter);
    drawTriangle(painter);
    drawRectangle(painter);

    this->update();
}

void HandleWidget::initialize()
{
    m_triangleColor = "#EA1C64";
    m_rectangleColor = "#1E39E5";
    m_rectangleBgColor = "#17D5E3";
    m_iEdgeLength = 100;
    m_iRadius = 300;
}

void HandleWidget::createConnectios()
{

}

void HandleWidget::drawTriangle(QPainter& painter)
{
    painter.save();

    painter.setBrush(m_triangleColor);
    painter.setPen(m_triangleColor);

    int x1 = m_iRadius - m_iEdgeLength / 2;
    int y1 = 2 * m_iRadius - m_iEdgeLength;

    int x2 = m_iRadius + m_iEdgeLength / 2;
    int y2 = 2 * m_iRadius - m_iEdgeLength;

    int x3 = m_iRadius;
    int y3 = 2 * m_iRadius - m_iEdgeLength * 2;

    QPoint points[4] = {
        QPoint(x1, y1),
        QPoint(x2, y2),
        QPoint(x3, y3),
    };

    painter.drawPolygon(points, 3);

    painter.restore();
}

void HandleWidget::drawRectangle(QPainter& painter)
{
    painter.save();

    painter.setBrush(m_rectangleColor);
    painter.setPen(m_rectangleColor);

    int x = m_iRadius - m_iEdgeLength / 2;
    int y = 2 * m_iRadius - m_iEdgeLength;
    painter.drawRect(x, y, m_iEdgeLength, m_iEdgeLength);

    painter.restore();
}

void HandleWidget::drawRectangleBg(QPainter& painter)
{
    painter.save();

    painter.setBrush(m_rectangleBgColor);
    painter.setPen(m_rectangleBgColor);

    int x = 0;
    int y = 2 * m_iRadius - m_iEdgeLength;
    painter.drawRect(x, y, 2 * m_iRadius, m_iEdgeLength);
//    painter.drawRect(0, 0, 2 * m_iRadius, 2 * m_iRadius);
    painter.restore();
}
