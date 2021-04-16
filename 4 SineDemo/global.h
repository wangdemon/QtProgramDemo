#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMutex>
#include <QMutexLocker>
#include <QPoint>
#include <QSize>

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

    static void SetRoundProgressPos(QPoint pos);
    static void SetRountProgressSize(QSize size);
    static QPoint GetRoundProgressPos();
    static QSize GetRountProgressSize();

    static void SetRoseChartPos(QPoint pos);
    static void SetRoseChartSize(QSize size);
    static QPoint GetRoseChartPos();
    static QSize GetRoseChartSize();

    static void SetSineChartPos(QPoint pos);
    static void SetSineChartSize(QSize size);
    static QPoint GetSineChartPos();
    static QSize GetSineChartSize();

    static void SetBarChartPos(QPoint pos);
    static void SetBarChartSize(QSize size);
    static QPoint GetBarChartPos();
    static QSize GetBarChartSize();

protected:
    Global();

private:
    static Global *m_pInstance;
    static QMutex m_mutex;

    static QString RootPath;

    static QPoint RoundProgressPos;
    static QSize RountProgressSize;

    static QPoint RoseChartPos;
    static QSize RoseChartSize;

    static QPoint SineChartPos;
    static QSize SineChartSize;

    static QPoint BarChartPos;
    static QSize BarChartSize;

    static bool FrameState;

    static QString PEProgramName;
    static QString ChartProgramName;

    static QSettings* setting;

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
