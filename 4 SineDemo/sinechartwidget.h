#ifndef SINECHARTWIDGET_H
#define SINECHARTWIDGET_H

#include <QWidget>

class SineCurve;

class QHBoxLayout;

class SineChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SineChartWidget(QWidget* parent = nullptr);

    void setBackgroundTransparent();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void moveEvent(QMoveEvent *event);

private:
    QHBoxLayout* m_pMainHLayout;
    SineCurve* m_pSineCurve;
    bool m_bMove;
    QPoint m_spanPoint;
};

#endif // SINECHARTWIDGET_H
