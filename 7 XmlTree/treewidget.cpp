#include "treewidget.h"
#include "searchwidget.h"
#include "global.h"
#include "dragtreewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QMimeData>
#include <QByteArray>
#include <QDrag>
#include <QPixmap>


TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    createConnections();
}

TreeWidget::~TreeWidget()
{
}

void TreeWidget::setFixedState(bool fixed)
{
    m_bFixed = fixed;
}

void TreeWidget::setNewTreeState(bool state)
{
    m_pDragTreeWidget->setNewTreeState(state);
}

int TreeWidget::getTreeWigetItemState(const QString &text)
{
    QMap<QTreeWidgetItem*, int>::iterator it = m_mapItemState.begin();
    while (it != m_mapItemState.end()) {
        if(it.key()->text(0) == text) {
            qDebug() << "value:" << it.value() << ", text:-----" << text;
            return it.value();
        }
        it++;
    }
    return 0;
}

QList<QString> TreeWidget::getAllItemName()
{
    QList<QString> listName;
    QTreeWidgetItemIterator it(m_pDragTreeWidget);
    while (*it) {
        QString itemText = (*it)->text(0);
        listName.append(itemText);
        ++it;
    }
    return listName;
}

void TreeWidget::slotUpdateItemState(const QString &text, int state)
{
    QMap<QTreeWidgetItem*, int>::iterator it = m_mapItemState.begin();
    while (it != m_mapItemState.end()) {
        if(it.key()->text(0) == text) {
            if(state != getTreeWigetItemState(text)) {
                QString parentText = it.key()->parent()->text(0);
                m_mapItemState[it.key()] = state;
                QString clickedContent = parentText + "/" +text + "/" + stateToText(m_mapItemState[it.key()]);
                emit signalDoubleClicked(clickedContent);
            }

            break;
        }
        it++;
    }
}

void TreeWidget::slotNewAddItem(const QString &text, int state)
{
    if(m_bHideRootItem) {
        if(m_bNewItemState == false) {
            QTreeWidgetItem* rootItem = new QTreeWidgetItem;
            rootItem->setText(0, Global::GetNewAddItemText());
            m_listRootItem.append(rootItem);
            m_pDragTreeWidget->addTopLevelItem(rootItem);

            m_bNewItemState = true;
            m_listRootItem.append(rootItem);
        }

        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, text);
        m_mapItemState[item] = state;
        m_listRootItem.last()->addChild(item);
    }
    else {
        if(m_bNewItemState == false) {
            QTreeWidgetItem* rootItem = new QTreeWidgetItem;
            rootItem->setText(0, Global::GetNewAddItemText());
            m_pRootItem->addChild(rootItem);
            m_bNewItemState = true;
        }

        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, text);
        m_mapItemState[item] = state;

        QTreeWidgetItem* parentItem = textToItem(Global::GetNewAddItemText());
        if(parentItem) {
            parentItem->addChild(item);
        }
    }
}

void TreeWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        m_bMove = true;
        m_spanPoint = event->globalPos() - this->pos();
    }
}

void TreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bFixed)
    {
        if(m_bMove)
        {
            this->move(event->globalPos() - m_spanPoint);
        }
    }
}

void TreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bMove = false;
}

void TreeWidget::resizeEvent(QResizeEvent *event)
{
    //QSize size = event->size();
    Q_UNUSED(event);
    Global::SetTreeWidgetSize(this->size());
}

void TreeWidget::moveEvent(QMoveEvent *event)
{
    //QPoint pos = event->pos();
    Q_UNUSED(event);
    Global::SetTreeWidgetPos(this->pos());
}

void TreeWidget::paintEvent(QPaintEvent *event)
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

