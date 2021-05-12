/****************************************************************
 *
 * 作   者：王建军
 * 时   间：2021/04/19
 * 开发语言：C++
 * 开发工具：QtCreator(Qt)
 * 文   件：widget.cpp
 * 版   权：武汉创景可视技术有限公司
 *
 ***************************************************************/
#include "widget.h"

#include <QTextCodec>
#include <QDebug>

#include <windows.h>

#include <cmath>

#include "treewidget.h"
#include "newtreewidget.h"
#include "global.h"
#include "screenhelper.h"

#ifdef Q_CC_MSVC
#pragma comment(lib, "user32.lib")
#endif

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_pNewTreeWidget(nullptr)
{
    initialize();
    createConnections();
}

Widget::~Widget()
{
    delete m_pTreeWidget;
    m_pTreeWidget = nullptr;
}

bool Widget::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
    if(eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
    {
        MSG* pMsg = reinterpret_cast<MSG*>(message);
        if(pMsg->message == WM_COPYDATA)
        {
            //qDebug()<<"MainWindow windows system message WM_COPYDATA";

            COPYDATASTRUCT * p = reinterpret_cast<COPYDATASTRUCT*>(pMsg->lParam);

            QTextCodec *codec = QTextCodec::codecForName("GB2312");//也可以是GBK
            // QString str = codec->toUnicode("我是中文！");

            //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextCodec::setCodecForLocale(codec);
            QString recevice = QString::fromLocal8Bit((char *)(p->lpData)).toUtf8();


            qDebug() << "receive:" << QString(AnsiToUTF8((char *)(p->lpData)).c_str());
            if(recevice.contains("show"))
            {
                showChartWidget();
            }
            else if(recevice.contains("hide"))
            {
                hideChartWidget();
            }
            else if(recevice.contains("close"))
            {
                this->close();
            }
        }
    }
    return false;
}


void Widget::initialize()
{
    m_pTreeWidget = new TreeWidget;
    //    m_pTreeWidget->move(Global::GetTreeWidgetPos());
    //    m_pTreeWidget->resize(Global::GetTreeWidgetSize());
    m_pTreeWidget->setFixedState(Global::GetFixedState());
    QList<int> list = getWidgetPosAndSize(1);
    m_pTreeWidget->move(list.at(0), list.at(1));
    m_pTreeWidget->resize(list.at(2), list.at(3));

    if(!Global::GetFrameState()) {
        m_pTreeWidget->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        m_pTreeWidget->setAttribute(Qt::WA_TranslucentBackground);
        m_pTreeWidget->show();
    }
    m_pTreeWidget->setHidden(!Global::GetInitialzieShow());

    this->setWindowTitle("MainWidget");
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void Widget::createConnections()
{
    connect(m_pTreeWidget, &TreeWidget::signalClicked, this, &Widget::slotClickedTreeItem);
    connect(m_pTreeWidget, &TreeWidget::signalDoubleClicked, this, &Widget::slotDoubleClickedTreeItem);
    connect(m_pTreeWidget, &TreeWidget::signalCreateNewTree, this, &Widget::slotCreateNewTree);
    connect(m_pTreeWidget, &TreeWidget::signalNewItemText, this, &Widget::slotNewAddItem);        
}

void Widget::showChartWidget()
{
    bool frameState = Global::GetFrameState();
    if(frameState)
    {
        m_pTreeWidget->show();
    }
    else
    {
        m_pTreeWidget->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        m_pTreeWidget->setAttribute(Qt::WA_TranslucentBackground);
        m_pTreeWidget->show();
    }
}

void Widget::hideChartWidget()
{
    m_pTreeWidget->hide();
}

std::string Widget::AnsiToUTF8(const char *src)
{
    std::wstring unicode = AnsiToUnicode(src);
    return UnicodeToUTF8(unicode.c_str());
}

std::wstring Widget::AnsiToUnicode(const char *src)
{
    if (src == NULL || src[0] == '\0')
    {
        return L"";
    }
    std::string strSrc(src);
    int length = MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), -1, NULL, 0);
    wchar_t *buf = new wchar_t[length + 1];
    MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), -1, buf, length);
    buf[length] = L'\0';
    std::wstring dest = buf;
    delete [] buf;
    return dest;
}

