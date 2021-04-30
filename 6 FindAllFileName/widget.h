#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QTextEdit;
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void initialzie();
    void createConnections();

    void findAllFileName();

    void getFileFilterParameter();
    void getShowPathParameter();
    void getShowReturnParamter();
    void getFilePathParameter();
    void getShowFileSuffixParameter();
    void getPrefixParameter();

private slots:
    void slotOpenPath();
    void slotSubmit();


private:
    QVBoxLayout* m_pMainVLayout;

    QHBoxLayout* m_pTextAndParameterHLayout;

    QTextEdit* m_pTextEdit;

    QHBoxLayout* m_pPathHLayout;
    QLabel* m_pPathLabel;
    QLineEdit* m_pPathLineEdit;
    QPushButton* m_pOpenPathButton;
    QPushButton* m_pSubmitButton;

    QString m_sDirPath;

    // 参数设置窗口
    QWidget* m_pParameterWidget;
    QVBoxLayout* m_pParameterMainVLayout;

    QHBoxLayout* m_pParameterFilterLayout;
    QLabel* m_pParameterFilterLabel;
    QLineEdit* m_pParameterFilterLineEdit;

    QHBoxLayout* m_pShowPathLayout;
    QLabel* m_pShowPathLabel;
    QComboBox* m_pShowPathComboBox;

    QHBoxLayout* m_pShowReturnLayout;
    QLabel* m_pShowReturnLabel;
    QComboBox* m_pShowReturnComboBox;

    QHBoxLayout* m_pShowSuffixLayout;
    QLabel* m_pShowSuffixLabel;
    QComboBox* m_pShowSuffixComboBox;

    QHBoxLayout* m_pShowPrefixLayout;
    QLabel* m_pPrefixLabel;
    QLineEdit* m_pPrefixLineEdit;

    // 是否显示文件路径，0表示不显示，1表示显示
    int m_iShowPath;

    // 文件过滤器
    QStringList m_slistFilter;

    // 显示文件时候换行，0表示不换行，1表示换行
    int m_iReturnLine;

    // 显示文件后缀名, 0表示不显示， 1表示显示
    int m_iShowSuffix;

    QString m_sPrefix;
};
#endif // WIDGET_H