void TreeWidget::initialize()
{
    m_pMainVLayout = new QVBoxLayout;
    m_pMainVLayout->setSpacing(0);

    m_pSearchWidget = new SearchWidget;
    m_pMainVLayout->addWidget(m_pSearchWidget);

    // m_pDragTreeWidget = new QTreeWidget;
    m_pDragTreeWidget = new DragTreeWidget;
    m_pDragTreeWidget->setHeaderHidden(true);
    m_pDragTreeWidget->setColumnCount(1);
    // 子节点和根节点对其
    // m_pDragTreeWidget->setIndentation(0);
    // 多选
    m_pDragTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    m_pMainVLayout->addWidget(m_pDragTreeWidget);

    m_pButtonHLayout = new QHBoxLayout;
    m_pRedButton = new QPushButton;
    m_pRedButton->setFixedSize(50, 50);
    m_pRedButton->setObjectName("RedButton");
    m_pOrangeButton = new QPushButton;
    m_pOrangeButton->setFixedSize(50, 50);
    m_pOrangeButton->setObjectName("OrangeButton");
    m_pGreenButton = new QPushButton;
    m_pGreenButton->setFixedSize(50, 50);
    m_pGreenButton->setObjectName("GreenButton");
    m_pNoneButton = new QPushButton;
    m_pNoneButton->setFixedSize(50, 50);
    m_pNoneButton->setObjectName("NoneButton");
    m_pButtonHLayout->addWidget(m_pRedButton);
    m_pButtonHLayout->addWidget(m_pOrangeButton);
    m_pButtonHLayout->addWidget(m_pGreenButton);
    m_pButtonHLayout->addWidget(m_pNoneButton);
    m_pMainVLayout->addLayout(m_pButtonHLayout);

    this->setLayout(m_pMainVLayout);
    this->resize(300, 500);

    // 设置水平滑动条
    m_pDragTreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_pDragTreeWidget->header()->setStretchLastSection(false);

    m_fOpacity = Global::GetBkImageOpacity();
    m_bBkImageState = Global::GetBkImageState();
    if(m_bBkImageState == true) {
        m_sBkImagePath= Global::GetBkImagePath();
        QFile imageFile(m_sBkImagePath);
        if(!imageFile.exists()) {
            m_bBkImageState = false;
        }
    }

    m_bFixed = false;
    m_iSearchIndex = 0;
    m_bExpandFirstSubItem = Global::GetExpandFirstSubItemState();
    m_bHideRootItem = Global::GetHideRootItemState();

    readXml();

    initItemState();

    m_bNewItemState = false;
}

void TreeWidget::createConnections()
{
    connect(m_pSearchWidget, &SearchWidget::signalSearch, this, &TreeWidget::slotSearchContent);
    connect(m_pSearchWidget, &SearchWidget::signalNext, this, &TreeWidget::slotNextItem);
    connect(m_pSearchWidget, &SearchWidget::signalPrevious, this, &TreeWidget::slotPreviousItem);

    connect(m_pDragTreeWidget, &QTreeWidget::itemPressed, this, &TreeWidget::slotClickedTreeItem);
    //    connect(m_pDragTreeWidget, &QTreeWidget::itemDoubleClicked, this, &TreeWidget::slotDoubleClickedTreeItem);
    connect(m_pDragTreeWidget, &DragTreeWidget::signalCreateNewTree, this, &TreeWidget::signalCreateNewTree);
    connect(m_pDragTreeWidget, &DragTreeWidget::signalNewItemText, this, &TreeWidget::signalNewItemText);

    connect(m_pRedButton, &QPushButton::clicked, this, &TreeWidget::slotChangeItemState);
    connect(m_pOrangeButton, &QPushButton::clicked, this, &TreeWidget::slotChangeItemState);
    connect(m_pGreenButton, &QPushButton::clicked, this, &TreeWidget::slotChangeItemState);
    connect(m_pNoneButton, &QPushButton::clicked, this, &TreeWidget::slotChangeItemState);
}

void TreeWidget::readXml()
{
    // 新建QDomDocument类对象，它代表一个XML文档
    QDomDocument xmlDoc;
    QFile file(Global::GetRootPath() + "/resources/config.xml");
    // QFile file("resources/config.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setText("配置文件config.xml不存在");
        msgBox.exec();
        std::exit(0);
        return ;
    }

    // 将文件内容读到doc中
    if (!xmlDoc.setContent(&file)) {
        file.close();
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setText("配置文件config.xml内容错误");
        msgBox.exec();
        std::exit(0);
        return ;
    }

    // 关闭文件
    file.close();

    // 获得doc的第一个结点，即XML说明
    QDomNode firstNode = xmlDoc.firstChild();

    // 输出XML说明,nodeName()为“xml”,nodeValue()为版本和编码信息
    //    qDebug() << qPrintable(firstNode.nodeName())
    //             << qPrintable(firstNode.nodeValue());

    // 返回根元素
    QDomElement rootElem = xmlDoc.documentElement();
    // 返回根节点的第一个子结点
    //    QDomNode node = rootElem.firstChild();
    //    xmlToTree(node, true);
    if(!m_bHideRootItem) {
        m_pRootItem = new QTreeWidgetItem;
        QString rootText = removeNOString(rootElem.tagName());

        m_pRootItem->setText(0, rootText);
        m_pDragTreeWidget->addTopLevelItem(m_pRootItem);

        xmlToTree(rootElem, m_pRootItem);
        m_pRootItem->setExpanded(m_bExpandFirstSubItem);
    }
    else {
        QDomNode child = rootElem.firstChild();
        QList<QDomElement> listElement;
        while(!child.isNull()) {
            QString subText = removeNOString(child.toElement().tagName());
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, subText);
            m_listRootItem.append(item);
            listElement.append(child.toElement());
            child = child.nextSibling();
        }

        for(int i = 0; i < m_listRootItem.size(); i++) {
            m_pDragTreeWidget->addTopLevelItem(m_listRootItem[i]);
            xmlToTree(listElement[i].toElement(), m_listRootItem[i]);
        }

    }
}

