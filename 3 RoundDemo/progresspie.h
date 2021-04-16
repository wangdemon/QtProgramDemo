#ifndef PROGRESSPIE_H
#define PROGRESSPIE_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class QPaintEvent;

class ProgressPie : public QWidget
{
    Q_OBJECT

public:
    ProgressPie(QWidget *parent = nullptr);
    ~ProgressPie();

    void setValue(int value);
    int getValue();

protected:
    void paintEvent(QPaintEvent *event);

private:
    /**
    * @brief 画文本
    **/
    void drawText(QPainter& painter);

    /**
    * @brief 画背景
    **/
    void drawBackground(QPainter& painter);

    /**
    * @brief 画外环
    **/
    void drawRing(QPainter& painter);

    /**
    * @brief 画圆形进度条
    **/
    void drawProgress(QPainter& painter);

    /**
    * @brief 百分比的值转为进度的值
    **/
    int toSpanValue();

private:
    // 窗口半径
    int m_iRadius;

    // 环
    QPen m_ringPen;
    QBrush m_ringBrush;

    // 进度条
    QPen m_progressPen;
    QBrush m_progressBrush;

    // 文字
    QPen m_textPen;

    // 百分比显示
    int m_iValue;

};
#endif // PROGRESSPIE_H
