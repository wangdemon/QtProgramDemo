#ifndef DROPTABLEWIDGET_H
#define DROPTABLEWIDGET_H

#include <QTableWidget>

class DropTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit DropTableWidget(QWidget* parent = nullptr);
    ~DropTableWidget();

    QPoint getMousePos();
    bool getRightMouseState();
    void setRightMouseState(bool state);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint m_mousePos;
    bool m_bRightState;

};

#endif // DROPTABLEWIDGET_H
