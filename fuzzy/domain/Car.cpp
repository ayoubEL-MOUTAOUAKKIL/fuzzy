#include "Car.h"

domain::Car::Car() : 
	name(""),
	power(0),
	places(0),
	category((*new Category())),
	price(0),
	manual_gearbox(true),
	consumption(0)
{
}