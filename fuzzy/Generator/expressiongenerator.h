#ifndef EXPRESSIONGENERATOR_H
#define EXPRESSIONGENERATOR_H

#include "../core/expression.h"
#include "../core/valueModel.h"

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

    T generate(T,T,T,T,T,T);
};

template<typename T>
ExpressionGenerator<T>::ExpressionGenerator()
{}

template<typename T>
T ExpressionGenerator<T>::generate(T _power, T _seats,T _category,T _consumption,T _gearBox,T _price){

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


        /*
         *
         * to change
         *
         *
         *
        */

        IsTriangle poor(-5, 0, 5);
        IsTriangle good(0, 5, 10);
        IsTriangle excellent(5, 10, 15);

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

    core::Expression<T>* r =

            f.newAgg(
                f.newAgg(
                    f.newAgg(
                                f.newAgg(
                                    f.newAgg(
                                        f.newThen(
                                            f.newIs(&poor, &power),
                                            f.newIs(&cheap, &carIndicator)
                                        ),
                                        f.newThen(
                                            f.newIs(&good, &power),
                                            f.newIs(&average, &carIndicator)
                                        )
                                    ),
                                    f.newThen(
                                        f.newIs(&excellent, &power),
                                        f.newIs(&generous, &carIndicator)
                                    )
                                )

                                ,


                                f.newAgg(
                                    f.newAgg(
                                        f.newThen(
                                            f.newIs(&poor, &seats),
                                            f.newIs(&cheap, &carIndicator)
                                        ),
                                        f.newThen(
                                            f.newIs(&good, &seats),
                                            f.newIs(&average, &carIndicator)
                                        )
                                    ),
                                    f.newThen(
                                        f.newIs(&excellent, &seats),
                                        f.newIs(&generous, &carIndicator)
                                    )
                                )
                     )

                    ,

                    f.newAgg(


                                f.newAgg(
                                    f.newAgg(
                                        f.newThen(
                                            f.newIs(&poor, &category),
                                            f.newIs(&cheap, &carIndicator)
                                        ),
                                        f.newThen(
                                            f.newIs(&good, &category),
                                            f.newIs(&average, &carIndicator)
                                        )
                                    ),
                                    f.newThen(
                                        f.newIs(&excellent, &category),
                                        f.newIs(&generous, &carIndicator)
                                    )
                                )

                                ,

                                f.newAgg(
                                    f.newAgg(
                                        f.newThen(
                                            f.newIs(&poor, &gearBox),
                                            f.newIs(&cheap, &carIndicator)
                                        ),
                                        f.newThen(
                                            f.newIs(&good, &gearBox),
                                            f.newIs(&average, &carIndicator)
                                        )
                                    ),
                                    f.newThen(
                                        f.newIs(&excellent, &gearBox),
                                        f.newIs(&generous, &carIndicator)
                                    )
                                )

                        )


                    )

                    ,

                f.newAgg(
                    f.newAgg(
                        f.newThen(
                            f.newIs(&poor, &price),
                            f.newIs(&cheap, &carIndicator)
                        ),
                        f.newThen(
                            f.newIs(&good, &price),
                            f.newIs(&average, &carIndicator)
                        )
                    ),
                    f.newThen(
                        f.newIs(&excellent, &price),
                        f.newIs(&generous, &carIndicator)
                    )
                )

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

#endif // EXPRESSIONGENERATOR_H
