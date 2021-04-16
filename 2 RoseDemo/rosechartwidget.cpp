#include "rosechartwidget.h"

#include <QHBoxLayout>
#include "rosepie.h"
#include <QSize>
#include <QPoint>
#include <QMoveEvent>
#include <QResizeEvent>
#include "global.h"

RoseChartWidget::RoseChartWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pMainHLayout = new QHBoxLayout;
    m_pRosePie = new RosePie;
    m_pMainHLayout->addWidget(m_pRosePie);
    this->setLayout(m_pMainHLayout);

    QMap<int, int> valueMap;
    valueMap[0] = 10;
    valueMap[1] = 25;
    valueMap[2] = 65;
    //valueMap[3] = 30;
    QMap<int, QString> titleMap;
    titleMap[0] = "10%高危故障";
    titleMap[1] = "25%中危故障";
    titleMap[2] = "65%低危故障";
    //titleMap[3] = "30";
    QMap<int, QColor> colorMap;
    colorMap[0] = QColor("#EF2020");
    colorMap[1] = QColor("#F1D93B");
    colorMap[2] = QColor("#24D85B");
    //colorMap[3] = QColor("#2BEBED");
    m_pRosePie->setData(valueMap, titleMap, colorMap);


    m_timer.setInterval(1000);
    m_timer.start();

    connect(&m_timer, &QTimer::timeout, this, &RoseChartWidget::slotUpdateValue);
}

void RoseChartWidget::mousePressEvent(QMouseEvent *event)
{
    m_bMove = true;
    m_spanPoint = event->globalPos() - this->pos();
}

void RoseChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        this->move(event->globalPos() - m_spanPoint);
    }

}

void RoseChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void RoseChartWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetRoseChartSize(this->size());
}

void RoseChartWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetRoseChartPos(this->pos());
}

void RoseChartWidget::slotUpdateValue()
{
    int value1 = generateDiffNumber(5, 15, 1).at(0);
    int value2 = generateDiffNumber(20, 30, 1).at(0);
    int value3 = 100 - value1 - value2;
    QMap<int, int> valueMap;
    valueMap[0] = value1;
    valueMap[1] = value2;
    valueMap[2] = value3;
    QMap<int, QString> titleMap;
    titleMap[0] = QString::number(value1) + "%高危故障";
    titleMap[1] = QString::number(value2) + "%中危故障";
    titleMap[2] = QString::number(value3) + "%低危故障";
    //titleMap[3] = "30";
    QMap<int, QColor> colorMap;
    colorMap[0] = QColor("#EF2020");
    colorMap[1] = QColor("#F1D93B");
    colorMap[2] = QColor("#24D85B");
    //colorMap[3] = QColor("#2BEBED");
    m_pRosePie->setData(valueMap, titleMap, colorMap);
}


std::vector<int> RoseChartWidget::generateDiffNumber(int min, int max, int num)
{
    int rnd;
    std::vector<int> diff;
    std::vector<int> tmp;//存储剩余的数
    //初始化
    for(int i = min;i < max+1 ; i++ )
    {
        tmp.push_back(i);
    }
    srand((unsigned)time(0)); //初始化随机数种子
    for(int i = 0 ; i < num ; i++)
    {
        do
        {
            rnd = min+rand()%(max-min+1);

        }
        while(tmp.at(rnd - min) == -1);
        diff.push_back(rnd);
        tmp.at(rnd-min) = -1;
    }
    return diff;
}
