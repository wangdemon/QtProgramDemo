#ifndef DRAGTREEWIDGET_H
#define DRAGTREEWIDGET_H

#include <QTreeWidget>

class QDragEnterEvent;
class QDropEvent;

class DragTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DragTreeWidget(QWidget* parent = nullptr);

    void setNewTreeState(bool state);

signals:
    void signalCreateNewTree(QList<QString> listItemText);
    void signalNewItemText(QList<QString> listItemText);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;
//    void mouseMoveEvent(QMouseEvent* event) override;


    bool eventFilter(QObject *target, QEvent *event) override;

private:
    QList<QString> getSelectedItemsText();

private:
    // 创建新树形图状态，其值为真时表示已经创建，反之没有创建
    bool m_bNewTreeState;

};

#endif // DRAGTREEWIDGET_H
