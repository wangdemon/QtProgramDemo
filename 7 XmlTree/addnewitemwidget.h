#ifndef ADDNEWITEMWIDGET_H
#define ADDNEWITEMWIDGET_H

#include <QWidget>
#include <QTimer>

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QComboBox;
class QTableWidget;
class QTableWidgetItem;
class QLabel;

class AddNewItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddNewItemWidget(QWidget* parent = nullptr);

    void setNum(int num);

    int getNum();
    QString getName();
    int getState();

    void setTipText(const QString& text, int type = 0);
    void closeTip();

    void cleanData();

signals:
    void signalSubmitAddNew();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    void initialize();
    void createConnections();

private slots:
    void slotCancel();

    void slotTip();

private:
    QVBoxLayout* m_pMainVLayout;

    QTableWidget* m_pParameterTableWidget;
    QTableWidgetItem* m_pNumItem;
    QTableWidgetItem* m_pNameItem;
    QComboBox* m_pStateComboBox;

    QLabel* m_pTipLabel;

    QHBoxLayout* m_pButtonHLayout;
    QPushButton* m_pSubmitButton;
    QPushButton* m_pCancelButton;

    bool m_bMove;
    QPoint m_spanPoint;
    bool m_bFixed;

    QTimer m_timer;
    // 提示文本
    QString m_sTipText;
    // 提示类型, 0表示没有输入节点名称, 1表示重复节点
    int m_iTipType;
};

#endif // ADDNEWITEMWIDGET_H
