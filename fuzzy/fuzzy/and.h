#ifndef AND_H
#define AND_H

#include <cmath>
#include "../core/expression.h"

namespace fuzzy {

	template <typename T>
	class And:public core::BinaryExpression<T> {
	};



	template <typename T>
	class AndMin :public And<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T AndMin<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		return fmin(_e1->evaluate(), _e2->evaluate());
	}

	template <typename T>
	class AndMult :public And<T> {
	public:
		T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};

	template<typename T>
	T AndMult<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const{
		return _e1->evaluate() * _e2->evaluate();
	}
}






#endif
