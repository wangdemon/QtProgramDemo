#include "rosepie.h"

#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QMouseEvent>

RosePie::RosePie(QWidget *parent)
    : QWidget(parent)
{
    m_iRadius = 20;
    m_iWindowRadius = 100;
}

void RosePie::setData(QMap<int, int> valueMap, QMap<int, QString> titleMap,
                      QMap<int, QColor> colorMap)
{
    int count1 = valueMap.size();
    int count2 = titleMap.size();
    int count3 = colorMap.size();
    if(count1 != count2 || count2 != count3 || count1 != count3)
        return;

    m_valueMap = valueMap;
    m_titleMap = titleMap;
    m_colorMap = colorMap;
    m_sortValueList = valueMap.values();
    qSort(m_sortValueList.begin(), m_sortValueList.end());
    this->update();
}

void RosePie::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    m_iSide = qMin(width(), height());
    int x = (width() - m_iSide) / 2;
    int y = (height() - m_iSide) / 2;

    // 设置ViewPort
    painter.setViewport(QRect(x, y, m_iSide, m_iSide));
    // 设置窗口 逻辑坐标
    painter.setWindow(QRect(0, 0, 2 * m_iWindowRadius, 2 * m_iWindowRadius));
    painter.setRenderHint(QPainter::Antialiasing);

    // 画玫瑰饼图
    drawRose(painter);
}

void RosePie::drawRose(QPainter &painter)
{   
    // 测试例子
    //    QPen pen;
    //    painter.save();
    //    pen.setColor(Qt::red);
    //    pen.setWidth(10);
    //    painter.setPen(pen);
    //    int startAngle = 90 * 16;
    //    int spanAngle =  -360 * 16;
    //    QRectF rectangle(100 - 30, 100 - 30,
    //                     2 * 30, 2 * 30);
    //    painter.drawArc(rectangle, startAngle, spanAngle);
    //    painter.restore();

    //    painter.save();
    //    pen.setColor(Qt::green);
    //    pen.setWidth(20);
    //    pen.setStyle(Qt::SolidLine);
    //    pen.setCapStyle(Qt::FlatCap);
    //    painter.setPen(pen);
    //    startAngle = 60 * 16;
    //    spanAngle =  -180 * 16;
    //    QRectF rectangle1(100 - 35, 100 - 35,
    //                     2 * 35, 2 * 35);
    //    painter.drawArc(rectangle1, startAngle, spanAngle);
    //    painter.restore();

    QMap<int, QColor> colorMap = m_colorMap;
    QMap<int, QString> titleMap = m_titleMap;
    QMap<int, int> valueMap = m_valueMap;
    int totalValue = 0;
    int radiusSpan = 80 / (m_sortValueList.size() * 4);
    for (int i = 0; i < m_sortValueList.size(); i++)
    {
        totalValue += m_sortValueList.at(i);
    }

    int earlierTotalValue = 0;
    for (int i = 0; i < m_sortValueList.size(); i++)
    {
        int value = m_sortValueList.at(i);

        earlierTotalValue += value;

        int index = getIndexFromaValue(value);
        if(!m_valueMap.contains(index))
            return;

        QColor color = colorMap.value(index);
        QString title = titleMap.value(index);
        colorMap.remove(index);
        titleMap.remove(index);
        valueMap.remove(index);

        painter.save();
        QPen pen;
        pen.setColor(color);
        pen.setWidth(radiusSpan * (2 * i + 2));
        pen.setCapStyle(Qt::FlatCap);
        painter.setPen(pen);
        int startAngle = 0;
        int spanAngle = 0;
        if(i == 0)
        {
            startAngle = 90 * 16;
        }
        else
        {
            int earlierTotalAngle = 360 * (earlierTotalValue -value) / totalValue;
            startAngle = (90 - earlierTotalAngle) * 16;
        }
        spanAngle =  -(360 * value / totalValue) * 16;
        QRectF rectangle(m_iWindowRadius - (m_iRadius + radiusSpan * (i + 1)),
                         m_iWindowRadius - (m_iRadius + radiusSpan * (i + 1)),
                         2 * (m_iRadius + radiusSpan * (i + 1)),
                         2 * (m_iRadius + radiusSpan * (i + 1)));
        painter.drawArc(rectangle, startAngle, spanAngle);
        painter.restore();

        float textAngle = 360 * (earlierTotalValue - value + float(value / 2)) / totalValue;
        drawText(painter, textAngle, m_iRadius + radiusSpan * (2 * i + 2), title, color);
    }
}

