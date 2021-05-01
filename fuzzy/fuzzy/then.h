#ifndef THEN_H
#define THEN_H

#include <cmath>
#include "../core/expression.h"
namespace fuzzy {


	template<typename T>
	class Then :public core::BinaryExpression<T> {
	};

	template<typename T>
	class ThenMin :public Then<T> {
	public:
		T evaluate(core::Expression<T>*,core::Expression<T>*)const;
	};

	template<typename T>
	T ThenMin<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		/*std::cout << std::endl << "-->thenMin";
		std::cout << std::endl << "-->1: " << _e1->evaluate();
		std::cout << std::endl << "-->2: " << _e2->evaluate();
		std::cout << std::endl << "-->result: " << fmin(_e1->evaluate(), _e2->evaluate());*/
		return fmin(_e1->evaluate(), _e2->evaluate());
	}

	template<typename T>
	class ThenMult :public Then<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T ThenMult<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		return _e1->evaluate() * _e2->evaluate();
	}

	template<typename T>
	class SugenoThen :public Then<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
		T premiseValue();
	private:
		mutable T premiseVal;
	};

	template<typename T>
	T SugenoThen<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		premiseVal = _e1->evaluate();
		return  _e1->evaluate() * _e2->evaluate();
	}

	template<typename T>
	T SugenoThen<T>::premiseValue(){
		return premiseVal;
	}
}



#endif
