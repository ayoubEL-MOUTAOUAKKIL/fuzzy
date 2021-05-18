#include "CarFactory.h"
#include "CarBuilder.h"
#include "categorie/CategoryFactory.h"

namespace domain {
	Car& domain::CarFactory::createCar(const std::vector<std::string> _csvLine)
	{
		domain::CarBuilder* builder = new CarBuilder();
		return builder
			->setName(_csvLine[0])
			.setPower(std::stof(_csvLine[1]))
            .setPlaces(std::stoi(_csvLine[2]))
			.setCategory(domain::CategoryFactory().createCategory(_csvLine[3]))
			.setConsumption(std::stof(_csvLine[4]))
			.withManualGearbox(_csvLine[5].compare("manuelle") ? true : false)
			.setPrice(std::stof(_csvLine[6]))
			.setPictureName(_csvLine[7])
			.build();
	}
}
