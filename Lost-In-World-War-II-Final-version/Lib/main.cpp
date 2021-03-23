#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow Window(nullptr);
    Window.show();
    return a.exec();
}

