#ifndef BARCHART_H
#define BARCHART_H

#include <QWidget>
#include <QList>

class BarChart : public QWidget
{
    Q_OBJECT
public:
    explicit BarChart(QWidget* parent = nullptr);

    void setData(QList<int> valueList, QList<QString> titleList);

protected:
    void paintEvent(QPaintEvent *event);

    void drawBar(QPainter& painter);
    void drawText(QPainter& painter);


private:
    int getMaxOrMin(QList<int> list, bool isMax);

private:
    // 窗口半径
    int m_iRadius;

    // 柱状图的值
    QList<int> m_valueList;

    // 柱状图的标题
    QList<QString> m_titleList;

};

#endif // BARCHART_H
