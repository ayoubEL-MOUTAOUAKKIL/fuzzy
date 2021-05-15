#ifndef SUV_H
#define SUV_H

#include "Category.h"

namespace domain {
    class Suv : public Category{
        virtual int getType() const { return 4; };
    };
}

#endif // !SUV_H
