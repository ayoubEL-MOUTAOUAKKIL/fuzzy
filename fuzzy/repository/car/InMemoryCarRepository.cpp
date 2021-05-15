#include "InMemoryCarRepository.h"

#include <iostream>

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
}
