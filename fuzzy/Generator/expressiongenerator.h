#ifndef EXPRESSIONGENERATOR_H
#define EXPRESSIONGENERATOR_H

#include <iostream>
#include <stdlib.h>
#include <map>

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
    ExpressionGenerator(CarController&);
    ~ExpressionGenerator() = default;

    T generate(T,T,T,T,T,T)const;
    domain::Car* scan(T) const;
private:
    CarController& controller;
};

template<typename T>
ExpressionGenerator<T>::ExpressionGenerator(CarController& _controller):
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
        std::vector<fuzzy::is<T>*> vpower = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllPower());
        std::vector<fuzzy::is<T>*> vseats = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllSeats());
        std::vector<fuzzy::is<T>*> vcategory = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllCategory());
        std::vector<fuzzy::is<T>*> vconsumption = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllConsumption());
        std::vector<fuzzy::is<T>*> vgear = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllGear());
        std::vector<fuzzy::is<T>*> vprice = controller.createIs(new fuzzy::isTriangle<T>(), carRepository->getAllPrice());


        //power
        IsTriangle* weak = vpower.at(0);
        IsTriangle* medium = vpower.at(1);
        IsTriangle* strong = vpower.at(2);
        //seats
        IsTriangle* notSpacious = vseats.at(0);
        IsTriangle* spacious = vseats.at(1);
        IsTriangle* verySpacious = vseats.at(2);
        //category
        IsTriangle*  city = vcategory.at(0);
        IsTriangle*  electric = vcategory.at(1);
        IsTriangle*  sport = vcategory.at(2);
        IsTriangle*  suv = vcategory.at(3);
        IsTriangle*  util = vcategory.at(4);
        //consumption
        IsTriangle*  cWeak = vconsumption.at(0);
        IsTriangle*  cMedium = vcategory.at(1);
        IsTriangle*  cStrong = vcategory.at(2);
        //gear
        IsTriangle*  man = vcategory.at(0);
        IsTriangle*  aut = vcategory.at(1);
        //price
        IsTriangle*  pcheap = vcategory.at(0);
        IsTriangle*  paverage = vcategory.at(1);
        IsTriangle*  pgenerous = vcategory.at(2);
        //id
        IsTriangle cheap(0, 5, 10);
        IsTriangle average(10, 15, 20);
        IsTriangle generous(20, 25, 30);


        /*****/

        Value power(0);
        Value seats(0);
        Value category(0);
        Value consumption(0);
        Value gearBox(0);
        Value price(0);
        Value carIndicator(0);



        core::Expression<T>* powerExpression =  f.newAgg(
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(weak, &power),
                                                                    f.newIs(&medium, &carIndicator)
                                                                )
                                                                ,
                                                                f.newThen(
                                                                    f.newIs(medium, &power),
                                                                    f.newIs(&average, &carIndicator)
                                                                )
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(strong, &power),
                                                                f.newIs(&generous, &carIndicator)
                                                            )
                                                        );

        core::Expression<T>* consumptionExpression =  f.newAgg(
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(cWeak, &consumption),
                                                                    f.newIs(&medium, &carIndicator)
                                                                )
                                                                ,
                                                                f.newThen(
                                                                    f.newIs(cMedium, &consumption),
                                                                    f.newIs(&average, &carIndicator)
                                                                )
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(cStrong, &consumption),
                                                                f.newIs(&generous, &carIndicator)
                                                            )
                                                        );

        core::Expression<T>* seatsExpression =  f.newAgg(
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(notSpacious, &seats),
                                                                    f.newIs(&cheap, &carIndicator)
                                                                ),
                                                                f.newThen(
                                                                    f.newIs(spacious, &seats),
                                                                    f.newIs(&average, &carIndicator)
                                                                )
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(verySpacious, &seats),
                                                                f.newIs(&generous, &carIndicator)
                                                            )
                                                        );

        core::Expression<T>* categoryExpression = f.newAgg(
                                                            f.newAgg(
                                                                    f.newAgg(
                                                                        f.newThen(
                                                                            f.newIs(city, &category),
                                                                            f.newIs(&cheap, &carIndicator)
                                                                        )
                                                                        ,
                                                                        f.newThen(
                                                                            f.newIs(electric, &category),
                                                                            f.newIs(&generous, &carIndicator)
                                                                        )
                                                                    ),
                                                                    f.newAgg(
                                                                        f.newThen(
                                                                            f.newIs(sport, &category),
                                                                            f.newIs(&generous, &carIndicator)
                                                                        )
                                                                        ,
                                                                        f.newThen(
                                                                            f.newIs(suv, &category),
                                                                            f.newIs(&average, &carIndicator)
                                                                        )
                                                                    )
                                                                )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(util, &category),
                                                                f.newIs(&cheap, &carIndicator)
                                                            )
                                                            );

        core::Expression<T>* gearBoxExpression = f.newAgg(
                                                            f.newThen(
                                                                f.newIs(man, &gearBox),
                                                                f.newIs(&cheap, &carIndicator)
                                                            ),
                                                            f.newThen(
                                                                f.newIs(aut, &gearBox),
                                                                f.newIs(&average, &carIndicator)
                                                            )
                                                        );





        core::Expression<T>* priceExpression =    f.newAgg(
                                                            f.newAgg(
                                                                f.newThen(
                                                                    f.newIs(pcheap, &price),
                                                                    f.newIs(&cheap, &carIndicator)
                                                                ),
                                                                f.newThen(
                                                                    f.newIs(paverage, &price),
                                                                    f.newIs(&average, &carIndicator)
                                                                )
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(pgenerous, &price),
                                                                f.newIs(&generous, &carIndicator)
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

            power.setValue(_power);
            seats.setValue(_seats);
            category.setValue(_category);
            consumption.setValue(_consumption);
            gearBox.setValue(_gearBox);
            price.setValue(_price);

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
            nCar = &(*car);
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
