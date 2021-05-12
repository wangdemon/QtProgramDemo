#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QDomElement>
#include <QPoint>
#include <QString>
#include <QMap>

class QTreeWidget;
class QHBoxLayout;
class QVBoxLayout;
class QTreeWidgetItem;
class DragTreeWidget;
class SearchWidget;

class QHBoxLayout;
class QPushButton;

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    void setFixedState(bool fixed);

    void setNewTreeState(bool state);

    /**
    * @brief 获取树形图节点的状态
    *  根据节点的名称, 获取节点的状态
    * @param text是树形图节点的名称
    **/
    int getTreeWigetItemState(const QString& text);


    QList<QString> getAllItemName();

public slots:
    /**
    * @brief 更新树形图节点状态
    *  通过新建的树形图，改变树形图的状态
    **/
    void slotUpdateItemState(const QString& text, int state);

    /**
    * @brief 新增节点
    **/
    void slotNewAddItem(const QString& text, int state);

signals:
    void signalDoubleClicked(QString& clickedContent);
    void signalClicked(QString& clickedContent);

    void signalCreateNewTree(QList<QString> listItemText);
    void signalNewItemText(QList<QString> listItemText);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;

    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;




private:
    void initialize();
    void createConnections();

    void readXml();
    void xmlToTree(const QDomElement &element, QTreeWidgetItem* item);

    // 遍历所有节点
    void searchAllItem();
    // 展开节点
    void expandItem();

    QString removeNOString(const QString& str);

    /**
    * @brief 初始化节点状态
    *  把所有字节点的状态都设置为无
    **/
    void initItemState();

    /**
    * @brief 节点状态转文字
    *  节点的每种状态都对应一种文字, 0对应无, 1对应红, 2对应绿, 3对应蓝
    * @param state是节点的状态, 其值为0~3之间的整数
    **/
    QString stateToText(int state);

    /**
    * @brief 通过节点文本寻找节点
    **/
    QTreeWidgetItem* textToItem(const QString& text);

private slots:
    void slotSearchContent(const QString& searchContent);

    void slotNextItem();
    void slotPreviousItem();

    void slotDoubleClickedTreeItem(QTreeWidgetItem *item, int column);
    void slotClickedTreeItem(QTreeWidgetItem *item, int column);

    /**
    * @brief 改变节点状态槽函数
    * @param 点击四种状态按钮, 改变节点的状态
    **/
    void slotChangeItemState();

private:
    QVBoxLayout* m_pMainVLayout;
    SearchWidget* m_pSearchWidget;

    // QTreeWidget* m_pDragTreeWidget;
    DragTreeWidget* m_pDragTreeWidget;
    QTreeWidgetItem* m_pRootItem;
    QList<QTreeWidgetItem*> m_listRootItem;
    QList<QTreeWidgetItem*> m_listItem;

    bool m_bMove;
    QPoint m_spanPoint;
    bool m_bFixed;

    bool m_bBkImageState;
    QString m_sBkImagePath;

    int m_iSearchIndex;
    QString m_sSearchContent;
    float m_fOpacity;

    // 隐藏根节点
    bool m_bHideRootItem;
    // 展开第一个子节点
    bool m_bExpandFirstSubItem;

    // 四个按钮, 分别对应节点的四种状态
    // 状态: 红、橙、绿和无
    QHBoxLayout* m_pButtonHLayout;
    QPushButton* m_pRedButton;
    QPushButton* m_pOrangeButton;
    QPushButton* m_pGreenButton;
    QPushButton* m_pNoneButton;

    // 子节点状态
    // 0表示无, 1表示红, 2表示橙, 3表示绿
    QMap<QTreeWidgetItem*, int> m_mapItemState;

    bool m_bNewItemState;
};
#endif // TREEWIDGET_H
