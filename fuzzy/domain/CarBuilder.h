#ifndef CARBUILDER_H
#define CARBUILDER_H

#include "Car.h"
#include "categorie/Category.h"

namespace domain {
	class CarBuilder {
	private:
		Car& car;
	public:
		virtual ~CarBuilder() = default;
		CarBuilder(): car(*new domain::Car()) {};
		CarBuilder& setName(const std::string);
		CarBuilder& setPower(const float);
        CarBuilder& setPlaces(const int);
        CarBuilder& setCategory(domain::Category*);
		CarBuilder& setPrice(const float);
		CarBuilder& withManualGearbox(const bool);
		CarBuilder& setConsumption(const float);
		CarBuilder& setPictureName(const std::string);
		Car& build();
	};
}
#endif // !CARBUILDER_H
