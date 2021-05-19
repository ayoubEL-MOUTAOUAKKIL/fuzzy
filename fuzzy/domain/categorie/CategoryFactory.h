#ifndef CATEGORY_FACTORY_H
#define CATEGORY_FACTORY_H
#include <string>
#include "Category.h"

namespace domain {
	class CategoryFactory
	{
	public:
		CategoryFactory() = default;
        Category* createCategory(const std::string _categoryType);
		virtual ~CategoryFactory() = default;
	};
}

#endif // !CATEGORY_FACTORY_H
