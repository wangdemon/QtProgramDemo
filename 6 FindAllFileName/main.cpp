#include "widget.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(qApp->applicationDirPath() + "/resources/stylesheet.css");
    if(styleFile.open(QIODevice::ReadOnly)) {
        QString strStyle = styleFile.readAll();
        qApp->setStyleSheet(strStyle);
        styleFile.close();
    }

    Widget w;
    w.show();
    return a.exec();
}
