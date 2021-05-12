#include "droptreewidget.h"

#include <QMouseEvent>

#include <QDebug>

DropTreeWidget::DropTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    initialize();
    createConnections();
}

DropTreeWidget::~DropTreeWidget()
{

}

QPoint DropTreeWidget::getMousePos()
{
    return m_mousePos;
}

bool DropTreeWidget::getRightMouseState()
{
    return m_bRightState;
}

void DropTreeWidget::setRightMouseState(bool state)
{
    m_bRightState = state;
}

void DropTreeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::RightButton) {
        m_bRightState = true;
        m_mousePos = mapToGlobal(event->pos());
        qDebug() << "pos:" << m_mousePos;

        // QTreeWidget::mousePressEvent(event);
    }
    QTreeWidget::mousePressEvent(event);
//    qDebug() << "pos:22222222222222";
}

void DropTreeWidget::initialize()
{
    m_bRightState = false;
}

void DropTreeWidget::createConnections()
{
    // QTreeWidget的itemClicked信号只有左键才有作用，使用右键没有效果
//    connect(this, &DropTreeWidget::itemPressed, this, &DropTreeWidget::slotItemClicked);
}

//void DropTreeWidget::slotItemClicked(QTreeWidgetItem *item, int column)
//{
//    // qDebug() << "text:" << item->text(column);
//    if(m_bRightState) {
//        m_pSelectedItem = item;

//        m_pRightMenu->move(m_mousePos);
//        m_pRightMenu->show();
//    }
//    m_bRightState = false;
//}
