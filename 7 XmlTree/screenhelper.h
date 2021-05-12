/****************************************************************
 *
 * 作   者：王建军
 * 时   间：2021/04/19
 * 开发语言：C++
 * 开发工具：QtCreator(Qt)
 * 文   件：screenhelper.h
 * 版   权：武汉创景可视技术有限公司
 *
 ***************************************************************/
#ifndef SCREENHELPER_H
#define SCREENHELPER_H

#include <QRect>
#include <QList>

/* on screen display */
class ScreenHelper
{
public:
    ScreenHelper();

    int currentScreen(const int x);
    QRect screenRect(const int current);

    static QRect normalRect();

private:
    QList<QRect> m_screenRects;
};

#endif // SCREENHELPER_H
