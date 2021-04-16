#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H

#include <QWidget>
#include <QTimer>
class BarChart;
class QHBoxLayout;
class QMouseEvent;
class QResizeEvent;
class QMoveEvent;

class BarChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BarChartWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void moveEvent(QMoveEvent *event);

private slots:
    void slotUpdate();
    std::vector<int> generateDiffNumber(int min,int max,int num);

private:
    QHBoxLayout* m_pMainHLayout;
    BarChart* m_pBarChart;
    QTimer m_timer;

    bool m_bMove;
    QPoint m_spanPoint;
};

#endif // BARCHARTWIDGET_H
