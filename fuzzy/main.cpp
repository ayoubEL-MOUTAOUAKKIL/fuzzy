#include "mainwindow.h"

#include "./tests/tests.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.addComboBoxElements();
    w.show();
    return a.exec();
}
