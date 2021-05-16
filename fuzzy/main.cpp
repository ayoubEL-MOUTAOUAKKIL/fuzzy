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
    std::cout << lines.size() << std::endl;
    for (auto line = lines.begin(); line != lines.end(); ++line) {
        carRepository->save(domain::CarFactory::createCar(*line));
    }
    ExpressionGenerator<double> e;
    domain::Car* c = e.scan(179);
    //std::cout << std::endl << c->getName();
    QApplication a(argc, argv);
    MainWindow w;
    QTextStream out(stdout);
    w.addComboBoxElements();
    w.setValidators();
    w.show();
    return a.exec();
}
