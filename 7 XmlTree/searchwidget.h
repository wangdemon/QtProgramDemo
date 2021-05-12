#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QPaintEvent;

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget* parent = nullptr);

signals:
    // 搜寻信号
    void signalSearch(const QString& str);
    // 上一个信号
    void signalPrevious();
    // 下一个信号
    void signalNext();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initialize();
    void createConnections();

private slots:
    void slotSubmitSearch();


private:
    QHBoxLayout* m_pMainHLayout;
    QLineEdit* m_pSearchLineEdit;
    QPushButton* m_pSearchButton;
    QPushButton* m_pPreviousButton;
    QPushButton* m_pNextButton;

};

#endif // SEARCHWIDGET_H
