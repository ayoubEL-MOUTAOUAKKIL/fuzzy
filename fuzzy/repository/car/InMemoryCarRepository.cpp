#include "InMemoryCarRepository.h"

#include <iostream>

repository::InMemoryCarRepository::~InMemoryCarRepository()
{
	cars.clear();
}

void repository::InMemoryCarRepository::save(const domain::Car& car) 
{
	cars.push_back(car);
}