#include "roundprogresswidget.h"

#include "progresspie.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSize>
#include <QPoint>
#include <QMoveEvent>
#include <QResizeEvent>

#include "global.h"

RoundProgressWidget::RoundProgressWidget(QWidget *parent)
    : QWidget(parent)
{
    m_pPieHLayout = new QHBoxLayout;
    // m_pPieHLayout->setContentsMargins(QMargins(10, 10, 10, 10));
    m_pPieHLayout->setMargin(0);
    m_pPieHLayout->setSpacing(0);

    // 圆形进度条
    m_pPie1 = new ProgressPie;
    m_pPie1->setValue(38);
    m_pPie2 = new ProgressPie;
    m_pPie2->setValue(62);
    m_pPie3 = new ProgressPie;
    m_pPie3->setValue(75);
    m_pPieHLayout->addWidget(m_pPie1);
    m_pPieHLayout->addWidget(m_pPie2);
    m_pPieHLayout->addWidget(m_pPie3);

    m_timer.setInterval(1000);
    m_timer.start();
    this->setLayout(m_pPieHLayout);

    connect(&m_timer, &QTimer::timeout, this, &RoundProgressWidget::slotUpdateValue);
}

void RoundProgressWidget::mousePressEvent(QMouseEvent *event)
{
    m_bMove = true;
    m_spanPoint = event->globalPos() - this->pos();
}

void RoundProgressWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove)
    {
        this->move(event->globalPos() - m_spanPoint);
    }

}

void RoundProgressWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void RoundProgressWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetRountProgressSize(this->size());
}

void RoundProgressWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetRoundProgressPos(this->pos());
}

void RoundProgressWidget::slotUpdateValue()
{
    /*
    int value1 = m_pPie1->getValue();
    int value2 = m_pPie2->getValue();
    int value3 = m_pPie3->getValue();
    if(value1 <= 43)
    {
        value1++;
    }
    else
    {
        value1 = 33;
    }
    m_pPie1->setValue(value1);

    if(value2 <= 67)
    {
        value2++;
    }
    else
    {
        value2 = 57;
    }
    m_pPie2->setValue(value2);

    if(value3 <= 80)
    {
        value3++;
    }
    else
    {
        value3 = 70;
    }
    m_pPie3->setValue(value3);
    */
    int value1 = generateDiffNumber(33, 43, 1).at(0);
    int value2 = generateDiffNumber(57, 67, 1).at(0);
    int value3 = generateDiffNumber(70, 80, 1).at(0);
    m_pPie1->setValue(value1);
    m_pPie2->setValue(value2);
    m_pPie3->setValue(value3);
}

std::vector<int> RoundProgressWidget::generateDiffNumber(int min, int max, int num)
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
        do{
            rnd = min+rand()%(max-min+1);

        }while(tmp.at(rnd-min)==-1);
        diff.push_back(rnd);
        tmp.at(rnd-min) = -1;
    }
    return diff;
}
