#ifndef EXPRESSIONGENERATOR_H
#define EXPRESSIONGENERATOR_H

#include <iostream>
#include <stdlib.h>
#include <map>

#include "../domain/CarBuilder.h"
#include "../controller/CarController.h"
#include "../core/expression.h"
#include "../core/valueModel.h"
#include "repository/car/CarRepository.h"
#include "repository/car/InMemoryCarRepository.h"
#include "../fuzzy/CogDefuzz.h"
#include "../core/evaluator.h"
#include "../fuzzy/or.h"
#include "../fuzzy/and.h"
#include "../fuzzy/then.h"
#include "../fuzzy/agg.h"
#include "../fuzzy/not.h"
#include "../fuzzy/is.h"
#include "../fuzzy/fuzzyfactory.h"

template<typename T>
class ExpressionGenerator
{
public:
    ExpressionGenerator(CarController<T>*);
    ~ExpressionGenerator() = default;

    T generate(T,T,T,T,T,T)const;
    std::vector<domain::Car*> scan(const T) const;
private:
    CarController<T>* controller;
};

template<typename T>
ExpressionGenerator<T>::ExpressionGenerator(CarController<T>* _controller):
    controller(_controller)
{}

template<typename T>
T ExpressionGenerator<T>::generate(T _power, T _seats,T _category,T _consumption,T _gearBox,T _price) const{

    using Not = fuzzy::NotMinus1<T>;
    using AndMin = fuzzy::AndMin<T>;
    using OrMax = fuzzy::OrMax<T>;
    using ThenMin = fuzzy::ThenMin<T>;
    using AggMax = fuzzy::AggMax<T>;
    using CogDefuzz = fuzzy::CogDefuzz<T>;
    using FuzzyExpressionFactory = fuzzy::FuzzyExpressionFactory<T>;
    using IsTriangle = fuzzy::isTriangle<T>;
    using IsTrapezeRight = fuzzy::isTrapezeRight<T>;
    using Value = core::valueModel<T>;

    Not opNot;
    AndMin opAnd;
    OrMax opOr;
    ThenMin opThen;
    AggMax opAgg;
    CogDefuzz opMDefuzz;

    FuzzyExpressionFactory f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMDefuzz);

    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();

    std::vector<fuzzy::is<T>*> v_power = controller->createIs(fuzzy::isTriangle<T>(), carRepository->getAllPower());
    std::vector<fuzzy::is<T>*> v_seats = controller->createIs(fuzzy::isTriangle<T>(), carRepository->getAllSeats());
    std::vector<fuzzy::is<T>*> v_category = controller->createIs(fuzzy::isTriangle<T>(), carRepository->getAllCategory());
    std::vector<fuzzy::is<T>*> v_consumption = controller->createIs(fuzzy::isTriangle<T>(), carRepository->getAllConsumption());
    std::vector<fuzzy::is<T>*> v_gear = controller->createIs(fuzzy::isTrapezeRight<T>(), carRepository->getAllGear());
    std::vector<fuzzy::is<T>*> v_price = controller->createIs(fuzzy::isTriangle<T>(), carRepository->getAllPrices());

    //power
    IsTriangle* weak = dynamic_cast<fuzzy::isTriangle<T>*>(v_power.at(0));
    IsTriangle* medium = dynamic_cast<fuzzy::isTriangle<T>*>(v_power.at(1));
    IsTriangle* strong = dynamic_cast<fuzzy::isTriangle<T>*>(v_power.at(2));
    //seats
    IsTriangle* notSpacious = dynamic_cast<fuzzy::isTriangle<T>*>(v_seats.at(0));
    IsTriangle* spacious = dynamic_cast<fuzzy::isTriangle<T>*>(v_seats.at(1));
    IsTriangle* verySpacious = dynamic_cast<fuzzy::isTriangle<T>*>(v_seats.at(2));
    //category
    IsTriangle* city = dynamic_cast<fuzzy::isTriangle<T>*>(v_category.at(0));
    IsTriangle* electric = dynamic_cast<fuzzy::isTriangle<T>*>(v_category.at(1));
    IsTriangle* sport = dynamic_cast<fuzzy::isTriangle<T>*>(v_category.at(2));
    IsTriangle* suv = dynamic_cast<fuzzy::isTriangle<T>*>(v_category.at(0));
    IsTriangle* util = dynamic_cast<fuzzy::isTriangle<T>*>(v_category.at(1));
    //consumption
    IsTriangle* cWeak = dynamic_cast<fuzzy::isTriangle<T>*>(v_consumption.at(0));
    IsTriangle* cMedium = dynamic_cast<fuzzy::isTriangle<T>*>(v_consumption.at(1));
    IsTriangle* cStrong = dynamic_cast<fuzzy::isTriangle<T>*>(v_consumption.at(2));
    //gear
    IsTrapezeRight* man = dynamic_cast<fuzzy::isTrapezeRight<T>*>(v_gear.at(0));
    IsTrapezeRight* aut = dynamic_cast<fuzzy::isTrapezeRight<T>*>(v_gear.at(1));
    //price
    IsTriangle* pcheap = dynamic_cast<fuzzy::isTriangle<T>*>(v_price.at(0));
    IsTriangle* paverage = dynamic_cast<fuzzy::isTriangle<T>*>(v_price.at(1));
    IsTriangle* pgenerous = dynamic_cast<fuzzy::isTriangle<T>*>(v_price.at(2));
    //id
    IsTriangle cheap(0, 5, 10);
    IsTriangle average(10, 15, 20);
    IsTriangle generous(20, 25, 30);

    //carindicator
    IsTriangle economicCar(0, 30, 60);
    IsTriangle lowConsumptionCar(60,90,120);
    IsTriangle crumpedCar(120,150,180);
    IsTriangle highConsumptionCar(180, 210, 240);
    IsTriangle spaciousCar(240, 270, 300);
    IsTriangle expensiveCar(300, 230, 330);

    /*****/

    Value power(_power);
    Value seats(_seats);
    Value category(_category);
    Value consumption(_consumption);
    Value gearBox(_gearBox);
    Value price(_price);
    Value carIndicator(T(0));

    core::Expression<T>* powerExpression =  f.newAgg(
                                                f.newAgg(
                                                    f.newThen(
                                                        f.newIs(weak, &power),
                                                        f.newIs(&economicCar, &carIndicator)
                                                    )
                                                    ,
                                                    f.newThen(
                                                        f.newIs(medium, &power),
                                                        f.newIs(&spaciousCar, &carIndicator)
                                                    )
                                                )
                                                ,
                                                f.newThen(
                                                    f.newIs(strong, &power),
                                                    f.newIs(&highConsumptionCar, &carIndicator)
                                                )
                                            );

    core::Expression<T>* consumptionExpression =  f.newAgg(
                                                        f.newAgg(
                                                            f.newThen(
                                                                f.newIs(cWeak, &consumption),
                                                                f.newIs(&lowConsumptionCar, &carIndicator)
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(cMedium, &consumption),
                                                                f.newIs(&economicCar, &carIndicator)
                                                            )
                                                        )
                                                        ,
                                                        f.newThen(
                                                            f.newIs(cStrong, &consumption),
                                                            f.newIs(&highConsumptionCar, &carIndicator)
                                                        )
                                                    );

    core::Expression<T>* seatsExpression = f.newAgg(
                                                f.newAgg(
                                                    f.newThen(
                                                        f.newIs(notSpacious, &seats),
                                                        f.newIs(&crumpedCar, &carIndicator)
                                                    ),
                                                    f.newThen(
                                                        f.newIs(spacious, &seats),
                                                        f.newIs(&crumpedCar, &carIndicator)
                                                    )
                                                )
                                                ,
                                                f.newThen(
                                                    f.newIs(verySpacious, &seats),
                                                    f.newIs(&highConsumptionCar, &carIndicator)
                                                )
                                            );

    core::Expression<T>* categoryExpression = f.newAgg(
                                                    f.newAgg(
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(city, &category),
                                                                    f.newIs(&crumpedCar, &carIndicator)
                                                                )
                                                                ,
                                                                f.newThen(
                                                                    f.newIs(electric, &category),
                                                                    f.newIs(&lowConsumptionCar, &carIndicator)
                                                                )
                                                            ),
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(sport, &category),
                                                                    f.newIs(&expensiveCar, &carIndicator)
                                                                )
                                                                ,
                                                                f.newThen(
                                                                    f.newIs(suv, &category),
                                                                    f.newIs(&highConsumptionCar, &carIndicator)
                                                                )
                                                            )
                                                        )
                                                    ,
                                                    f.newThen(
                                                        f.newIs(util, &category),
                                                        f.newIs(&spaciousCar, &carIndicator)
                                                    )
                                                );

    core::Expression<T>* gearBoxExpression = f.newAgg(
                                                f.newThen(
                                                    f.newIs(man, &gearBox),
                                                    f.newIs(&lowConsumptionCar, &carIndicator)
                                                ),
                                                f.newThen(
                                                    f.newIs(aut, &gearBox),
                                                    f.newIs(&highConsumptionCar, &carIndicator)
                                                )
                                            );

    core::Expression<T>* priceExpression = f.newAgg(
                                                    f.newAgg(
                                                        f.newThen(
                                                            f.newIs(pcheap, &price),
                                                            f.newIs(&economicCar, &carIndicator)
                                                        ),
                                                        f.newThen(
                                                            f.newIs(paverage, &price),
                                                            f.newIs(&spaciousCar, &carIndicator)
                                                        )
                                                    )
                                                    ,
                                                    f.newThen(
                                                        f.newIs(pgenerous, &price),
                                                        f.newIs(&expensiveCar, &carIndicator)
                                                    )
                                                );

    core::Expression<T>* r = f.newAgg(
                                f.newAgg(
                                        f.newAgg(powerExpression,seatsExpression)
                                        ,
                                        f.newAgg(categoryExpression,gearBoxExpression)
                                    )
                                ,
                                f.newAgg(priceExpression,consumptionExpression)

                            );

    core::Expression<T>* result = f.newMandanidaniDefuzz(&carIndicator, r, 0, 3330, 1);

    return result->evaluate();
}

template<typename T>
std::vector<domain::Car*> ExpressionGenerator<T>::scan(const T _v) const{
    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
    std::vector<domain::Car> cars = carRepository->getAllCars();
    T nearest;
    std::vector<domain::Car*> nCars;

    for (auto car = cars.begin(); car != cars.end(); ++car) {
        T power = car->getPower();
        T seats = car->getPlaces();
        T category = car->getCategory()->getType();
        T consumption = car->getConsumption();
        T gearBox = car->isManualGearbox() ? T(1) : T(0);
        T price = car->getPrice();
        T value = ExpressionGenerator<T>::generate(power, seats, category, consumption, gearBox, price);
        if(car==cars.begin() || (std::abs(value - _v) < std::abs(nearest - _v))){
            nearest = value;
            domain::CarBuilder* cBuilder = new domain::CarBuilder();
            cBuilder->setName(car->getName())
                    .setPower(car->getPower())
                    .setPrice(car->getPrice())
                    .setPlaces(car->getPlaces())
                    .setPictureName(car->getPictureName())
                    .setCategory(car->getCategory())
                    .setConsumption(car->getConsumption());
            nCars.push_back(&(cBuilder->build()));
        }
    }

    return nCars;
}

#endif // EXPRESSIONGENERATOR_H
