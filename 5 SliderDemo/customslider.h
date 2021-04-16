#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>

class HandleWidget;

class QMouseEvent;
class QResizeEvent;
class QWheelEvent;

class CustomSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSlider(QWidget* parent = nullptr);

    void setRange(int min, int max);

    void showDial(bool state = true);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event);

    void wheelEvent(QWheelEvent *event);

private:
    void initialize();
    void createConnections();

    void updatePosition();

    void drawDial(QPainter& painter);

private:
    int m_iMin;
    int m_iMax;
    bool m_bShowDial;
    int m_iRadius;
    int m_iEdgeLength;

    int m_iX;
    int m_iMouseX;

    QColor m_dialColor;

    HandleWidget* m_pHandleWidget;

    bool m_bMove;
};

#endif // CUSTOMSLIDER_H
