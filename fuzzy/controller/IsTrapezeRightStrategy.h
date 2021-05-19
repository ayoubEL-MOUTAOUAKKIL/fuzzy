#ifndef ISTRAPEZERIGHT_H
#define ISTRAPEZERIGHT_H
#include "IsStrategy.h"

template <typename T>
class IsTrapezeRightStrategy: public IsStrategy<T>
{
public:
    IsTrapezeRightStrategy() = default;
    virtual ~IsTrapezeRightStrategy() = default;
    virtual std::vector<fuzzy::is<T>*> generateIs(const T&,const T&) override;
};

template<typename T>
fuzzy::is<T>* create_trapeze_right(const T min_range, const T max_range) {
    return new fuzzy::isTrapezeRight<T>(min_range, max_range);
}

template <typename T>
std::vector<fuzzy::is<T>*> IsTrapezeRightStrategy<T>::generateIs(const T& min, const T& max){
    std::vector<fuzzy::is<T>*> trapezesRight;
    trapezesRight.push_back(create_trapeze_right<T>(min,(max-min)/2));
    trapezesRight.push_back(create_trapeze_right<T>((max-min)/2,max));
    return trapezesRight;
}
#endif // ISTRAPEZERIGHT_H
