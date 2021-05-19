#ifndef UTILITARY_H
#define UTILITARY_H

#include "Category.h"

namespace domain {
    class Utilitary : public Category{
        virtual double getType() const { return 5; };
    };
}

#endif // !UTILITARY_H
