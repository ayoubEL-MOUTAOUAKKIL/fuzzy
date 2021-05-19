#include "./tests/tests.h"
#include "repository/csv/CSVParser.h"
#include "repository/car/CarRepository.h"
#include "repository/car/InMemoryCarRepository.h"
#include "domain/Car.h"
#include "domain/CarBuilder.h"
#include "domain/categorie/CategoryFactory.h"
#include "domain/CarFactory.h"
#include "generator/expressiongenerator.h"
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
    QApplication a(argc, argv);
    MainWindow w;
    QTextStream out(stdout);
    w.addComboBoxElements();
    w.setValidators();
    w.show();

    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
    repository::CSVParser parser("../fuzzy/datas/cars.csv", ',');
    std::vector<std::vector<std::string>> lines = parser.getLines();
    for (auto& line : lines) {
        carRepository->save(domain::CarFactory::createCar(line));
    }
    std::cout << carRepository->getAllCars().size();

//    ExpressionGenerator<double>* e = new ExpressionGenerator<double>(new CarController<double>());
//    e->scan(700);
    return a.exec();
//    return 0;
}
