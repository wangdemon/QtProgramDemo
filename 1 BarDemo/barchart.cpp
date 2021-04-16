#include "barchart.h"

#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>
#include <QDebug>

#include <cmath>

BarChart::BarChart(QWidget *parent)
    : QWidget(parent)
{
    m_iRadius = 300;
}

void BarChart::setData(QList<int> valueList, QList<QString> titleList)
{
    int valueSize = valueList.size();
    int titleSize = titleList.size();
    if(valueSize != titleSize)
        return;
    m_valueList = valueList;
    m_titleList = titleList;
}

void BarChart::paintEvent(QPaintEvent *event)
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

    // 画柱状图
    drawBar(painter);

    // 画文字
    drawText(painter);

    this->update();
}

void BarChart::drawBar(QPainter &painter)
{
    painter.save();

    QLinearGradient linearGradient(QPointF(0,0), QPointF(0, 200));
    linearGradient.setColorAt(0, "#EB7B30");
    linearGradient.setColorAt(1, "#F03059");
    painter.setBrush(linearGradient);
    painter.setPen(QColor("#EB7B30"));

    int count = m_valueList.size();
    int maxValue = getMaxOrMin(m_valueList, true);
    int minValue = getMaxOrMin(m_valueList, false);
    int baseSpan = m_iRadius * 2 / (count * 2 + 1);

    for(int i = 0; i < count; i++)
    {
        int x, y, width, height;
        x = (2 * i + 1) * baseSpan;
        width = baseSpan / 2;
        height = (m_valueList.at(i) - minValue) / float(maxValue - minValue) * 130 + 50;
        y = 2 * m_iRadius - 100;
        painter.drawRect(x, y, width, -height);
    }
    painter.restore();
}

void BarChart::drawText(QPainter &painter)
{
    painter.save();
    QFont font;
    font.setPointSize(15);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QColor("#C5D9FA"));

    int count = m_valueList.size();
    int maxValue = getMaxOrMin(m_valueList, true);
    int minValue = getMaxOrMin(m_valueList, false);
    int baseSpan = m_iRadius * 2 / (count * 2 + 1);

    for(int i = 0; i < count; i++)
    {
        int x, y, width, height;
        x = (2 * i + 1) * baseSpan;
        width = baseSpan / 2;
        height = (m_valueList.at(i) - minValue) / float(maxValue - minValue) * 130 + 50;
        y = 2 * m_iRadius - height - 100;
        QRect topRect(x - 5, y, width + 10, -30);
        painter.drawText(topRect, Qt::AlignCenter, QString("%1件").arg(m_valueList.at(i)));

        x = x - 15;
        y = y + height + 5;
        width = width * 2;
        QRect bottomRect(x - 18, y, width + 36, 30);
        painter.drawText(bottomRect, Qt::AlignCenter, m_titleList.at(i));
    }
    painter.restore();
}


int BarChart::getMaxOrMin(QList<int> list, bool isMax)
{
    int temp = list.at(0);
    int count = list.size();
    for(int i = 1; i < count; i++)
    {
        if(isMax)
        {
            if(temp < list.at(i))
            {
                temp = list.at(i);
            }
        }
        else
        {
            if(temp > list.at(i))
            {
                temp = list.at(i);
            }
        }
    }
    return temp;
}
