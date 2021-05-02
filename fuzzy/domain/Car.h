#ifndef CAR_H
#define CAR_H

#include "./categorie/Categorie.h"

namespace domain {
	class Car {
	public:
		Car() = default;
		virtual ~Car() = default;

		virtual int getPower() { return power; }
		virtual int getPlaces() { return places; }
		virtual Categorie& getCategorie() { return categorie; }
		virtual float getPrice() { return price; }
		virtual bool isManualGearbox() { return manual_gearbox; }
		virtual float getConsumption() { return consumption; }

		virtual void setPower(const int _power) { power = _power; }
		virtual void setPlaces(const int _places) { places = _places; }
		virtual void setCategorie(const Categorie& _categorie) { categorie = _categorie; }
		virtual void setPrice(const int _price) { price = _price; }
		virtual void withManualGearbox(const bool isManualGearbox) { manual_gearbox = isManualGearbox; }
		virtual void setConsumption(const float _consumption) { consumption = _consumption; }

	private:
		int power;
		int places;
		Categorie categorie;
		float price;
		bool manual_gearbox;
		float consumption;
	};

	static class CarBuilder {
	protected:
		Car& car;
	public:
		CarBuilder& setPower(const int _power) {
			this->car.setPower(_power);
			return *this;
		}

		CarBuilder& addPlaces(const int _places) {
			this->car.setPlaces(_places);
			return *this;
		}

		CarBuilder& setCategorie(const Categorie& _categorie) {
			this->car.setCategorie(_categorie);
			return *this;
		}

		CarBuilder& setPrice(const float _price) {
			this->car.setPrice(_price);
			return *this;
		}

		CarBuilder& withManualGearbox(const bool isManual) {
			this->car.withManualGearbox(isManual);
			return *this;
		}

		CarBuilder& setConsumption(const float _consumption) {
			this->car.setConsumption(_consumption);
			return *this;
		}

		Car& build() {
			return car;
		};		
	};
}

#endif // !CAR_H