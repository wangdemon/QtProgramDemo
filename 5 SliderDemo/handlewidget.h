#ifndef HANDLEWIDGET_H
#define HANDLEWIDGET_H

#include <QWidget>
#include <QColor>

class QPaintEvent;

class HandleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HandleWidget(QWidget* parent = nullptr);

    bool containPos(QPoint pos);

protected:
    void paintEvent(QPaintEvent *event);

private:
    // 初始化函数
    // 初始化所有的私有变量
    void initialize();

    // 创建信号和槽函数连接
    void createConnectios();

    // 画三角形
    void drawTriangle(QPainter& painter);
    // 画矩形
    void drawRectangle(QPainter& painter);
    // 画矩形背景
    void drawRectangleBg(QPainter& painter);

private:
    // 三角形颜色
    QColor m_triangleColor;
    // 矩形颜色
    QColor m_rectangleColor;
    // 矩形背景颜色
    QColor m_rectangleBgColor;

    // 窗口半径
    int m_iRadius;
    int m_iEdgeLength;
};

#endif // HANDLEWIDGET_H
