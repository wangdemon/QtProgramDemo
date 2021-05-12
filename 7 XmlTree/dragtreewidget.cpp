#include "dragtreewidget.h"
#include "global.h"

#include <QLabel>
#include <QMimeData>
#include <QByteArray>
#include <QDrag>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDebug>

DragTreeWidget::DragTreeWidget(QWidget *parent)
    : QTreeWidget(parent)    
{
    this->installEventFilter(this);
    this->setMouseTracking(true);
    this->setAcceptDrops(true);
    m_bNewTreeState = false;
}

void DragTreeWidget::setNewTreeState(bool state)
{
    m_bNewTreeState = state;
}

void DragTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }

}

void DragTreeWidget::dropEvent(QDropEvent *event)
{
    //    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    //        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    //        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    //        QPixmap pixmap;
    //        QPoint offset;
    //        dataStream >> pixmap >> offset;

    //        QLabel *newIcon = new QLabel(this);
    //        newIcon->setPixmap(pixmap);
    //        newIcon->move(event->pos() /*- offset*/);
    //        newIcon->show();
    //        newIcon->setAttribute(Qt::WA_DeleteOnClose);

    //        if (event->source() == this) {
    //            event->setDropAction(Qt::MoveAction);
    //            event->accept();
    //        } else {
    //            event->acceptProposedAction();
    //        }
    //    } else {
    //        event->ignore();
    //    }

//    qDebug() << "-------dropEvent";
//    if(m_pNewTreeWidget == nullptr) {
//        qDebug() << "-------2";
//        m_pNewTreeWidget = new NewTreeWidget;
//        m_pNewTreeWidget->resize(200, 300);
//        m_pNewTreeWidget->move(mapToGlobal(event->pos()));
//        m_pNewTreeWidget->show();
//    }
}


void DragTreeWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "-------dragLeaveEvent";

    Q_UNUSED(event);

    QList<QString> listItemText = getSelectedItemsText();
    if(!m_bNewTreeState) {
        if(listItemText.count()) {
            emit signalCreateNewTree(listItemText);
        }
    }
    else {
        if(listItemText.count()) {
            emit signalNewItemText(listItemText);
        }
    }
}

void DragTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QTreeWidget::mouseReleaseEvent(event);
    qDebug() << "-------mouseReleaseEvent---------------";
}

//void DragTreeWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    static int i = 0;
//    qDebug() << "-------mouseMoveEvent" << i++;
//}

bool DragTreeWidget::eventFilter(QObject *target, QEvent *event)
{

//    if(event->type() == QEvent::MouseMove)
//    {
//       // This piece of code is never called
//        qDebug() << "-------mouseMoveEvent";
//    }
    return QTreeWidget::eventFilter(target, event);
}

QList<QString> DragTreeWidget::getSelectedItemsText()
{
    QList<QString> listItemText;
    QList<QTreeWidgetItem*> listItem = this->selectedItems();
    if(listItem.count()) {
        foreach (QTreeWidgetItem* item, listItem) {
            QString text = item->text(0);
            if(item->childCount() == 0)
                listItemText.append(text);
        }
    }
    return listItemText;
}

void DragTreeWidget::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);

    QList<QString> listText = getSelectedItemsText();
    if(listText.count() == 0) {
        return;
    }

    QImage image(140, 140, QImage::Format_ARGB32);
    image.fill(QColor(47, 168, 236, 150));
    QPixmap pixmap = QPixmap::fromImage(image);
    // pixmap.load(Global::GetImagePath() + "hover.png");

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() /*- child->pos()*/ + QPoint(pixmap.width() / 2, pixmap.height() / 2));

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    // painter.fillRect(pixmap.rect(), QColor(47, 168, 236, 150));
    if(m_bNewTreeState) {
        QFont font = painter.font();
        font.setPixelSize(16);
        painter.setFont(font);
        QPen pen = painter.pen();
        pen.setStyle(Qt::DotLine);
        pen.setColor(QColor("#2FEC2F"));
        painter.setPen(pen);

        for(int i = 0; i < listText.size(); i++) {
            const QRect rectangle = QRect(10, 10 + 40 * i, pixmap.width() - 10, 50);
            QRect boundingRect;
            painter.drawText(rectangle, 0, listText.at(i), &boundingRect);
        }

    }
    painter.end();

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(tempPixmap);
    drag->setHotSpot(/*mapToGlobal(event->pos())*/QPoint(pixmap.width() / 2, pixmap.height() / 2));
    // qDebug() << "pos1:" << event->pos() << "pos2:" << mapToParent(event->pos()) << "pos3:" << mapToGlobal(event->pos());

//    QPixmap tempPixmap = pixmap;
//    QPainter painter;
//    painter.begin(&tempPixmap);
//    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
//    if(m_bNewTreeState) {
//        QFont font = painter.font();
//        font.setPixelSize(16);
//        painter.setFont(font);
//        QPen pen = painter.pen();
//        pen.setStyle(Qt::DotLine);
//        painter.setPen(pen);
//        const QRect rectangle = QRect(10, 10, 50, 50);
//        QRect boundingRect;
//        painter.drawText(rectangle, 0, "Hello", &boundingRect);
//        qDebug() << "-------------";
//    }
//    painter.end();

//    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
//        child->close();
    } else {
//        child->show();
//        child->setPixmap(pixmap);
    }
}

