#ifndef CITY_H
#define CITY_H

#include "Category.h"

namespace domain {
    class City : public Category{
        virtual double getType() const { return 1; };
    };
}

#endif // !CITY_H