std::string Widget::UnicodeToUTF8(const wchar_t *src)
{
    if (src == NULL || src[0] == '\0')
    {
        return "";
    }


    std::wstring strSrc(src);
    int length = WideCharToMultiByte(CP_UTF8, 0, strSrc.c_str(),
                                     -1, NULL, 0, NULL, FALSE);
    char *buf = new char[length + 1];
    WideCharToMultiByte(CP_UTF8, 0, strSrc.c_str(), -1, buf, length, NULL, FALSE);
    buf[length] = '\0';
    std::string dest = buf;
    delete [] buf;
    return dest;
}

QPair<char *, int> Widget::UnicodeToAnsi(const QString &str)
{
    QPair<char*, int> strPair;
    // QString str = "供热好&zwnj;1.6元/m²?月";
    wchar_t *punicode_buf = new wchar_t[str.size()+1];
    memset(punicode_buf, 0, 2 * (str.size() + 1));
    int unicode_size = str.toWCharArray(punicode_buf);
    int ansi_size = WideCharToMultiByte(CP_ACP, 0, punicode_buf, unicode_size, NULL, 0, 0, 0);
    char* pansi_buf = new char[ansi_size + 1];
    memset(pansi_buf, 0, ansi_size + 1);
    WideCharToMultiByte(CP_ACP, 0, punicode_buf, unicode_size, pansi_buf, ansi_size, 0, 0);
    // MultiByteToWideChar(CP_ACP, 0, pansi_buf, ansi_size, punicode_buf, unicode_size);
    // qDebug() << QString::fromWCharArray(punicode_buf).mid(0, str.size());
    // return pansi_buf;
    strPair.first = pansi_buf;
    strPair.second = ansi_size;
    return strPair;
}

void Widget::sendMessage(QString msg)
{
    // 发送信息
    QString sendStr = msg;
    QString peProgramName = Global::GetPEProgramName();

    // QString转wchar_t
    const wchar_t* wprogramName = reinterpret_cast<const wchar_t *>(peProgramName.utf16());
    HWND receiveHwnd = ::FindWindowW(nullptr, wprogramName);
    // 提示，没有找到接收窗口
    //    if(!IsWindow(receiveHwnd))
    //    {
    //        m_pTipLabel->setText("未找到接收窗口");
    //        return;
    //    }
    //    else
    //    {
    //        m_pTipLabel->setText("");
    //    }

    //设置COPYDATASTRUCT结构体
    COPYDATASTRUCT cds;
    cds.dwData = winId();//自定义数据

    //    QByteArray byteArray = sendStr.toUtf8();
    //    // 发送信息长度
    //    cds.cbData = byteArray.size();
    //    const char* ch = byteArray.data();
    //    cds.lpData = (PVOID)ch;
    //    // cds.lpData = (PVOID)"12345"; //测试发送数据，发送成功
    QPair<char*, int> strPair = UnicodeToAnsi(sendStr);
    cds.cbData = strPair.second;
    cds.lpData = (PVOID)strPair.first;

    //    std::string out;
    //    std::wstring in = sendStr.toStdWString();
    //    CharacterConversion::UnicodeToMulti(out, in);
    ////    std::string strAnsi = CharacterConversion::UTF8ToAnsi(sendStr.toStdString().c_str());
    //    cds.cbData = out.size();
    //    cds.lpData = (PVOID)out.c_str();

    //    cds.cbData = 1;
    //    cds.lpData = (PVOID)"1";

    HWND sender = (HWND)effectiveWinId();//SendMessage 消息发送者可以不用填写

    ::SendMessage(receiveHwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&cds));

    delete []strPair.first;
}

