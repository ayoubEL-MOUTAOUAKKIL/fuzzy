#ifndef ISSTRATEGYFACTORY_H
#define ISSTRATEGYFACTORY_H
#include "IsStrategy.h"
#include "IsTriangleStrategy.h"
#include "IsTrapezeRightStrategy.h"
#include <string>
template <typename T>
class IsStrategyFactory{
public:
    IsStrategyFactory() = default;
    virtual ~IsStrategyFactory()=default;
    virtual IsStrategy<T>* generateIsStrategy(const fuzzy::is<T>&);
};

template<typename A, typename B>
bool is_same_class(const A& class1, const B& class2) {
    return typeid(class1) == typeid(class2);
}

template <typename T>
IsStrategy<T>* IsStrategyFactory<T>::generateIsStrategy(const fuzzy::is<T>& is){
    if (is_same_class(fuzzy::isTriangle<T>(), is)){
        return new IsTriangleStrategy<T>();
    }
    if (is_same_class(fuzzy::isTrapezeRight<T>(), is)){
        return new IsTrapezeRightStrategy<T>();
    }
    throw std::string("Not implemented type.");
}
#endif // ISSTRATEGYFACTORY_H
