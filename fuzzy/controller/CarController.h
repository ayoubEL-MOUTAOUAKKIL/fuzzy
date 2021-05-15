#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H
#include "fuzzy/is.h"
#include <iostream>

template<typename T>
class CarController
{
public:
    CarController() = default;
    virtual ~CarController() = default;
    virtual fuzzy::is<T> createIs(fuzzy::is<T>*,const std::vector<T>);
};

template<typename T>
fuzzy::is<T> CarController<T>::createIs(fuzzy::is<T>* is,const std::vector<T>datas){
    T min = datas.at(0);
    T max =0;
    T sum =0;
    T average = 0;
    for(auto& data : datas){
        if( data > max ){
            max = data;
        }
        if(data < min){
            min = data;
        }
        sum += data;
    }
    average = sum/datas.size();
    if(dynamic_cast<fuzzy::isTriangle<T>*>(is)!= nullptr){
       return new fuzzy::isTriangle<T>(min,(min+average)/2,average);
    }
    return is;
}

#endif // CARCONTROLLER_H
