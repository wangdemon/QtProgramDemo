#include "barchartwidget.h"

#include <QHBoxLayout>
#include <QSize>
#include <QPoint>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QList>
#include "barchart.h"
#include "global.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

// random generator function:
int myrandom (int i) { return std::rand()%i;}

BarChartWidget::BarChartWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pMainHLayout = new QHBoxLayout;
    m_pBarChart = new BarChart;
    m_pMainHLayout->addWidget(m_pBarChart);
    this->setLayout(m_pMainHLayout);

    QList<int> valueList;
    valueList << 3 << 5 << 8 << 10 << 6;
    QList<QString> titleList;
    titleList << "1号发动机" << "2号发动机" << "3号发动机" << "4号发动机" << "5号发动机";
    m_pBarChart->setData(valueList, titleList);

    connect(&m_timer, &QTimer::timeout, this, &BarChartWidget::slotUpdate);
    m_timer.setInterval(1000);
    m_timer.start();
}

void BarChartWidget::mousePressEvent(QMouseEvent *event)
{
    m_bMove = true;
    m_spanPoint = event->globalPos() - this->pos();
}

void BarChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        this->move(event->globalPos() - m_spanPoint);
    }

}

void BarChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void BarChartWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetBarChartSize(this->size());
}

void BarChartWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetBarChartPos(this->pos());
}

void BarChartWidget::slotUpdate()
{
    QList<int> valueList;

    std::srand ( unsigned ( std::time(0) ) );
    std::vector<int> myvector;

    // set some values:
    for (int i = 1; i < 11; ++i)
        myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

    // using built-in random generator:
    std::random_shuffle ( myvector.begin(), myvector.end() );

    // using myrandom:
    std::random_shuffle ( myvector.begin(), myvector.end(), myrandom);

    // print out content:
    int i = 0;
    for (std::vector<int>::iterator it = myvector.begin();
         it != myvector.end(); ++it)
    {
        if(i < 5)
            valueList << *it;
        else
            break;
        i++;
    }


//    QList<int> valueList;
//    valueList << generateDiffNumber(1, 10, 1).at(0)
//              << generateDiffNumber(1, 10, 1).at(0)
//              << generateDiffNumber(1, 10, 1).at(0)
//              << generateDiffNumber(1, 10, 1).at(0)
//              << generateDiffNumber(1, 10, 1).at(0);
    QList<QString> titleList;
    titleList << "1号发动机" << "2号发动机" << "3号发动机" << "4号发动机" << "5号发动机";
    m_pBarChart->setData(valueList, titleList);
}

std::vector<int> BarChartWidget::generateDiffNumber(int min, int max, int num)
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
            rnd = min + rand()%(max - min + 1);

        }
        while(tmp.at(rnd - min) == -1);
        diff.push_back(rnd);
        tmp.at(rnd - min) = -1;
    }
    return diff;
}
