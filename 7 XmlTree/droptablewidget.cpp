#include "droptablewidget.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QDebug>

DropTableWidget::DropTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
//    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_bRightState = false;
}

DropTableWidget::~DropTableWidget()
{

}

QPoint DropTableWidget::getMousePos()
{
    return m_mousePos;
}

bool DropTableWidget::getRightMouseState()
{
    return m_bRightState;
}

void DropTableWidget::setRightMouseState(bool state)
{
    m_bRightState = state;
}

void DropTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::RightButton) {
        m_bRightState = true;
        m_mousePos = mapToGlobal(event->pos());
         qDebug() << "pos:" << m_mousePos;
        // QTreeWidget::mousePressEvent(event);
    }
    QTableWidget::mousePressEvent(event);
}
