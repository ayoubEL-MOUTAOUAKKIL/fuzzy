#ifndef CATEGORY_H
#define CATEGORY_H

namespace domain {
	class Category{
    public:
        virtual int getType() const { return -1; };
	};
}

#endif // !CATEGORIE_H
