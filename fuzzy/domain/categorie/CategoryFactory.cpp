#include "CategoryFactory.h"
#include "City.h"
#include "Sports.h"
#include "Suv.h"
#include "Utilitary.h"
#include "Electric.h"

namespace domain {

	const std::string CITY = "citadine";
	const std::string SPORT = "sportive";
	const std::string SUV = "suv";
	const std::string ELECTRIC = "electrique";
	const std::string UTILITARY = "utilitaire";

	Category domain::CategoryFactory::createCategory(const std::string _categoryType)
	{
		if (_categoryType.compare(CITY)) return City();
		if (_categoryType.compare(SPORT)) return Sports();
		if (_categoryType.compare(SUV)) return Suv();
		if (_categoryType.compare(ELECTRIC)) return Electric();
		if (_categoryType.compare(UTILITARY)) return Utilitary();
		return Category();
	}
}