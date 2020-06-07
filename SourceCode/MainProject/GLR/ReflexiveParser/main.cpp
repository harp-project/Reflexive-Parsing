#include "mainwindow.h"
#include "appmanager.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppManager manager;
    return a.exec();
}

