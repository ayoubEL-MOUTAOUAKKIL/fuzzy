#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "Car.h"
#include <vector>

namespace domain {
	class CarFactory
	{
	public:
		CarFactory() = default;
		virtual ~CarFactory() = default;
		static Car& createCar(const std::vector<std::string> _csvLine);
	};
}

#endif // !CAR