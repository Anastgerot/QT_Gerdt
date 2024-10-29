#include "mainwindow.h"
#include <QApplication>
#include <QStyleHints>
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if QT_VERSION >= 0x060800
    a.styleHints()->setColorScheme(Qt::ColorScheme::Light);
#endif
    MainWindow w;
    w.show();
    return a.exec();
}

