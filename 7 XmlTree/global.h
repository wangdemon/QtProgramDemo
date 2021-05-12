#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMutex>
#include <QMutexLocker>
#include <QPoint>
#include <QSize>
#include <QColor>

class QSettings;

class Global
{
public:
    static Global* Instance();

    /**
    *@brief 检查资源目录或者文件是否存在
    **/
    static void CheckResource();

    static QString GetIniPath();

    static QString GetRootPath();

    static void SetRootPath(const QString& path);

    static QString GetPEProgramName();
    static QString GetChartProgramName();
    static bool GetFrameState();
    static bool GetFixedState();
    static bool GetInitialzieShow();

    static void SetTreeWidgetPos(QPoint pos);
    static void SetTreeWidgetSize(QSize size);
    static QPoint GetTreeWidgetPos();
    static QSize GetTreeWidgetSize();

    static void SetNewTreeWidgetPos(QPoint pos);
    static void SetNewTreeWidgetSize(QSize size);
    static QPoint GetNewTreeWidgetPos();
    static QSize GetNewTreeWidgetSize();

    static QColor GetBgColor();
    static QColor GetHoverBgColor();
    static QColor GetCheckedBgColor();
    static QColor GetTextColor();
    static QColor GetHoverTextColor();
    static QColor GetCheckedTextColor();
    static QColor GetLineColor();

    static bool GetBkImageState();
    static QString GetBkImagePath();
    static float GetBkImageOpacity();


    static QString GetImagePath();

    static bool GetExpandFirstSubItemState();
    static bool GetHideRootItemState();

    static QSize GetScreenSize();
    static void SetScreenSize(int width, int height);

    static QString GetNewAddItemText();

    static QString GetStyleSheetStr();

protected:
    Global();

private:
    static Global *m_pInstance;
    static QMutex m_mutex;

    static QString RootPath;

    static QPoint TreeWidgetPos;
    static QSize TreeWidgetSize;

    static QPoint NewTreeWidgetPos;
    static QSize NewTreeWidgetSize;

    static bool FrameState;
    static bool FixedState;
    static bool InitializeShow;

    static QString PEProgramName;
    static QString ChartProgramName;

    static QColor BgColor;
    static QColor HoverBgColor;
    static QColor CheckedBgColor;
    static QColor TextColor;
    static QColor HoverTextColor;
    static QColor CheckedTextColor;
    static QColor LineColor;

    static bool BkImageState;
    static QString BkImagePath;
    static float BkImageOpacity;

    static QString ImagePath;

    static QSettings* setting;

    static bool ExpandFirstSubItemState;
    static bool HideRootItemState;

    // 屏幕分辨率
    static int ScreenWidth;
    static int ScreenHeight;

    // 新增节点文本名称
    static QString NewAddItemText;

    // GC类
    // 程序退出后，该类的析构函数释放单例内存
    class GC
    {
    public :
        ~GC()
        {
            if(m_pInstance != nullptr )
            {
                delete m_pInstance;
                m_pInstance = nullptr ;
            }

            if(setting != nullptr)
            {
                delete setting;
                setting = nullptr;
            }
        }
    };

    static GC gc;
};

#endif // GLOBAL_H
