#ifndef CITY_H
#define CITY_H

#include "Category.h"

namespace domain {
    class City : public Category{
        virtual int getType() const { return 1; };
    };
}

#endif // !CITY_H
