#ifndef CARREPOSITORY_H
#define CARREPOSITORY_H

#include "../../domain/Car.h"
#include <vector>

namespace repository {
	class CarRepository
	{
	public:
		CarRepository() = default;
		virtual ~CarRepository() = default;
		virtual void save(const domain::Car&) = 0;
        virtual std::vector<domain::Car> getAllCars() const = 0;
	};
}
#endif // !CARREPOSITORY_H
