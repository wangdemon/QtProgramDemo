#ifndef DROPTREEWIDGET_H
#define DROPTREEWIDGET_H

#include <QTreeWidget>
#include <QPoint>

class QMouseEvent;


class DropTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DropTreeWidget(QWidget* parent = nullptr);
    ~DropTreeWidget();

   QPoint getMousePos();
   bool getRightMouseState();
   void setRightMouseState(bool state);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void initialize();
    void createConnections();

private slots:
//    void slotDeleteItem();

//    void slotItemClicked(QTreeWidgetItem *item, int column);
private:
    QPoint m_mousePos;
    bool m_bRightState;
};

#endif // DROPTREEWIDGET_H
