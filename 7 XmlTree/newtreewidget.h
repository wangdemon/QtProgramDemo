#ifndef NEWTREEWIDGET_H
#define NEWTREEWIDGET_H


#include <QWidget>
#include <QList>

class QVBoxLayout;
class QTreeWidget;
class QTreeWidgetItem;
class QMouseEvent;
class QDragEnterEvent;
class QDropEvent;
class QHBoxLayout;
class QPushButton;
class QMenu;
class QAction;
class QTableWidget;
class DropTreeWidget;
class DropTableWidget;
class QTableWidgetItem;
class QHBoxLayout;
class QPushButton;

class AddNewItemWidget;

class NewTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewTreeWidget(QWidget* parent = nullptr);
    ~NewTreeWidget();

    void addItem(const QString& text, int state = 0);

    void setNewItemTexts(QList<QString> texts);

    /**
    * @brief 更新树形图节点的状态
    *  点击旧的树形图, 改变节点的状态, 新的树形图节点状态也保持更新
    **/
    void updateItemState(const QString& text, int state);

    void setAllItemName(QList<QString> listName);

signals:
    void signalNoItem();

    /**
    * @brief 更新树形图节点状态信号, 由新的树形图触发
    **/
    void signalUpdateItemState(const QString& text, int state);

    void signalNewAddItem(const QString& text, int state);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void initialize();
    void createConnections();

    void addTableRow(const QString& text, int state);

    /**
    * @brief 更新节点编号
    **/
    void updateTableRowNum();

    void submitAddNewItem(int num, QString& name, int state);

private slots:
    /**
    * @brief 点击树形图节点
    *  点击树形图节点，弹出右键菜单
    **/
    // void slotItemClicked(QTreeWidgetItem *item, int column);
    void slotItemClicked(QTableWidgetItem* item);

    /**
    * @brief 删除树形图节点
    **/
    // void slotDeleteItem();
    void slotDeleteItem();

    /**
    * @brief 更新树形图节点状态
    *  通过点击QComboBox对象,改变新的树形图节点状态
    **/
    void slotUpdateItemState(int index);

    /**
    * @brief 显示新增窗口
    **/
    void slotShowAndNewWidget();

    /**
    * @brief 确认新增节点
    **/
    void slotSubmitAndNewItem();
private:
    QVBoxLayout* m_pMainVLayout;
    // DropTreeWidget* m_pDropTreeWidget;
    // QList<QTreeWidgetItem*> m_listRootItem;
    // QTreeWidgetItem* m_pSelectedItem;

    DropTableWidget* m_pDropTableWidget;
    QTableWidgetItem* m_pSelectedItem;

    bool m_bMove;
    QPoint m_spanPoint;
    bool m_bFixed;

    bool m_bBkImageState;
    QString m_sBkImagePath;

    float m_fOpacity;

    QList<QString> m_listNewItemText;

    // 右键菜单
    QMenu* m_pRightMenu;
    QAction* m_pAddAction;
    QAction* m_pDeleteAction;

    QHBoxLayout* m_pButtonHLayout;
    QPushButton* m_pAddButton;
    QPushButton* m_pDeleteButton;

    // 新增节点窗口
    AddNewItemWidget* m_pAddNewItemWidget;

    // 所有节点的名称
    QList<QString> m_listAllItemName;
};

#endif // NEWTREEWIDGET_H
