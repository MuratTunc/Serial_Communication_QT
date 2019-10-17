#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QEvent>

#include "autotest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    AutoTest test(&w);
    test.start();
    return a.exec();
}
