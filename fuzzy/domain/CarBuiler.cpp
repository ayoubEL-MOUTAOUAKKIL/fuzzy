#include "CarBuilder.h"

namespace domain {
	CarBuilder& CarBuilder::setName(const std::string _name)
	{
		car.setName(_name);
		return *this;
	}

	CarBuilder& domain::CarBuilder::setPower(const float _power)
	{
		car.setPower(_power);
		return *this;
	}

    CarBuilder& domain::CarBuilder::setPlaces(const int _places)
	{
		car.setPlaces(_places);
		return *this;
	}

    CarBuilder& domain::CarBuilder::setCategory(domain::Category* _category)
	{
        car.setCategory(_category);
		return *this;
	}

	CarBuilder& domain::CarBuilder::setPrice(const float _price)
	{
		car.setPrice(_price);
		return *this;
	}

	CarBuilder& domain::CarBuilder::withManualGearbox(const bool _isManual)
	{
		car.withManualGearbox(_isManual);
		return *this;
	}

	CarBuilder& domain::CarBuilder::setConsumption(const float _consumption)
	{
		car.setConsumption(_consumption);
		return *this;
	}

	CarBuilder& domain::CarBuilder::setPictureName(const std::string _picture_name) {
		car.setPictureName(_picture_name);
		return *this;
	}

	Car& CarBuilder::build() {
		return car;
	}
}
