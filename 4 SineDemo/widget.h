#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPoint>

class SineChartWidget;

class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QMouseEvent;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void initialzie();
    void createConnections();

private:
    QGridLayout* m_pMainGLayout;

    SineChartWidget* m_pSineChartWidget;

    bool m_bMove;
    QPoint m_spanPoint;
};

#endif // WIDGET_H
