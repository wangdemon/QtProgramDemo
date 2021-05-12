/****************************************************************
 *
 * 作   者：王建军
 * 时   间：2021/04/19
 * 开发语言：C++
 * 开发工具：QtCreator(Qt)
 * 文   件：widget.h
 * 版   权：武汉创景可视技术有限公司
 *
 ***************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractNativeEventFilter>

class TreeWidget;
class QTreeWidgetItem;
class NewTreeWidget;

class Widget : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE;
private:
    void initialize();
    void createConnections();

    void showChartWidget();
    void hideChartWidget();

    std::string AnsiToUTF8(const char* src);

    std::wstring AnsiToUnicode(const char* src);

    std::string UnicodeToUTF8(const wchar_t* src);

    /**
    * @brief 宽字符转多字节字符
    * 针对平台采用Ansi编码方式，如果将utf-8编码的字符发送给平台，
    * 会导致平台接收乱码的字符
    * @param str发送的字符串，utf-8编码，发送给平台的utf-8编码的字符串
    * @return 返回类型是QPair<char*, int>，第一个值是ansi编码的多字节，它是
    * 平台接收的字符，第二个值是多字节的大小
    **/
    QPair<char *, int> UnicodeToAnsi(const QString& str);

    void sendMessage(QString msg);

    /**
    * @brief 获取窗口的坐标和大小
    * @param index值为1时表示树形图的坐标和大小，其值为2时表示新树形图的坐标和大小
    **/
    QList<int> getWidgetPosAndSize(int index = 1);

    void setScreenSize();

private slots:
    void slotDoubleClickedTreeItem(QString& clickedContent);
    void slotClickedTreeItem(QString& clickedContent);

    /**
    * @brief 创建新树形图
    * @param listItemText树形图节点的名称
    **/
    void slotCreateNewTree(QList<QString> listItemText);


    /**
    * @brief 给新的树形图添加新的节点
    * @param listItemText树形图节点的名称
    **/
    void slotNewAddItem(QList<QString> listItemText);

    /**
    * @brief 删除新树形图
    *  当新属性图上没有节点时，删除新的树形图
    **/
    void slotDeleteNewTree();
private:
    // 树形图
    TreeWidget* m_pTreeWidget;

    // 新的树形图
    NewTreeWidget* m_pNewTreeWidget;
};

#endif // WIDGET_H
