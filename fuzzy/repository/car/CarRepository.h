#ifndef CARREPOSITORY_H
#define CARREPOSITORY_H

#include "../../domain/Car.h"

namespace repository {
	class CarRepository
	{
	public:
		CarRepository() = default;
		virtual ~CarRepository() = default;
		virtual void save(const domain::Car&) = 0;
	};
}
#endif // !CARREPOSITORY_H
