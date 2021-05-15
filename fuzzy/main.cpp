#include "./tests/tests.h"
#include "repository/csv/CSVParser.h"
#include "repository/car/CarRepository.h"
#include "repository/car/InMemoryCarRepository.h"
#include "domain/Car.h"
#include "domain/CarBuilder.h"
#include "domain/categorie/CategoryFactory.h"
#include "domain/CarFactory.h"
#include "generator/Expressiongenerator.h"
#include "mainwindow.h"
#include "controller/CarController.h"
#include "fuzzy/is.h"
#include <QApplication>
#include <string>
#include <vector>
#include <QDebug>
#include <QString>
#include <iostream>

int main(int argc, char** argv) {
    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
    repository::CSVParser parser("../fuzzy/datas/cars.csv", ',');
    std::vector<std::vector<std::string>> lines = parser.getLines();
    for (auto line : lines) {
        carRepository->save(domain::CarFactory::createCar(line));
    }

    ExpressionGenerator<double> e;
    e.scan();
    CarController<double>* carController = new CarController<double>();
    std::vector<double> prices;
    fuzzy::isTriangle<double> issou(0,0,0);
    for (auto car : carRepository->getAllCars()) {
        prices.push_back(car.getPrice());
        std::cout << car.getPrice() << std::endl;
    }
   fuzzy::is<double> iss = carController->createIs(&issou ,prices);
   /* QApplication a(argc, argv);
    MainWindow w;
    QTextStream out(stdout);
    w.addComboBoxElements();
    w.setValidators();
    w.show();
    return a.exec();*/
    return 0;
}
