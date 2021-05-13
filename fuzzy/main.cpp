#include "./tests/tests.h"
#include "repository/csv/CSVParser.h"
#include "repository/car/CarRepository.h"
#include "repository/car/InMemoryCarRepository.h"
#include "domain/Car.h"
#include "domain/CarBuilder.h"
#include "domain/categorie/CategoryFactory.h"
#include "domain/CarFactory.h"
#include "Generator/expressiongenerator.h"
#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    repository::CarRepository* carRepository = new repository::InMemoryCarRepository();
    repository::CSVParser parser("./datas/cars.csv", ',');
    std::vector<std::vector<std::string>> lines = parser.getLines();
    for (auto line = lines.begin(); line != lines.end(); ++line) {
        carRepository->save(domain::CarFactory::createCar((*line)));
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.addComboBoxElements();
    w.setValidators();
    w.show();
    return a.exec();
}
