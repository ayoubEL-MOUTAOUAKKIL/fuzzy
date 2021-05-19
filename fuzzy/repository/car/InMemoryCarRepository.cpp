#include "InMemoryCarRepository.h"

#include <iostream>
#include <algorithm>

namespace repository {
    InMemoryCarRepository* InMemoryCarRepository::instance = nullptr;

    InMemoryCarRepository* InMemoryCarRepository::getInstance(){
        if (!instance){
            instance = new InMemoryCarRepository();
        }
        return instance;
    };

    InMemoryCarRepository::~InMemoryCarRepository()
    {
        cars.clear();
    }

    void InMemoryCarRepository::save(const domain::Car& car)
    {
        cars.push_back(car);
    }

    std::vector<domain::Car> InMemoryCarRepository::getAllCars() const {
        std::vector<domain::Car> allCars;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allCars.push_back(*car);
        }
        return allCars;
    }

    std::vector<double> InMemoryCarRepository::getAllPower() const {
        std::vector<double> allPowers;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allPowers.push_back((*car).getPower());
        }
        return allPowers;
    }

    std::vector<double> InMemoryCarRepository::getAllSeats() const {
        std::vector<double> allSeats;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allSeats.push_back((*car).getPlaces());
        }
        return allSeats;
    }

    std::vector<double> InMemoryCarRepository::getAllCategory() const {
        std::vector<double> allCategory;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allCategory.push_back((*car).getCategory().getType());
        }
        return allCategory;
    }

    std::vector<double> InMemoryCarRepository::getAllConsumption() const {
        std::vector<double> allConsumption;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allConsumption.push_back((*car).getConsumption());
        }
        return allConsumption;
    }

    std::vector<double> InMemoryCarRepository::getAllPrices() const {
        std::vector<double> allPrices;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allPrices.push_back((*car).getPrice());
        }
        return allPrices;
    }

    std::vector<double> InMemoryCarRepository::getAllGear() const {
        std::vector<double> allGears;
        for (auto car = cars.begin(); car != cars.end(); ++car){
            allGears.push_back((*car).isManualGearbox() ? 1 : 0);
        }
        return allGears;
    }
}
