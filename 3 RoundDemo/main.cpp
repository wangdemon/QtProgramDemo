#include "widget.h"
#include "global.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Global::Instance();
    Global::SetRootPath(qApp->applicationDirPath());
    Global::CheckResource();

    Widget w;
    // w.show();

    return a.exec();
}
