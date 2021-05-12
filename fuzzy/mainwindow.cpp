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
    , ui(new Ui::MainWindow),
      powerField(new QLineEdit()),
      consumptionField(new QLineEdit()),
      seatsField(new QLineEdit()),
      priceField(new QLineEdit())
{
    ui->setupUi(this);
    priceField = ui->lineEdit_Power;
    consumptionField = ui->lineEdit_Consumption;
    seatsField = ui->lineEdit_Seats;
    priceField = ui->lineEdit_Price;
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi() const{
    return ui;
}

void MainWindow::addComboBoxElements(){

    QComboBox* categorySelector = ui->comboBox_Category;
    categorySelector->addItem("city-run");
    categorySelector->addItem("SUV");
    categorySelector->addItem("electric");
    categorySelector->addItem("sport");

    QComboBox* gearboxSelector = ui->comboBox_GearBox;
    gearboxSelector->addItem("manual");
    gearboxSelector->addItem("automatic");
}

void MainWindow::setValidators(){
    QDoubleValidator* powerValidator = new QDoubleValidator(0.0, 9999.0, 2);
    powerValidator->setNotation(QDoubleValidator::StandardNotation);
    powerField->setValidator(powerValidator);

    QDoubleValidator* consumptionValidator = new QDoubleValidator(0.0, 99.0, 2);
    consumptionValidator->setNotation(QDoubleValidator::StandardNotation);
    consumptionField->setValidator(consumptionValidator);

    QIntValidator* seatsValidator = new QIntValidator(0, 9);
    seatsField->setValidator(seatsValidator);

    QDoubleValidator* priceValidator = new QDoubleValidator(0.0, 99999999.0, 2);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    priceField->setValidator(priceValidator);
}

void MainWindow::setImage(QString name,QString power,QString seats, QString category,QString consumption,QString gearbox,QString price,QString pic){

     QLabel* titlePower = ui->titlePower;
     QLabel* titleSeats = ui->titleSeats;
     QLabel* titleCategory = ui->titleCategory;
     QLabel* titleConsumption = ui->titleConsumption;
     QLabel* titleGearBox = ui->title_GearBox;
     QLabel* titlePrice = ui->titlePrice;

     QLabel* labelCar = ui->Label_Car;
     QLabel* labelPower = ui->carPower;
     QLabel* labelSeats = ui->carSeats;
     QLabel* labelCategory = ui->carCategory;
     QLabel* labelConsumption = ui->carConsumption;
     QLabel* labelGearbox = ui->carGearBox;
     QLabel* labelPrice = ui->carPrice;

     labelCar->setText(name);
     labelPower->setText(power);
     labelSeats->setText(seats);
     labelCategory->setText(category);
     labelConsumption->setText(consumption);
     labelGearbox->setText(gearbox);
     labelPrice->setText(price);

     titlePower->setText("Power :");
     titleSeats->setText("Seats :");
     titleCategory->setText("Category :");
     titleConsumption->setText("Consumption :");
     titleGearBox->setText("Gear Box :");
     titlePrice->setText("Price :");

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
