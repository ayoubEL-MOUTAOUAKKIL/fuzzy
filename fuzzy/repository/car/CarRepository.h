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
        virtual std::vector<double> getAllPower() const = 0;
        virtual std::vector<double> getAllSeats() const = 0;
        virtual std::vector<double> getAllCategory() const = 0;
        virtual std::vector<double> getAllConsumption() const = 0;
        virtual std::vector<double> getAllPrices() const = 0;
        virtual std::vector<double> getAllGear() const = 0;
        virtual std::string getCategoryName(const domain::Category*) const = 0;
	};
}
#endif // !CARREPOSITORY_H
