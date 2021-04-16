#include "sinecurve.h"

#include <QTime>
#include <QDebug>
#include <qmath.h>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QRandomGenerator>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSize>
#include <QPoint>
#include <QMoveEvent>
#include <QResizeEvent>
#include "global.h"

SineCurve::SineCurve(QWidget *parent)
    : QWidget(parent)
{
    // setWindowTitle("动态正弦波形图");
    m_pChart = new QChart;
    // m_pChart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
    // m_pChart->setTitle("动态正弦波形图");//设置标题
    m_pChart->setTitleFont(QFont("Micsofot YaHei",10));
    m_pChart->legend()->hide();

    m_x1 = 0;
    m_y1 = 0;
    m_x2 = 0;
    m_y2 = 0;
    m_x3 = 0;
    m_y3 = 0;

    m_pSeries1 = new QSplineSeries;
    m_pSeries2 = new QSplineSeries;
    m_pSeries3 = new QSplineSeries;

    QPen pen1(Qt::green);
    pen1.setWidth(2);

    QPen pen2(Qt::red);
    pen2.setWidth(2);

    QPen pen3(Qt::blue);
    pen3.setWidth(2);

    m_pSeries1->setPen(pen1);
    m_pSeries2->setPen(pen2);
    m_pSeries3->setPen(pen3);

    m_pSeries1->append(m_x1, m_y1);
    m_pSeries2->append(m_x2, m_y2);
    m_pSeries3->append(m_x3, m_y3);

    m_pChart->addSeries(m_pSeries1);
    m_pChart->addSeries(m_pSeries2);
    m_pChart->addSeries(m_pSeries3);

    m_pChart->createDefaultAxes();
//    m_pChart->setAxisX(&m_axis, m_pSeries1);

    // 设置刻度数量
    m_axis.setTickCount(10);
    // 设置x和y轴区间
    m_pChart->axisX()->setRange(0, 10);
    m_pChart->axisY()->setRange(-1.1, 1.1);
    // 隐藏x,y轴
    m_pChart->axisX()->setVisible(false);
    m_pChart->axisY()->setVisible(false);
    // 图例显示
    //m_pChart->legend()->setVisible(true);
    //m_pChart->legend()->setAlignment(Qt::AlignRight | Qt::AlignTop);

    m_pChartView = new QChartView(m_pChart);
    m_pChartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_pChartView);
    this->setLayout(layout);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotRealTimeData()));
    m_timer.setInterval(200);
    m_timer.start();
}

void SineCurve::slotRealTimeData()
{
    qreal x = m_pChart->plotArea().width() / m_axis.tickCount();
    qreal y = 10 / m_axis.tickCount();
    m_x1 += y;
    m_y1 = sin(m_x1);
    m_pSeries1->append(m_x1, m_y1);

    m_x2 = m_x1 + 1.0;
    m_y2 = m_y1;
    m_pSeries2->append(m_x2, m_y2);

    m_x3 = m_x1 + 1.7;
    m_y3 = m_y1;
    m_pSeries3->append(m_x3, m_y3);

    m_pChart->scroll(x / 2, 0);
}
SineCurve::~SineCurve()
{

}

void SineCurve::setBackgroundTransparent()
{
    // setAttribute(Qt::WA_TranslucentBackground);
    m_pChartView->setStyleSheet("background: transparent");
    m_pChart->setBackgroundVisible(false);
}

