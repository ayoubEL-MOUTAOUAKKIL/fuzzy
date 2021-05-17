#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H
#include "fuzzy/is.h"
#include <iostream>
#include <memory>

template<typename T>
class CarController
{
public:
    CarController();
    virtual ~CarController() = default;
    virtual std::vector<fuzzy::is<T>*>& createIs(const fuzzy::is<T>&, const std::vector<T>&);
    virtual void init_datas(const std::vector<T>&);
    virtual void set_min();
    virtual void set_max();
    virtual void set_mean();
private:
    std::vector<T> datas;
    T min;
    T max;
    T mean;
};

template<typename A, typename B>
bool is_same_class(const A& class1, const B& class2) {
    return typeid(class1) == typeid(class2);
}

template<typename T>
CarController<T>::CarController():
    min(T(0)),
    max(T(0)),
    mean(T(0)),
    datas(std::vector<T>())
{
}

template<typename T>
void CarController<T>::set_min() {
    const int FIRST_INDEX = 0;
    min = datas.at(FIRST_INDEX);
    for (auto& d : datas) {
        if (d < min)
            min = d;
    }
}

template<typename T>
void CarController<T>::set_max() {
    max = T(0);
    for (auto& d : datas) {
        if (d > max)
            max = d;
    }
}

template<typename T>
void CarController<T>::set_mean() {
   T sum = T(0);
   for (auto& d : datas)
       sum += d;

   mean = sum/datas.size();
}

template<typename T>
void CarController<T>::init_datas(const std::vector<T>& d) {
    datas = d;
    set_min();
    set_max();
    set_mean();
}

template<typename T>
fuzzy::is<T>* create_triangle(const T min_range, const T max_range) {
    return new fuzzy::isTriangle<T>(min_range, (min_range+max_range)/T(2), min_range);
}

template<typename T>
std::vector<fuzzy::is<T>*>& CarController<T>::createIs(const fuzzy::is<T>& is, const std::vector<T>& car_datas){
    init_datas(car_datas);
    std::vector<fuzzy::is<T>*> t;
    if (is_same_class(fuzzy::isTriangle<T>(), is)){
        T first_tier = (max-min)/T(3);
        T second_tier = first_tier*T(2);
        T third_tier = first_tier*T(3);
        t.push_back(create_triangle<T>(first_tier, second_tier));
        t.push_back(create_triangle<T>((first_tier+second_tier)/T(2), (second_tier+third_tier)/T(2)));
        t.push_back(create_triangle<T>(second_tier, third_tier));
    }

    return t;
}

#endif // CARCONTROLLER_H
