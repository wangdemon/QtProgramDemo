#ifndef ROSEPIE_H
#define ROSEPIE_H

#include <QWidget>
#include <QMap>
#include <QColor>

class QPaintEvent;

class RosePie : public QWidget
{
    Q_OBJECT
public:
    explicit RosePie(QWidget* parent = nullptr);

    void setData(QMap<int, int> valueMap,
                 QMap<int, QString> titleMap, QMap<int, QColor> colorMap);

protected:
    void paintEvent(QPaintEvent *event);

    /**
    * @brief 画玫瑰饼图
    **/
    void drawRose(QPainter& painter);

    /**
    * @brief 画说明文本
    **/
    void drawText(QPainter& painter, float angle, float radius, const QString& title, QColor color = QColor("#BDC8F5"));




private:
    int getIndexFromaValue(int value);
    int leftTotalFromList(int index, QList<int> list);

private:
    int m_iWindowRadius;
    int m_iRadius;
    // 玫瑰图颜色
    QMap<int, QColor> m_colorMap;
    // 玫瑰图各个数据的标题
    QMap<int, QString> m_titleMap;
    // 玫瑰图各个数据的值
    QMap<int, int> m_valueMap;

    // 各个数据值从小到大排序
    QList<int> m_sortValueList;

    // 视口宽度
    int m_iSide;
};

#endif // ROSEPIE_H
