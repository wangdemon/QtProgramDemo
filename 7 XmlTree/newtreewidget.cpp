#include "newtreewidget.h"

#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QFile>
#include <QHeaderView>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QLabel>
#include <QMimeData>
#include <QByteArray>
#include <QDrag>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "global.h"
#include "droptreewidget.h"
#include "droptablewidget.h"
#include "addnewitemwidget.h"


NewTreeWidget::NewTreeWidget(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    createConnections();
}

NewTreeWidget::~NewTreeWidget()
{
    delete m_pDeleteAction;
    m_pDeleteAction = nullptr;
    delete m_pAddAction;
    m_pAddAction = nullptr;
    delete m_pRightMenu;
    m_pRightMenu = nullptr;
}

void NewTreeWidget::addItem(const QString &text, int state)
{
    // 树形图添加节点
    /*
    int count = m_listRootItem.count();
    bool containState = false;
    for (int i = 0; i < m_listRootItem.size(); i++) {
        QString itemText = m_listRootItem.at(i)->text(0);
        itemText = itemText.right(itemText.size() - 2);
        if(text == itemText) {
            containState = true;
            break;
        }
    }

    if(!containState) {
        QTreeWidgetItem* rootItem = new QTreeWidgetItem;
        rootItem->setText(0, QString::number(count + 1) + " " + text);
        m_pDropTreeWidget->addTopLevelItem(rootItem);
        m_listRootItem.append(rootItem);

        QTreeWidgetItem* item1 = new QTreeWidgetItem;
        QTreeWidgetItem* item2 = new QTreeWidgetItem;
        QTreeWidgetItem* item3 = new QTreeWidgetItem;
        item1->setText(0, "干扰");
        item2->setText(0, "扰乱");
        item3->setText(0, "损伤");
        rootItem->addChild(item1);
        rootItem->addChild(item2);
        rootItem->addChild(item3);
    }
    */
    // 表格添加节点
    QList<QTableWidgetItem*> listItem = m_pDropTableWidget->findItems(text, Qt::MatchExactly);
    //    if(listItem.count() == 1) {
    //        QTableWidgetItem* item = listItem.first();
    //        int row = m_pDropTableWidget->row(item);
    //    }
    if(listItem.count())
        return;
    addTableRow(text, state);
}

void NewTreeWidget::setNewItemTexts(QList<QString> texts)
{
    m_listNewItemText.clear();
    m_listNewItemText.append(texts);
}

void NewTreeWidget::updateItemState(const QString &text, int state)
{
    // 断开QComboBox对象的连接
    int rowCount = m_pDropTableWidget->rowCount();
    for(int i = 0; i < rowCount; i++) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(m_pDropTableWidget->cellWidget(i, 2));
        comboBox->disconnect();
    }

    QList<QTableWidgetItem*> listItem = m_pDropTableWidget->findItems(text, Qt::MatchExactly);
    if(listItem.count() == 1) {
        QTableWidgetItem* item = listItem.first();
        int row = m_pDropTableWidget->row(item);
        QComboBox* comboBox = qobject_cast<QComboBox*>(m_pDropTableWidget->cellWidget(row, 2));
        comboBox->setCurrentIndex(state);
    }

    // 重新建立QComboBox对象的连接
    for(int i = 0; i < rowCount; i++) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(m_pDropTableWidget->cellWidget(i, 2));
        connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUpdateItemState(int)));
    }
}

void NewTreeWidget::setAllItemName(QList<QString> listName)
{
    m_listAllItemName.clear();
    m_listAllItemName.append(listName);
}

void NewTreeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(m_bBkImageState) {
        QRectF target(0, 0, this->width(), this->height());
        QPixmap pixmap(m_sBkImagePath);
        QRectF source(0.0, 0.0, pixmap.width(), pixmap.height());
        QPainter painter(this);
        painter.setOpacity(m_fOpacity);
        painter.drawPixmap(target, pixmap, source);
    }
}

void NewTreeWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        m_bMove = true;
        m_spanPoint = event->globalPos() - this->pos();
    }
}

void NewTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        if(m_bMove)
        {
            this->move(event->globalPos() - m_spanPoint);
        }
    }
}

void NewTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void NewTreeWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetNewTreeWidgetSize(this->size());
}

void NewTreeWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetNewTreeWidgetPos(this->pos());
}

void NewTreeWidget::dragEnterEvent(QDragEnterEvent *event)
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

void NewTreeWidget::dragMoveEvent(QDragMoveEvent *event)
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

void NewTreeWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        //QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        if(m_listNewItemText.size()) {
            for(int i = 0; i < m_listNewItemText.size(); i++) {
                addItem(m_listNewItemText.at(i));
            }
        }

        //        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        //        QPixmap pixmap;
        //        QPoint offset;
        //        dataStream >> pixmap >> offset;

        //        QLabel *newIcon = new QLabel(this);
        //        newIcon->setPixmap(pixmap);
        //        newIcon->move(event->pos() - offset);
        //        newIcon->show();
        //        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        //        if (event->source() == this) {
        //            event->setDropAction(Qt::MoveAction);
        //            event->accept();
        //        } else {
        //            event->acceptProposedAction();
        //        }
    } else {
        event->ignore();
    }
}


void NewTreeWidget::initialize()
{
    m_pMainVLayout = new QVBoxLayout;
    //    m_pMainVLayout->setContentsMargins(20,20,20,20);
    //    m_pDropTreeWidget = new DropTreeWidget;
    //    m_pDropTreeWidget->setHeaderHidden(true);
    //    m_pDropTreeWidget->setColumnCount(1);
    //    m_pDropTreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //    m_pDropTreeWidget->header()->setStretchLastSection(false);

    m_pDropTableWidget = new DropTableWidget;
    m_pDropTableWidget->setColumnCount(3);
    m_pDropTableWidget->setRowCount(0);
    //    QComboBox* comboBox = new QComboBox;
    //    comboBox->addItem("无");
    //    comboBox->addItem("干扰");
    //    comboBox->addItem("扰乱");
    //    comboBox->addItem("损伤");
    //    m_pDropTableWidget->setCellWidget(0, 2, comboBox);

    //    m_pMainVLayout->addWidget(m_pDropTreeWidget);
    m_pMainVLayout->addWidget(m_pDropTableWidget);


    m_pButtonHLayout = new QHBoxLayout;
    m_pAddButton = new QPushButton;
    m_pAddButton->setIcon(QIcon(Global::GetImagePath() + "add.png"));
    m_pAddButton->setIconSize(QSize(50, 50));
    m_pAddButton->setObjectName("AddButton");
    m_pDeleteButton = new QPushButton;
    m_pDeleteButton->setIcon(QIcon(Global::GetImagePath() + "delete.png"));
    m_pDeleteButton->setIconSize(QSize(50, 50));
    m_pDeleteButton->setObjectName("DeleteButton");
    m_pButtonHLayout->addWidget(m_pAddButton);
    m_pButtonHLayout->addWidget(m_pDeleteButton);
    m_pMainVLayout->addLayout(m_pButtonHLayout);

    // this->resize(200, 300);
    this->setLayout(m_pMainVLayout);


    if(!Global::GetFrameState()) {
        this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
    }

    m_bFixed = false;
    m_fOpacity = Global::GetBkImageOpacity();
    m_bBkImageState = Global::GetBkImageState();
    if(m_bBkImageState == true) {
        m_sBkImagePath= Global::GetBkImagePath();
        QFile imageFile(m_sBkImagePath);
        if(!imageFile.exists()) {
            m_bBkImageState = false;
        }
    }

    this->setAcceptDrops(true);

    m_pRightMenu = new QMenu;
    m_pAddAction = new QAction;
    m_pAddAction->setText("新增");
    m_pDeleteAction = new QAction;
    m_pDeleteAction->setText("删除");
    m_pRightMenu->addAction(m_pAddAction);
    m_pRightMenu->addSeparator();
    m_pRightMenu->addAction(m_pDeleteAction);

    m_pSelectedItem = nullptr;

    m_pAddNewItemWidget = new AddNewItemWidget;
}

void NewTreeWidget::createConnections()
{
    // connect(m_pDropTreeWidget, &QTreeWidget::itemPressed, this, &NewTreeWidget::slotItemClicked);
    connect(m_pDropTableWidget, &QTableWidget::itemPressed, this, &NewTreeWidget::slotItemClicked);
    connect(m_pDeleteAction, &QAction::triggered, this, &NewTreeWidget::slotDeleteItem);
    connect(m_pDeleteButton, &QPushButton::clicked, this, &NewTreeWidget::slotDeleteItem);
    connect(m_pAddAction, &QAction::triggered, this, &NewTreeWidget::slotShowAndNewWidget);
    connect(m_pAddButton, &QPushButton::clicked, this, &NewTreeWidget::slotShowAndNewWidget);
    connect(m_pAddNewItemWidget, &AddNewItemWidget::signalSubmitAddNew, this, &NewTreeWidget::slotSubmitAndNewItem);
}

