#ifndef CATEGORY_H
#define CATEGORY_H

namespace domain {
	class Category{
    public:
        const int UNIMPLEMENTED_CATEGORY = -1;
        virtual int getType() const { return UNIMPLEMENTED_CATEGORY; };
	};
}

#endif // !CATEGORIE_H
