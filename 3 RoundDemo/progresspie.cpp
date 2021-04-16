#include "progresspie.h"

#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>

ProgressPie::ProgressPie(QWidget *parent)
    : QWidget(parent)
{
    m_iRadius = 100;
    m_ringPen.setColor("#F8E481");
    m_ringPen.setWidth(7);

    m_progressPen.setColor("#F8E481");
    m_progressPen.setWidth(14);
    m_progressPen.setCapStyle(Qt::RoundCap);

    m_textPen.setColor("#F8E481");
    m_textPen.setWidth(7);

    m_iValue = 60;
    setValue(m_iValue);
}

ProgressPie::~ProgressPie()
{
}

void ProgressPie::setValue(int value)
{
    m_iValue = value;
    if(m_iValue <= 45)
    {
        m_ringPen.setColor("#F8E481");
        m_ringPen.setWidth(7);

        m_progressPen.setColor("#F8E481");
        m_progressPen.setWidth(14);
        m_progressPen.setCapStyle(Qt::RoundCap);

        m_textPen.setColor("#F8E481");
        m_textPen.setWidth(7);
    }
    else if(m_iValue <= 69)
    {
        m_ringPen.setColor("#CFFFFF");
        m_ringPen.setWidth(7);

        m_progressPen.setColor("#CFFFFF");
        m_progressPen.setWidth(14);
        m_progressPen.setCapStyle(Qt::RoundCap);

        m_textPen.setColor("#CFFFFF");
        m_textPen.setWidth(7);
    }
    else if(m_iValue)
    {
        m_ringPen.setColor("#F4AAF7");
        m_ringPen.setWidth(7);

        m_progressPen.setColor("#F4AAF7");
        m_progressPen.setWidth(14);
        m_progressPen.setCapStyle(Qt::RoundCap);

        m_textPen.setColor("#F4AAF7");
        m_textPen.setWidth(7);
    }
    this->update();
}

int ProgressPie::getValue()
{
    return m_iValue;
}

void ProgressPie::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int side = qMin(width(), height());
    int x = (width() - side) / 2;
    int y = (height() - side) / 2;

    // 设置ViewPort
    painter.setViewport(QRect(x, y, side, side));
    // 设置窗口 逻辑坐标
    painter.setWindow(QRect(-m_iRadius, -m_iRadius,
                            2 * m_iRadius, 2 * m_iRadius));
    painter.setRenderHint(QPainter::Antialiasing);

    // 画背景
    // drawBackground(painter);

    // 画文字
    drawText(painter);

    // 画圆环
    drawRing(painter);

    // 画圆形进度条
    drawProgress(painter);

}

void ProgressPie::drawText(QPainter &painter)
{
    painter.save();
    QFont font;
    font.setPointSize(30);
    font.setFamily("Segoe UI");
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    painter.setFont(font);
    QRect textRect(-50, -50, 100, 100);
    painter.setPen(m_textPen);
    painter.drawText(textRect, Qt::AlignCenter, QString::number(m_iValue) + "%");
    painter.restore();
}

void ProgressPie::drawBackground(QPainter &painter)
{
    painter.save();
    QLinearGradient linearGradient(QPointF(0,0), QPointF(0, 100));
    linearGradient.setColorAt(0, "#18144F");
    linearGradient.setColorAt(1, "#1B195B");
    //linearGradient.setSpread(QGradient::RepeatSpread);
    painter.setBrush(linearGradient);
    painter.drawRect(QRect(-m_iRadius, -m_iRadius,
                           2 * m_iRadius, 2 * m_iRadius));
    painter.restore();
}

void ProgressPie::drawRing(QPainter &painter)
{
    painter.save();
    painter.setPen(m_ringPen);
    QRectF rectangle(-80, -80, 160,  160);
    painter.drawEllipse(rectangle);
    painter.restore();
}

void ProgressPie::drawProgress(QPainter &painter)
{
    painter.save();
    painter.setPen(m_progressPen);
    QRectF progressRectangle(-80, -80, 160,  160);
    // int startAngle = 10 * 16;
    int startAngle = 90 * 16;
    int spanAngle =  toSpanValue() * 16;
    painter.drawArc(progressRectangle, startAngle, spanAngle);
    painter.restore();
}

int ProgressPie::toSpanValue()
{
    int middleValue = m_iValue * 3.6;
    return (- middleValue);
}

