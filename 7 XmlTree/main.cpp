/****************************************************************
 *
 * 作   者：王建军
 * 时   间：2021/04/19
 * 开发语言：C++
 * 开发工具：QtCreator(Qt)
 * 文   件：main.cpp
 * 版   权：武汉创景可视技术有限公司
 *
 ***************************************************************/
#include "widget.h"
#include "global.h"
#include <QApplication>
#include <QSharedMemory>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 防止程序被多次启动
    QSharedMemory shared("chart_program");
    // 共享内存被占用则直接返回
    if(shared.attach())
    {
        return 0;
    }
    //共享内存没有被占用则创建UI
    shared.create(1);

    Global::Instance();
    Global::SetRootPath(qApp->applicationDirPath());
    Global::CheckResource();

    Widget w;
    w.setWindowTitle(Global::GetChartProgramName());
    //w.show();

    qApp->setStyleSheet(Global::GetStyleSheetStr());

    w.show();
    w.hide();

    a.installNativeEventFilter(&w);
    return a.exec();
}
