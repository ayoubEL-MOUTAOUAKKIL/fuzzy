#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi() const{
    return ui;
}

void MainWindow::addComboBoxElements(){
    QComboBox* qP = ui->comboBox_Power;
    qP->addItem("weak");
    qP->addItem("average");
    qP->addItem("powerful");

    QComboBox* qS = ui->comboBox_Seats;
    qS->addItem("2");
    qS->addItem("5");

    QComboBox* qC = ui->comboBox_Category;
    qC->addItem("city-run");
    qC->addItem("SUV");

    QComboBox* qCp = ui->comboBox_Consumption;
    qCp->addItem("low");
    qCp->addItem("medium");
     qCp->addItem("high");

    QComboBox* qG = ui->comboBox_GearBox;
    qG->addItem("manual");
    qG->addItem("automatic");

    QComboBox* qPr = ui->comboBox_Prices;
    qPr->addItem("cheap");
    qPr->addItem("average");
    qPr->addItem("expensive");

}

void MainWindow::on_RunButton_clicked()
{
    QLabel* qL = ui->Label_Car;
    qL->setText("Test vehicule");
}
