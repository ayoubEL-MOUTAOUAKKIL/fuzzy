#include "mainwindow.h"
#include "./Generator/expressiongenerator.h"
#include "./ui_mainwindow.h"
#include "./domain/Car.h"
#include "./domain/CarBuilder.h"
#include <iostream>
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
    powerField = ui->lineEdit_Power;
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

void MainWindow::setImage(domain::Car& car){

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

     labelCar->setText(QString::fromStdString(car.getName()));
     labelPower->setText(QString::number(car.getPower()));
     labelSeats->setText(QString::number(car.getPlaces()));
     labelCategory->setText("bidon");
     labelConsumption->setText(QString::number(car.getConsumption()));
     labelPrice->setText(QString::number(car.getPrice()));
     if (car.isManualGearbox()) {
         labelGearbox->setText("manual");
     }
     else {
         labelGearbox->setText("automatic");
     }

     titlePower->setText("Power :");
     titleSeats->setText("Seats :");
     titleCategory->setText("Category :");
     titleConsumption->setText("Consumption :");
     titleGearBox->setText("Gear Box :");
     titlePrice->setText("Price :");

     QPixmap picture(QString::fromStdString("../fuzzy/datas/pictures/"+car.getPictureName()));
     //QPixmap picture(QString::fromStdString("../fuzzy/datas/pictures/a1.jpg"));
     int w = ui->label_pic->width();
     int h = ui->label_pic->height();
     ui->label_pic->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::on_RunButton_clicked()
{
    ExpressionGenerator<float>* generator = new ExpressionGenerator<float>();
    //QLocale l(QLocale::French);
    QLineEdit* qLe = ui->lineEdit_Power;
    QString e = qLe->text();
    e.replace(",",".");
    float f = e.toFloat();
    qDebug() << f ;
    //qDebug() << QCoreApplication::applicationDirPath(); c'est ici que se trouve l'éxécutable et où j'ai mit ma seule image

    QString buffer = ui->lineEdit_Price->text();
    buffer.replace(",",".");
    float carPrice = buffer.toFloat();
    buffer = ui->lineEdit_Power->text();
    buffer.replace(",",".");
    float carPower = buffer.toFloat();
    buffer = ui->lineEdit_Consumption->text();
    buffer.replace(",",".");
    float carConsumption = buffer.toFloat();
    int carSeats = ui->lineEdit_Seats->text().toInt();
    bool carGear = ui->comboBox_GearBox->currentIndex();
    float gearValue;
    carGear?gearValue=0:gearValue=1;

    float mean = generator->generate(carPower, carSeats, 10, carConsumption, gearValue, carPrice);

    domain::CarBuilder* builder = new domain::CarBuilder();
    builder->setName("Audi A1");
    builder->setPower(carPower);
    builder->setPlaces(carSeats);
    //builder->setCategory("citadine"); faut use la CategoryFactory j'ai la flemme atm
    builder->setConsumption(carConsumption);
    builder->setPrice(carPrice);
    builder->setPictureName("a1.jpg");

    domain::Car* carz = generator->scan(mean);
    std::cout << std::endl << carz->getPrice();

    setImage(*carz);
}
