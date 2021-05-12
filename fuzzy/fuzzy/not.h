#include "../core/expression.h"
#ifndef NOT_H
#define NOT_H

namespace fuzzy {
	template<typename T>
	class Not : public core::UnaryExpression<T> {
	};

	template<typename T>
	class NotMinus1 : public Not<T> {
	public:
		virtual ~NotMinus1() = default;
		T evaluate(core::Expression<T>*)const;
	};
	template<typename T>
	T NotMinus1<T>::evaluate(core::Expression<T>* _e1)const
	{
		return 1 - _e1->evaluate();
	}
}
#endif
