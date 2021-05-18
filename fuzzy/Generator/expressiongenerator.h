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
    ExpressionGenerator(CarController<T>&);
    ~ExpressionGenerator() = default;

    T generate(T,T,T,T,T,T)const;
    domain::Car* scan(T) const;
private:
    CarController<T>& controller;
};

template<typename T>
ExpressionGenerator<T>::ExpressionGenerator(CarController<T>& _controller):
    controller(_controller)
{}

template<typename T>
T ExpressionGenerator<T>::generate(T _power, T _seats,T _category,T _consumption,T _gearBox,T _price)const{

        using Not = fuzzy::NotMinus1<T>;
        using AndMin = fuzzy::AndMin<T>;
        using OrMax = fuzzy::OrMax<T>;
        using ThenMin = fuzzy::ThenMin<T>;
        using AggMax = fuzzy::AggMax<T>;
        using CogDefuzz = fuzzy::CogDefuzz<T>;
        using FuzzyExpressionFactory = fuzzy::FuzzyExpressionFactory<T>;
        using IsTriangle = fuzzy::isTriangle<T>;
        using Value = core::valueModel<T>;


        Not opNot;
        AndMin opAnd;
        OrMax opOr;
        ThenMin opThen;
        AggMax opAgg;
        CogDefuzz opMDefuzz;

        fuzzy::FuzzyExpressionFactory f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMDefuzz);



        repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
        std::vector<fuzzy::is<T>*> v_power = controller.createIs<T>(fuzzy::isTriangle<T>(), carRepository->getAllPower());
        std::vector<fuzzy::is<T>*> v_seats = controller.createIs<T>(fuzzy::isTriangle<T>(), carRepository->getAllSeats());
        std::vector<fuzzy::is<T>*> v_category = controller.createIs<T>(fuzzy::isTriangle<T>(), carRepository->getAllCategory());
        std::vector<fuzzy::is<T>*> v_consumption = controller.createIs<T>(fuzzy::isTriangle<T>(), carRepository->getAllConsumption());
        std::vector<fuzzy::is<T>*> v_gear = controller.createIs<T>(fuzzy::isTrapezeRight<T>(), carRepository->getAllGear());
        std::vector<fuzzy::is<T>*> v_price = controller.createIs<T>(fuzzy::isTriangle<T>(), carRepository->getAllPrice());


        //power
        IsTriangle* weak = v_power.at(0);
        IsTriangle* medium = v_power.at(1);
        IsTriangle* strong = v_power.at(2);
        //seats
        IsTriangle* notSpacious = v_seats.at(0);
        IsTriangle* spacious = v_seats.at(1);
        IsTriangle* verySpacious = v_seats.at(2);
        //category
        IsTriangle*  city = v_category.at(0);
        IsTriangle*  electric = v_category.at(1);
        IsTriangle*  sport = v_category.at(2);
        IsTriangle*  suv = v_category.at(3);
        IsTriangle*  util = v_category.at(4);
        //consumption
        IsTriangle*  cWeak = v_consumption.at(0);
        IsTriangle*  cMedium = v_category.at(1);
        IsTriangle*  cStrong = v_category.at(2);
        //gear
        IsTriangle*  man = v_category.at(0);
        IsTriangle*  aut = v_category.at(1);
        //price
        IsTriangle*  pcheap = v_category.at(0);
        IsTriangle*  paverage = v_category.at(1);
        IsTriangle*  pgenerous = v_category.at(2);
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

        core::Expression<T>* seatsExpression =  f.newAgg(
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
                                                                f.newIs(&man, &gearBox),
                                                                f.newIs(&lowConsumptionCar, &carIndicator)
                                                            ),
                                                            f.newThen(
                                                                f.newIs(&aut, &gearBox),
                                                                f.newIs(&highConsumptionCar, &carIndicator)
                                                            )
                                                        );





        core::Expression<T>* priceExpression =    f.newAgg(
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





        core::Expression<T>* r =    f.newAgg(
                                                f.newAgg(
                                                            f.newAgg(powerExpression,seatsExpression)
                                                            ,
                                                            f.newAgg(categoryExpression,gearBoxExpression)
                                                        )
                                                ,
                                                f.newAgg(priceExpression,consumptionExpression)

                                            );



            core::Expression<T>* result = f.newMandanidaniDefuzz(&carIndicator, r, 0, 300, 1);

            return result->evaluate();
}

template<typename T>
domain::Car* ExpressionGenerator<T>::scan(T _v) const{
    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
    std::vector<domain::Car> cars = carRepository->getAllCars();
    std::map<domain::Car*,T> association;
    T nearest;
    domain::Car* nCar;
    domain::Car fcar;
    domain::CarBuilder cbuilder;

    for (auto car = cars.begin(); car != cars.end(); ++car) {
        T power = car->getPower();
        T seats = car->getPlaces();
        T category = car->getCategory().getType();
        T consumption = car->getConsumption();
        T gearBox;
        car->isManualGearbox() ? (gearBox = 1) : (gearBox = 0);
        T price = car->getPrice();
        T value = ExpressionGenerator<T>::generate(power,seats,category,consumption,gearBox,price);
        if(car==cars.begin() || (std::abs(value - _v) < std::abs(nearest - _v))){
            nearest = value;
            cbuilder.setName(car->getName());
            cbuilder.setPower(car->getPower());
            cbuilder.setConsumption(car->getConsumption());
            cbuilder.setPrice(car->getPrice());
            cbuilder.addPlaces(car->getPlaces());
            cbuilder.setPictureName(car->getPictureName());
            car->isManualGearbox() ? cbuilder.withManualGearbox(1) : cbuilder.withManualGearbox(0);
            nCar = &cbuilder.build();
        }
    }
    std::cout << std::endl << nCar->getName();
    std::cout << std::endl << nCar->getConsumption();
    //std::cout << std::endl << nCar->getCategory();
    std::cout << std::endl << nCar->getPictureName();
    std::cout << std::endl << nCar->getPower();
    std::cout << std::endl << nCar->getPrice();
    return nCar;

}



#endif // EXPRESSIONGENERATOR_H
