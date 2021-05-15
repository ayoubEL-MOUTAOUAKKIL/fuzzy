#ifndef SPORTS_H
#define SPORTS_H

#include "Category.h"

namespace domain {

	class Sports : public Category{
        virtual int getType() const { return 3; };
	};
}

#endif // !SPORTS_H
