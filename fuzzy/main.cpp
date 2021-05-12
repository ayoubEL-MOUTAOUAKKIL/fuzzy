#include "./tests/tests.h"
#include "repository/csv/CSVParser.h"
#include "repository/car/CarRepository.h"
#include "repository/car/InMemoryCarRepository.h"
#include "domain/Car.h"
#include "domain/CarBuilder.h"
#include "domain/categorie/CategoryFactory.h"
#include "domain/CarFactory.h"
#include <string>
#include <vector>

int main() {
	repository::CarRepository* carRepository = new repository::InMemoryCarRepository();
	repository::CSVParser parser(std::string("./datas/cars.csv"), ',');
	std::vector<std::vector<std::string>> lines = parser.getLines();
	for (auto line = lines.begin(); line != lines.end(); ++line) {
		carRepository->save(domain::CarFactory::createCar((*line)));
	}
	tests();
	return 0;
}