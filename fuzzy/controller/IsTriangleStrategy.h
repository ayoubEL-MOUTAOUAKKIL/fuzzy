#ifndef ISTRIANGLESTRATEGY_H
#define ISTRIANGLESTRATEGY_H
#include "IsStrategy.h"
template <typename T>
class IsTriangleStrategy: public IsStrategy<T>
{
public:
    IsTriangleStrategy() = default;
    virtual ~IsTriangleStrategy() = default;
    virtual std::vector<fuzzy::is<T>*> generateIs(const T&,const T&) override;
};

template<typename T>
fuzzy::is<T>* create_triangle(const T min_range, const T max_range) {
    return new fuzzy::isTriangle<T>(min_range, (min_range+max_range)/T(2), max_range);
}

template <typename T>
std::vector<fuzzy::is<T>*> IsTriangleStrategy<T>::generateIs(const T& min, const T& max){
    T first_tier = (max-min)/T(3);
    T second_tier = first_tier*T(2);
    T third_tier = first_tier*T(3);
    std::vector<fuzzy::is<T>*> triangles;
    triangles.push_back(create_triangle<T>(first_tier, (first_tier+second_tier)/T(2)));
    triangles.push_back(create_triangle<T>((first_tier+second_tier)/T(2), (second_tier+third_tier)/T(2)));
    triangles.push_back(create_triangle<T>(second_tier, third_tier));
    return triangles;
}


#endif // ISTRIANGLESTRATEGY_H
