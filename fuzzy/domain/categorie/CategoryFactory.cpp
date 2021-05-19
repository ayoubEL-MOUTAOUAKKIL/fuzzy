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

    Category* domain::CategoryFactory::createCategory(const std::string _categoryType)
	{
        if (_categoryType == CITY) return new City();
        if (_categoryType == SPORT) return new Sports();
        if (_categoryType == SUV) return new Suv();
        if (_categoryType == ELECTRIC) return new Electric();
        if (_categoryType == UTILITARY) return new Utilitary();
	}
}
