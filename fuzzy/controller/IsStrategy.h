#ifndef ISSTRATEGY_H
#define ISSTRATEGY_H
#include "fuzzy/is.h"
#include <vector>
template <typename T>

class IsStrategy{
public:
    virtual std::vector<fuzzy::is<T>*>& generateIs(const T&,const T&)=0;
};

#endif // ISSTRATEGY_H
