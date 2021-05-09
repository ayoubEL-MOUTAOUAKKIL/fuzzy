#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), qP(new QLineEdit()),qC(new QLineEdit()),qS(new QLineEdit()),qPr(new QLineEdit())
{
    ui->setupUi(this);
    qP = ui->lineEdit_Power;
    qC= ui->lineEdit_Consumption;
    qS= ui->lineEdit_Seats;
    qPr= ui->lineEdit_Price;
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi() const{
    return ui;
}

void MainWindow::addComboBoxElements(){

    QComboBox* qC = ui->comboBox_Category;
    qC->addItem("city-run");
    qC->addItem("SUV");
    qC->addItem("electric");
    qC->addItem("sport");

    QComboBox* qG = ui->comboBox_GearBox;
    qG->addItem("manual");
    qG->addItem("automatic");


}

void MainWindow::setValidators(){
    QDoubleValidator* qV = new QDoubleValidator(0.0, 1000.0, 2);
    qV->setNotation(QDoubleValidator::StandardNotation);
    qP->setValidator(qV);

    QDoubleValidator* qVc = new QDoubleValidator(0.0, 10.0, 2);
    qVc->setNotation(QDoubleValidator::StandardNotation);
    qC->setValidator(qVc);

    QIntValidator* qVs = new QIntValidator(0, 9);
    qS->setValidator(qVs);

    QDoubleValidator* qVp = new QDoubleValidator(0.0, 10000.0, 2);
    qVp->setNotation(QDoubleValidator::StandardNotation);
    qPr->setValidator(qVp);

}

void MainWindow::setImage(QString name,QString power,QString seats, QString category,QString consumption,QString gearbox,QString price,QString pic){
     QLabel* qL = ui->Label_Car;
     QLabel* qP = ui->carPower;
     QLabel* qS = ui->carSeats;
     QLabel* qC = ui->carCategory;
     QLabel* qCp = ui->carConsumption;
     QLabel* qG = ui->carGearBox;
     QLabel* qPr = ui->carPrice;
     QLabel* qP1 = ui->titlePower;
     QLabel* qS1 = ui->titleSeats;
     QLabel* qC1 = ui->titleCategory;
     QLabel* qCp1 = ui->titleConsumption;
     QLabel* qG1 = ui->title_GearBox;
     QLabel* qPr1 = ui->titlePrice;

     qL->setText(name);
     qP->setText(power);
     qS->setText(seats);
     qC->setText(category);
     qCp->setText(consumption);
     qG->setText(gearbox);
     qPr->setText(price);
     qP1->setText("Power :");
     qS1->setText("Seats :");
     qC1->setText("Category :");
     qCp1->setText("Consumption :");
     qG1->setText("Gear Box :");
     qPr1->setText("Price :");

     QPixmap picture(pic);
     int w = ui->label_pic->width();
     int h = ui->label_pic->height();
     ui->label_pic->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::on_RunButton_clicked()
{
    //QLocale l(QLocale::French);
    QLineEdit* qLe = ui->lineEdit_Power;
    QString e = qLe->text();
    e.replace(",",".");
    float f = e.toFloat();
    qDebug() << f ;
    //qDebug() << QCoreApplication::applicationDirPath(); c'est ici que se trouve l'éxécutable et où j'ai mit ma seule image
    setImage("Audi A1","82","5","citadine","5,7","manuelle","21500","../fuzzy/datas/pictures/a1.jpg");
}
