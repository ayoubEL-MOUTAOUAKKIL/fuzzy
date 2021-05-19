#include "Car.h"
#include "domain/categorie/City.h"

domain::Car::Car() : 
	name(""),
	power(0),
	places(0),
    category(new domain::City()),
	price(0),
	manual_gearbox(true),
	consumption(0)
{
}
