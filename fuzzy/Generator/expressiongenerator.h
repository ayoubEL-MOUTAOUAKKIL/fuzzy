#ifndef EXPRESSIONGENERATOR_H
#define EXPRESSIONGENERATOR_H

#include <iostream>
#include <map>

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
    ExpressionGenerator();
    ~ExpressionGenerator() = default;

    T generate(T,T,T,T,T,T)const;
    void scan() const;
};

template<typename T>
ExpressionGenerator<T>::ExpressionGenerator()
{}

template<typename T>
T ExpressionGenerator<T>::generate(T _power, T _seats,T _category,T _consumption,T _gearBox,T _price) const
{
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

        IsTriangle poor(-5, 200, 500);
        IsTriangle good(0, 100, 10000);
        IsTriangle excellent(5000, 10000, 1500000);

        IsTriangle cheap(0, 5, 10);
        IsTriangle average(10, 15, 20);
        IsTriangle generous(20, 25, 30);

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
                                                                    f.newIs(&poor, &power),
                                                                    f.newIs(&cheap, &carIndicator)
                                                                )
                                                                ,
                                                                f.newThen(
                                                                    f.newIs(&good, &power),
                                                                    f.newIs(&average, &carIndicator)
                                                                )
                                                            )
                                                            ,
                                                            f.newThen(
                                                                f.newIs(&excellent, &power),
                                                                f.newIs(&generous, &carIndicator)
                                                            )
                                                        );

        core::Expression<T>* seatsExpression = f.newAgg(
                                                    f.newAgg(
                                                        f.newThen(
                                                            f.newIs(&poor, &seats),
                                                            f.newIs(&cheap, &carIndicator)
                                                        ),
                                                        f.newThen(
                                                            f.newIs(&good, &seats),
                                                            f.newIs(&average, &carIndicator)
                                                        )
                                                    )
                                                    ,
                                                    f.newThen(
                                                        f.newIs(&excellent, &seats),
                                                        f.newIs(&generous, &carIndicator)
                                                    )
                                                );

        core::Expression<T>* categoryExpression = f.newAgg(
                                                    f.newAgg(
                                                        f.newThen(
                                                            f.newIs(&poor, &category),
                                                            f.newIs(&cheap, &carIndicator)
                                                        )
                                                        ,
                                                        f.newThen(
                                                            f.newIs(&good, &category),
                                                            f.newIs(&average, &carIndicator)
                                                        )
                                                    ),
                                                    f.newThen(
                                                        f.newIs(&excellent, &category),
                                                        f.newIs(&generous, &carIndicator)
                                                    )
                                                );

        core::Expression<T>* gearBoxExpression = f.newAgg(
                                                        f.newAgg(
                                                            f.newThen(
                                                                f.newIs(&poor, &gearBox),
                                                                f.newIs(&cheap, &carIndicator)
                                                            ),
                                                            f.newThen(
                                                                f.newIs(&good, &gearBox),
                                                                f.newIs(&average, &carIndicator)
                                                            )
                                                        )
                                                        ,
                                                        f.newThen(
                                                            f.newIs(&excellent, &gearBox),
                                                            f.newIs(&generous, &carIndicator)
                                                        )
                                                    );

        core::Expression<T>* priceExpression = f.newAgg(
                                                    f.newAgg(
                                                        f.newThen(
                                                            f.newIs(&poor, &price),
                                                            f.newIs(&cheap, &carIndicator)
                                                        ),
                                                        f.newThen(
                                                            f.newIs(&good, &price),
                                                            f.newIs(&average, &carIndicator)
                                                        )
                                                    )
                                                    ,
                                                    f.newThen(
                                                        f.newIs(&excellent, &price),
                                                        f.newIs(&generous, &carIndicator)
                                                    )
                                                );

        core::Expression<T>* r = f.newAgg(
                                        f.newAgg(
                                            f.newAgg(powerExpression,seatsExpression),
                                            f.newAgg(categoryExpression,gearBoxExpression)
                                        )
                                        ,
                                        priceExpression
                                    );

            core::Expression<T>* result = f.newMandanidaniDefuzz(&carIndicator, r, 0, 30, 1);

            power.setValue(_power);
            seats.setValue(_seats);
            category.setValue(_category);
            consumption.setValue(_consumption);
            gearBox.setValue(_gearBox);
            price.setValue(_price);

            return result->evaluate();
}

template<typename T>
void ExpressionGenerator<T>::scan() const{
    repository::CarRepository* carRepository = repository::InMemoryCarRepository::getInstance();
    std::vector<domain::Car> cars = carRepository->getAllCars();
    for (auto car = cars.begin(); car != cars.end(); ++car) {
        T power = car->getPower();
        T seats = car->getPlaces();
        T category = car->getCategory().getType();
        T consumption = car->getConsumption();
        T gearBox;
        car->isManualGearbox() ? (gearBox = 1) : (gearBox = 0);
        T price = car->getPrice();
        T value = ExpressionGenerator<T>::generate(power,seats,category,consumption,gearBox,price);
        //carRepository->setValue(car,value);
    }

}

#endif // EXPRESSIONGENERATOR_H