QList<int> Widget::getWidgetPosAndSize(int index)
{
    ScreenHelper screen;
    // qDebug() << "rect:" << screen.screenRect(0);
    QSize screenRealSize = screen.screenRect(0).size();
    QSize screenRecordSize = Global::GetScreenSize();
    QList<int> list;
    if(index == 1) {
        QPoint p1 = Global::GetTreeWidgetPos();
        QSize s1 = Global::GetTreeWidgetSize();
        if(screenRealSize != screenRecordSize) {
            int x = std::floor(float(p1.x() * screenRealSize.width()) / float(screenRecordSize.width()));
            int y = std::floor(float(p1.y() * screenRealSize.height()) / float(screenRecordSize.height()));
            int width = std::floor(float(s1.width() * screenRealSize.width()) / float(screenRecordSize.width()));
            int height = std::floor(float(s1.height() * screenRealSize.height()) / float(screenRecordSize.height()));

            list.append(x);
            list.append(y);
            list.append(width);
            list.append(height);
        }
        else {
            list.append(p1.x());
            list.append(p1.y());
            list.append(s1.width());
            list.append(s1.height());
        }

        return list;
    }
    else {
        QPoint p2 = Global::GetNewTreeWidgetPos();
        QSize s2 = Global::GetNewTreeWidgetSize();

        if(screenRealSize != screenRecordSize) {
            int x = (p2.x() * screenRealSize.width()) / screenRecordSize.width();
            int y = (p2.y() * screenRealSize.height()) / screenRecordSize.height();
            int width = (s2.width() * screenRealSize.width()) / screenRecordSize.width();
            int height = (s2.height() * screenRealSize.height()) / screenRecordSize.height();

            list.append(x);
            list.append(y);
            list.append(width);
            list.append(height);
        }
        else {
            list.append(p2.x());
            list.append(p2.y());
            list.append(s2.width());
            list.append(s2.height());
        }

        return list;
    }

}

void Widget::setScreenSize()
{
    ScreenHelper screen;
    QSize screenRealSize = screen.screenRect(0).size();
    Global::SetScreenSize(screenRealSize.width(), screenRealSize.height());
}

void Widget::slotDoubleClickedTreeItem(QString &clickedContent)
{
    // 更新新树形图节点状态
    if(m_pNewTreeWidget != nullptr) {
        QString sendContent = clickedContent;
        QStringList listSendContent = sendContent.split("/");
        if(listSendContent.count() == 3) {
            QString itemText = listSendContent.at(1);
            int state = m_pTreeWidget->getTreeWigetItemState(itemText);
            m_pNewTreeWidget->updateItemState(itemText, state);
        }
    }
    sendMessage(clickedContent);
}

void Widget::slotClickedTreeItem(QString &clickedContent)
{
    // 更新新树形图节点状态
    if(m_pNewTreeWidget != nullptr) {
        QString sendContent = clickedContent;
        QStringList listSendContent = sendContent.split("/");
        if(listSendContent.count() == 3) {
            QString itemText = listSendContent.at(1);
            int state = m_pTreeWidget->getTreeWigetItemState(itemText);
            m_pNewTreeWidget->updateItemState(itemText, state);
        }
    }
    sendMessage(clickedContent);
}

void Widget::slotCreateNewTree(QList<QString> listItemText)
{
    if(m_pNewTreeWidget == nullptr) {
        m_pNewTreeWidget = new NewTreeWidget;
        connect(m_pNewTreeWidget, &NewTreeWidget::signalNoItem, this, &Widget::slotDeleteNewTree);
        for (int i = 0; i < listItemText.size(); i++) {
            m_pNewTreeWidget->addItem(listItemText.at(i), m_pTreeWidget->getTreeWigetItemState(listItemText.at(i)));
        }

        QList<int> list = getWidgetPosAndSize(2);
        m_pNewTreeWidget->move(list.at(0), list.at(1));
        m_pNewTreeWidget->resize(list.at(2), list.at(3));
        m_pNewTreeWidget->show();
        m_pTreeWidget->setNewTreeState(true);

        connect(m_pNewTreeWidget, &NewTreeWidget::signalUpdateItemState, m_pTreeWidget, &TreeWidget::slotUpdateItemState);
        connect(m_pNewTreeWidget, &NewTreeWidget::signalNewAddItem, m_pTreeWidget, &TreeWidget::slotNewAddItem);
        setScreenSize();

        m_pNewTreeWidget->setAllItemName(m_pTreeWidget->getAllItemName());
    }
}

void Widget::slotNewAddItem(QList<QString> listItemText)
{
    // m_pNewTreeWidget->setNewItemTexts(listItemText);
    QList<QString> list = listItemText;
    for (int i = 0; i < list.size(); i++) {
        m_pNewTreeWidget->addItem(list.at(i), m_pTreeWidget->getTreeWigetItemState(list.at(i)));
    }
    m_pNewTreeWidget->setAllItemName(m_pTreeWidget->getAllItemName());
}

void Widget::slotDeleteNewTree()
{
    disconnect(m_pNewTreeWidget, &NewTreeWidget::signalNoItem, this, &Widget::slotDeleteNewTree);

    delete m_pNewTreeWidget;
    m_pNewTreeWidget = nullptr;
    m_pTreeWidget->setNewTreeState(false);
}


