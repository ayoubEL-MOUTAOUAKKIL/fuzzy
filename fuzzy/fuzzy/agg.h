#ifndef AGG_H
#define AGG_H

#include <cmath>
#include "../core/expression.h"

namespace fuzzy {

	template<typename T>
	class Agg :public core::BinaryExpression<T> {
	};

	template<typename T>
	class AggMax : public Agg<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T AggMax<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		/*std::cout << std::endl << "-->aggmax2" ;
		std::cout << std::endl << "-->1: " << _e1->evaluate();
		std::cout << std::endl << "-->2: " << _e2->evaluate();
		std::cout << std::endl << "-->result: " << fmax(_e1->evaluate(), _e2->evaluate());*/
		return fmax(_e1->evaluate(), _e2->evaluate());
	}

	template<typename T>
	class AggPlus : public Agg<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T AggPlus<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		return (_e1->evaluate() + _e2->evaluate()) - (_e1->evaluate() * _e2->evaluate());
	}
}



#endif