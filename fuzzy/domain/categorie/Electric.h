#ifndef ELECTRIC_H
#define ELECTRIC_H
#include "Category.h"

namespace domain {
    class Electric: public Category{
        virtual int getType() const { return 2; };
    };
}

#endif // !ELECTRIC_H
