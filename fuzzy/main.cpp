#include "mainwindow.h"
#include <iostream>
#include "./tests/tests.h"
#include "./Generator/expressiongenerator.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    ExpressionGenerator<double> v;
    qDebug() << v.generate(1,1,1,1,1,1);
    qDebug() << v.generate(0,0,0,0,0,0);
    qDebug() << v.generate(1,1,0.5,1,1,1);
    qDebug() << v.generate(10,1,20,1,20,1);
    QApplication a(argc, argv);
    MainWindow w;
    w.addComboBoxElements();
    w.setValidators();
    w.show();
    return a.exec();
}
