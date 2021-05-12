#include "addnewitemwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>

#include "global.h"

AddNewItemWidget::AddNewItemWidget(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    createConnections();
}

void AddNewItemWidget::setNum(int num)
{
    m_pNumItem->setText(QString::number(num));
}

int AddNewItemWidget::getNum()
{
    return m_pNumItem->text().toInt();
}

QString AddNewItemWidget::getName()
{
    return m_pNameItem->text();
}

int AddNewItemWidget::getState()
{
    return m_pStateComboBox->currentIndex();
}

void AddNewItemWidget::setTipText(const QString &text, int type)
{
    m_sTipText = text;
    m_iTipType = type;
    m_timer.start();
}

void AddNewItemWidget::closeTip()
{
    m_timer.stop();
}

void AddNewItemWidget::cleanData()
{
    m_pNumItem->setText("");
    m_pNameItem->setText("");
}

void AddNewItemWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        m_bMove = true;
        m_spanPoint = event->globalPos() - this->pos();
    }
}

void AddNewItemWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        if(m_bMove)
        {
            this->move(event->globalPos() - m_spanPoint);
        }
    }
}

void AddNewItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void AddNewItemWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QRectF target(0, 0, this->width(), this->height());
    QPixmap pixmap(Global::GetImagePath() + "bk01.jpg");
    QRectF source(0.0, 0.0, pixmap.width(), pixmap.height());
    QPainter painter(this);
    painter.setOpacity(Global::GetBkImageOpacity());
    painter.drawPixmap(target, pixmap, source);
}


void AddNewItemWidget::initialize()
{
    m_pMainVLayout = new QVBoxLayout;

    m_pParameterTableWidget = new QTableWidget;
    m_pParameterTableWidget->setColumnCount(3);
    m_pParameterTableWidget->setRowCount(1);
    m_pParameterTableWidget->setHorizontalHeaderLabels(QStringList() << "序号" << "名称" << "状态");
    m_pParameterTableWidget->verticalHeader()->setVisible(false);

    m_pNumItem = new QTableWidgetItem;
    // 禁止编辑
    m_pNumItem->setFlags(m_pNumItem->flags() & (~Qt::ItemIsEditable));
    m_pNumItem->setBackground(QBrush(QColor(Qt::lightGray)));

    m_pNameItem = new QTableWidgetItem;
    m_pParameterTableWidget->setItem(0, 0, m_pNumItem);
    m_pParameterTableWidget->setItem(0, 1, m_pNameItem);

    m_pStateComboBox = new QComboBox;
    m_pStateComboBox->addItem("无");
    m_pStateComboBox->addItem("干扰");
    m_pStateComboBox->addItem("扰乱");
    m_pStateComboBox->addItem("损伤");
    m_pStateComboBox->setCurrentIndex(0);
    m_pParameterTableWidget->setCellWidget(0, 2, m_pStateComboBox);
    // m_pParameterTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    //    m_pParameterTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_pParameterTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_pMainVLayout->addWidget(m_pParameterTableWidget);

    m_pTipLabel = new QLabel;
    m_pTipLabel->setObjectName("TipLabel");
    m_pMainVLayout->addWidget(m_pTipLabel);
    m_timer.setInterval(1000);

    m_pButtonHLayout = new QHBoxLayout;
    m_pSubmitButton = new QPushButton;
    m_pSubmitButton->setText("确认");
    m_pCancelButton = new QPushButton;
    m_pCancelButton->setText("取消");
    m_pButtonHLayout->addStretch();
    m_pButtonHLayout->addWidget(m_pSubmitButton);
    m_pButtonHLayout->addWidget(m_pCancelButton);
    m_pMainVLayout->addLayout(m_pButtonHLayout);

    this->setLayout(m_pMainVLayout);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // this->setAttribute(Qt::WA_TranslucentBackground);

    this->setWindowModality(Qt::ApplicationModal);

    this->setFixedSize(400, 150);
    m_bFixed = false;
}

void AddNewItemWidget::createConnections()
{
    connect(m_pCancelButton, &QPushButton::clicked, this, &AddNewItemWidget::slotCancel);
    connect(m_pSubmitButton, &QPushButton::clicked, this, &AddNewItemWidget::signalSubmitAddNew);
    connect(&m_timer, &QTimer::timeout, this, &AddNewItemWidget::slotTip);
}

void AddNewItemWidget::slotCancel()
{
    this->hide();
}

void AddNewItemWidget::slotTip()
{
    if(m_iTipType == 0) {
        if(!m_pNameItem->text().isEmpty()) {
            m_timer.stop();
            m_pTipLabel->setText("");
            return;
        }
    }

    QString text = m_pTipLabel->text();
    if(text.isEmpty()) {
        m_pTipLabel->setText(m_sTipText);
    }
    else {
        m_pTipLabel->setText("");
    }
}
