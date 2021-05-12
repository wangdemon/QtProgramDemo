/****************************************************************
 *
 * 作   者：王建军
 * 时   间：2021/04/19
 * 开发语言：C++
 * 开发工具：QtCreator(Qt)
 * 文   件：screenhelper.cpp
 * 版   权：武汉创景可视技术有限公司
 *
 ***************************************************************/
#include "screenhelper.h"

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#include <QApplication>
#include <QDesktopWidget>
#else
#include <QGuiApplication>
#include <QScreen>
#endif

ScreenHelper::ScreenHelper()
{
    m_screenRects.clear();

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    QDesktopWidget *desktop = QApplication::desktop();
    int screenCnt = desktop->screenCount();

    for (int i = 0; i < screenCnt; i++) {
        QRect rect = desktop->availableGeometry(i);
        m_screenRects.append(rect);
    }
#else
    QList<QScreen *> screenList = QGuiApplication::screens();
    foreach (QScreen *screen, screenList) {
        m_screenRects.append(screen->availableGeometry());
    }
#endif
}

int ScreenHelper::currentScreen(const int x)
{
    int width;

    for (int i = 0; i < m_screenRects.count(); i++) {
        width = m_screenRects.at(i).x() + m_screenRects.at(i).width();

        if (x > width) {
            continue;
        }
        return i;
    }

    return 0;
}

QRect ScreenHelper::screenRect(const int current)
{
    if (current >= m_screenRects.count()) {
        return m_screenRects.at(0);
    } else {
        return m_screenRects.at(current);
    }
}

QRect ScreenHelper::normalRect()
{
    QRect geom;
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    geom = QApplication::desktop()->availableGeometry();
#else
    geom = QGuiApplication::primaryScreen()->availableGeometry();
#endif
    return QRect(geom.x() + 100, geom.y() + 100,
                 2 * geom.width() / 3, 2 * geom.height() / 3);
}