void NewTreeWidget::addTableRow(const QString &text, int state)
{
    int count = m_pDropTableWidget->rowCount();
    m_pDropTableWidget->setRowCount(count + 1);
    QTableWidgetItem* numItem = new QTableWidgetItem;
    numItem->setText(QString::number(count + 1));
    QTableWidgetItem* textItem = new QTableWidgetItem;
    textItem->setText(text);
    QComboBox* comboBox = new QComboBox;
    comboBox->addItem("无");
    comboBox->addItem("干扰");
    comboBox->addItem("扰乱");
    comboBox->addItem("损伤");
    comboBox->setCurrentIndex(state);

    m_pDropTableWidget->setItem(count, 0, numItem);
    m_pDropTableWidget->setItem(count, 1, textItem);
    m_pDropTableWidget->setCellWidget(count, 2, comboBox);
    m_pDropTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    // connect(comboBox, &QComboBox::currentIndexChanged, this, &NewTreeWidget::slotUpdateItemState);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUpdateItemState(int)));
}

void NewTreeWidget::updateTableRowNum()
{
    int rowCount = m_pDropTableWidget->rowCount();
    for(int i = 0; i < rowCount; i++) {
        QString textNum = m_pDropTableWidget->item(i, 0)->text();
        if(textNum.toInt() != (i + 1))
            m_pDropTableWidget->item(i, 0)->setText(QString::number(i + 1));
    }
}

void NewTreeWidget::submitAddNewItem(int num, QString &name, int state)
{
    addTableRow(name, state);
    emit signalNewAddItem(name, state);
}

void NewTreeWidget::slotItemClicked(QTableWidgetItem *item)
{
    if(m_pDropTableWidget->getRightMouseState()) {
        m_pRightMenu->move(m_pDropTableWidget->getMousePos());
        m_pRightMenu->show();
        m_pDropTableWidget->setRightMouseState(false);
    }
    m_pSelectedItem = item;
}

void NewTreeWidget::slotDeleteItem()
{
    int row = m_pDropTableWidget->row(m_pSelectedItem);
    m_pDropTableWidget->removeRow(row);
    updateTableRowNum();
    if(m_pDropTableWidget->rowCount() == 0)
        emit signalNoItem();
}

//void NewTreeWidget::slotItemClicked(QTreeWidgetItem *item, int column)
//{
//    if(item->childCount() == 0) {
//        return;
//    }

//    if(m_pDropTreeWidget->getRightMouseState()) {
//        m_pSelectedItem = item;
//        m_pRightMenu->move(m_pDropTreeWidget->getMousePos());
//        m_pRightMenu->show();
//        m_pDropTreeWidget->setRightMouseState(false);
//    }
//}

//void NewTreeWidget::slotDeleteItem()
//{
//    if(m_pSelectedItem != nullptr) {
//        QList<QTreeWidgetItem *> listItem = m_pSelectedItem->takeChildren();
//        while (!listItem.isEmpty()) {
//            QTreeWidgetItem* item = listItem.first();
//            listItem.removeFirst();
//            delete item;
//            item = nullptr;
//        }

//        m_listRootItem.removeOne(m_pSelectedItem);

//        delete m_pSelectedItem;
//        m_pSelectedItem = nullptr;
//    }

//    if(m_listRootItem.count() == 0)
//        emit signalNoItem();
//}

void NewTreeWidget::slotUpdateItemState(int index)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(this->sender());
    int rowCount = m_pDropTableWidget->rowCount();

    for(int i = 0; i < rowCount; i++) {
        QWidget* widget = m_pDropTableWidget->cellWidget(i, 2);
        QComboBox* comboBoxWidget = qobject_cast<QComboBox*>(widget);
        qDebug() << "---------------111111111111111111111111111111111111111111";
        if(comboBox == comboBoxWidget) {
            QString text = m_pDropTableWidget->item(i, 1)->text();
            emit signalUpdateItemState(text, index);
            qDebug() << "---------------2222222222222222222222------------------" << text;
        }
    }
}

void NewTreeWidget::slotShowAndNewWidget()
{
    if(!m_pAddNewItemWidget->isVisible()) {
        m_pAddNewItemWidget->cleanData();
        m_pAddNewItemWidget->show();
    }

    int count = m_pDropTableWidget->rowCount();
    m_pAddNewItemWidget->setNum(count + 1);
}

void NewTreeWidget::slotSubmitAndNewItem()
{
    int num = m_pAddNewItemWidget->getNum();
    QString name = m_pAddNewItemWidget->getName();
    int state = m_pAddNewItemWidget->getState();
    if(name.isEmpty()) {
        m_pAddNewItemWidget->setTipText("请输入节点名称!", 0);
        return;
    }
    else {
       for(int i = 0; i < m_listAllItemName.size(); i++) {
           if(m_listAllItemName.at(i) == name) {
               m_pAddNewItemWidget->setTipText("节点名称重复了, 请输入其他名称.", 1);
               qDebug() << "================";
               return;
           }
       }
    }

    m_pAddNewItemWidget->hide();
    submitAddNewItem(num, name, state);
}
