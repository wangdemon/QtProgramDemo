#ifndef SINECURVE_H
#define SINECURVE_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QTimer>

#include <QChartView>//显示图表
#include <QLineSeries>//线系列
#include <QSplineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class SineCurve : public QWidget
{
    Q_OBJECT

public:
    explicit SineCurve(QWidget *parent = 0);
    ~SineCurve();

    void setBackgroundTransparent();

private slots:
    void slotRealTimeData();

private:
    QTimer m_timer;
    QStringList m_titles;
    QChartView* m_pChartView;
    QChart* m_pChart;
    QSplineSeries* m_pSeries1;
    QSplineSeries* m_pSeries2;
    QSplineSeries* m_pSeries3;
    QValueAxis m_axis;

    qreal m_step;
    qreal m_x1;
    qreal m_y1;

    qreal m_x2;
    qreal m_y2;

    qreal m_x3;
    qreal m_y3;
};


#endif // SINECURVE_H