void TreeWidget::xmlToTree(const QDomElement &element, QTreeWidgetItem* item)
{
    QDomNode child = element.firstChild();
    while(!child.isNull())
    {
        //        QString subText = child.toElement().tagName();
        //        QString tempText = subText.left(2).toLower();
        //        if(tempText == "no")
        //            subText = subText.right(subText.count() - 2);
        QString subText = removeNOString(child.toElement().tagName());
        if(!subText.isEmpty()) {
            QTreeWidgetItem* subItem = new QTreeWidgetItem;
            subItem->setText(0, subText);
            item->addChild(subItem);

            xmlToTree(child.toElement(), subItem);
        }
        child = child.nextSibling();
    }

}

void TreeWidget::searchAllItem()
{
    m_listItem.clear();
    QTreeWidgetItemIterator it(m_pDragTreeWidget);
    while (*it) {
        QString itemText = (*it)->text(0);
        if(itemText.contains(m_sSearchContent))
            m_listItem.append(*it);
        ++it;
    }
}

void TreeWidget::expandItem()
{
    if(!m_listItem.isEmpty())
        m_pDragTreeWidget->setCurrentItem(m_listItem[m_iSearchIndex]);
}

QString TreeWidget::removeNOString(const QString &str)
{
    QString text = str;
    QString tempText = str.left(2).toLower();
    if(tempText == "no")
        text = text.right(text.count() - 2);
    return text;
}

void TreeWidget::initItemState()
{
    QTreeWidgetItemIterator it(m_pDragTreeWidget);
    while (*it) {
        if((*it)->childCount() == 0) {
            m_mapItemState[*it] = 0;
        }
        ++it;
    }
}

QString TreeWidget::stateToText(int state)
{
    QString text = "无";
    switch(state) {
    case 0:
        text = "无";
        break;
    case 1:
        text = "红";
        break;
    case 2:
        text = "橙";
        break;
    case 3:
        text = "绿";
        break;
    }
    return text;
}

QTreeWidgetItem *TreeWidget::textToItem(const QString &text)
{
    QTreeWidgetItemIterator it(m_pDragTreeWidget);
    while (*it) {
        QString itemText = (*it)->text(0);
        if(itemText == text)
            return (*it);
        ++it;
    }
    return nullptr;
}

void TreeWidget::slotSearchContent(const QString &searchContent)
{
    m_sSearchContent = searchContent;
    if(m_sSearchContent.isEmpty())
        return;

    searchAllItem();
    m_iSearchIndex = 0;
    expandItem();
}

void TreeWidget::slotNextItem()
{
    int totalNum = m_listItem.size();
    if(m_iSearchIndex >= 0 && m_iSearchIndex < totalNum -1) {
        m_iSearchIndex++;
    }
    else if(m_iSearchIndex == totalNum - 1) {
        m_iSearchIndex = 0;
    }
    expandItem();
}

void TreeWidget::slotPreviousItem()
{
    int totalNum = m_listItem.size();
    if(m_iSearchIndex > 0 && m_iSearchIndex <= totalNum - 1) {
        m_iSearchIndex--;
    }
    else if(m_iSearchIndex == 0) {
        m_iSearchIndex = totalNum - 1;
    }
    expandItem();
}

void TreeWidget::slotDoubleClickedTreeItem(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0) {
        QString itemText = item->text(column);
        QString parentText = item->parent()->text(0);
        QString clickedContent = parentText + "/" +itemText + "/" + stateToText(m_mapItemState[item]);
        emit signalDoubleClicked(clickedContent);
    }
}

void TreeWidget::slotClickedTreeItem(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0) {
        QString itemText = item->text(column);
        QString parentText = item->parent()->text(0);
        QString clickedContent = parentText + "/" +itemText + "/" + stateToText(m_mapItemState[item]);
        emit signalClicked(clickedContent);
    }
}

void TreeWidget::slotChangeItemState()
{
    QTreeWidgetItem* selectedItem = m_pDragTreeWidget->currentItem();
    if(selectedItem == nullptr)
        return;

    if(selectedItem->childCount() == 0) {
        QPushButton* button = qobject_cast<QPushButton*>(this->sender());
        if(button == m_pRedButton) {
            m_mapItemState[selectedItem] = 1;
        }
        else if(button == m_pOrangeButton) {
            m_mapItemState[selectedItem] = 2;
        }
        else if(button == m_pGreenButton) {
            m_mapItemState[selectedItem] = 3;
        }
        else if(button == m_pNoneButton) {
            m_mapItemState[selectedItem] = 0;
        }

        QString itemText = selectedItem->text(0);
        QString parentText = selectedItem->parent()->text(0);
        QString clickedContent = parentText + "/" +itemText + "/" + stateToText(m_mapItemState[selectedItem]);

        emit signalDoubleClicked(clickedContent);
    }

}

