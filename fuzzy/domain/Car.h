#ifndef CAR_H
#define CAR_H
#include "categorie/Category.h"
#include <string>

namespace domain {
	class Car {
	public:
            Car();
            virtual ~Car() = default;
            Car & operator = (Car const &);

            virtual std::string getName() const { return name; }
            virtual double getPower() const { return power; }
            virtual int getPlaces() const { return places; }
            virtual Category& getCategory() const { return category; }
            virtual double getPrice() const { return price; }
            virtual bool isManualGearbox() const { return manual_gearbox; }
            virtual double getConsumption() const { return consumption; }
            virtual std::string getPictureName() const { return picture_name; }

            virtual void setName(const std::string _name) { name = _name; }
            virtual void setPower(const double _power) { power = _power; }
            virtual void setPlaces(const int _places) { places = _places; }
            virtual void setCategory(const Category& _category) { category = _category; }
            virtual void setPrice(const double _price) { price = _price; }
            virtual void withManualGearbox(const bool isManualGearbox) { manual_gearbox = isManualGearbox; }
            virtual void setConsumption(const double _consumption) { consumption = _consumption; }
            virtual void setPictureName(const std::string _picture_name) { picture_name = _picture_name; }

	private:
            std::string name;
            double power;
            int places;
            Category& category;
            double price;
            bool manual_gearbox;
            double consumption;
            std::string picture_name;
	};
}

#endif // !CAR_H