void RosePie::drawText(QPainter &painter, float angle, float radius, const QString& title, QColor color)
{
    // 位置，分别在直角坐标系上的四个象限上，其值分别为1,2,3,4
    // 他们代表1,2,3,4象限
    int iPosState = 0;

    painter.save();
    painter.setPen(color);
    QPointF p1, p2, p3;
    if(angle <= 90)
    {
        p1.setX(100 + radius * qSin(qDegreesToRadians(angle)));
        p1.setY(100 - radius * qCos(qDegreesToRadians(angle)));

        p2.setX(100 + (radius + 25) * qSin(qDegreesToRadians(angle)));
        p2.setY(100 - (radius + 25) * qCos(qDegreesToRadians(angle)));

        p3.setX(100 + (radius + 25) * qSin(qDegreesToRadians(angle)) + 35);
        p3.setY(100 - (radius + 25) * qCos(qDegreesToRadians(angle)));

        iPosState = 1;
    }
    else if(angle > 90 && angle <= 180)
    {
        angle = angle - 90;
        p1.setX(100 + radius * qCos(qDegreesToRadians(angle)));
        p1.setY(100 + radius * qSin(qDegreesToRadians(angle)));

        p2.setX(100 + (radius + 25) * qCos(qDegreesToRadians(angle)));
        p2.setY(100 + (radius + 25) * qSin(qDegreesToRadians(angle)));

        p3.setX(100 + (radius + 25) * qCos(qDegreesToRadians(angle)) + 35);
        p3.setY(100 + (radius + 25) * qSin(qDegreesToRadians(angle)));
        iPosState = 2;
    }
    else if(angle > 180 && angle <= 270)
    {
        angle = angle - 180;
        p1.setX(100 - radius * qSin(qDegreesToRadians(angle)));
        p1.setY(100 + radius * qCos(qDegreesToRadians(angle)));

        p2.setX(100 - (radius + 25) * qSin(qDegreesToRadians(angle)));
        p2.setY(100 + (radius + 25) * qCos(qDegreesToRadians(angle)));

        p3.setX(100 - (radius + 25) * qSin(qDegreesToRadians(angle)) - 35);
        p3.setY(100 + (radius + 25) * qCos(qDegreesToRadians(angle)));
        iPosState = 3;
    }
    else if(angle > 270 && angle <= 360)
    {
        angle = angle - 270;
        p1.setX(100 - radius * qCos(qDegreesToRadians(angle)));
        p1.setY(100 - radius * qSin(qDegreesToRadians(angle)));

        p2.setX(100 - (radius + 25) * qCos(qDegreesToRadians(angle)));
        p2.setY(100 - (radius + 25) * qSin(qDegreesToRadians(angle)));

        p3.setX(100 - (radius + 25) * qCos(qDegreesToRadians(angle)) - 35);
        p3.setY(100 - (radius + 25) * qSin(qDegreesToRadians(angle)));
        iPosState = 4;
    }

    QFont font;
    font.setBold(true);
    //font.setWeight(15);
    font.setFamily("Microsoft YaHei");
    //font.setPointSize(15);
    font.setPixelSize(15);
    painter.setFont(font);

    painter.drawLine(p1, p2);
    painter.drawLine(p2, p3);
    //painter.drawText(p3, title);

//    QFont font;
//     font.setPointSize(18);
//     painter.setFont(font);
//    QFontMetrics fm = painter.fontMetrics();
//    QString list[] = {"A","B","C","D","E"};
//    for(int i = 0 ; i < 5; i++)
//    {
//        int width = fm.width(list[i]);
//        int height = fm.ascent()+fm.descent();

//        QPair<int,int> pos(mDatas[i]);
//        QRectF rect(pos.first - width / 2, pos.second - height / 2, width, height);
//        painter.drawText(rect, list[i]);
//    }
    //QFont font("times", 24);
    //    QFontMetrics fm(font);
    //    int pixelsWide = fm.horizontalAdvance(title);
    //    int pixelsHigh = fm.height();
    //    qDebug() << "h1:" << pixelsHigh << ", h2: " << m_iSide;

    QStringList titleList = title.split("%");

    if(titleList.size() == 2)
    {
        QString title1, title2;
        title1 = titleList.at(0) + "%";
        title2 = titleList.at(1);

        QPoint p31, p32;
        if(iPosState == 1 || iPosState == 2)
        {
            p31.setX(p3.x());
            p31.setY(p3.y() - 20);
            p32.setX(p3.x());
            p32.setY(p3.y());
        }
        else
        {
            p31.setX(p3.x() - 30);
            p31.setY(p3.y() - 20);
            p32.setX(p3.x() - 30);
            p32.setY(p3.y());
        }

        painter.drawText(QRect(p31, QSize(60, 20)), title1);
        painter.drawText(QRect(p32, QSize(60, 20)), title2);
    }
    else
    {
        painter.drawText(p3, title);
    }
    painter.restore();
}



int RosePie::getIndexFromaValue(int value)
{
    int index = -1;

    QMap<int, int>::iterator it = m_valueMap.begin();
    for(; it != m_valueMap.end(); it++)
    {
        if(value == it.value())
            return it.key();
    }
    return index;
}

int RosePie::leftTotalFromList(int index, QList<int> list)
{
    int size = list.size();
    int total = -1;
    if(index < 0)
        return total;

    for(int i = 0; i < size; i++)
    {
        if(i <= index)
        {
            total += list.at(i);
        }
    }

}

