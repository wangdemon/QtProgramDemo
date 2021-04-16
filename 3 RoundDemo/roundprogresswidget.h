#ifndef ROUNDPROGRESSWIDGET_H
#define ROUNDPROGRESSWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPoint>

#include <vector>

class QHBoxLayout;
class ProgressPie;
class QResizeEvent;
class QMoveEvent;

class RoundProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoundProgressWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void moveEvent(QMoveEvent *event);

private slots:
    void slotUpdateValue();

private:
    std::vector<int> generateDiffNumber(int min,int max,int num);

private:

    QHBoxLayout* m_pPieHLayout;
    ProgressPie* m_pPie1;
    ProgressPie* m_pPie2;
    ProgressPie* m_pPie3;
    QTimer m_timer;

    bool m_bMove;
    QPoint m_spanPoint;
};

#endif // ROUNDPROGRESSWIDGET_H
