#ifndef OR_H
#define OR_H

#include <cmath>
#include "../core/expression.h"

namespace fuzzy {

	template <typename T>
	class Or :public core::BinaryExpression<T> {
	};

	template <typename T>
	class OrPlus : public Or<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T OrPlus<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		return (_e1->evaluate() + _e2->evaluate()) - (_e1->evaluate() * _e2->evaluate());
	}

	template <typename T>
	class OrMax :public Or<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T OrMax<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const {
		return fmax(_e1->evaluate(), _e2->evaluate());
	}
}


#endif