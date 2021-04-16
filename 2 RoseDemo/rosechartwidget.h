#ifndef ROSECHARTWIDGET_H
#define ROSECHARTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <vector>

class QHBoxLayout;
class RosePie;

class RoseChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoseChartWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void moveEvent(QMoveEvent *event);

private slots:
    void slotUpdateValue();

private:
    std::vector<int> generateDiffNumber(int min,int max,int num);

private:
    QHBoxLayout* m_pMainHLayout;
    RosePie* m_pRosePie;
    QTimer m_timer;

    bool m_bMove;
    QPoint m_spanPoint;
};

#endif // ROSECHARTWIDGET_H
