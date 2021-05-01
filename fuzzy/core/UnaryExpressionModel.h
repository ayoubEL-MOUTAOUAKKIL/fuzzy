#ifndef UNARYEXPRESSIONMODEL_H
#define UNARYEXPRESSIONMODEL_H
#include "expression.h"

namespace core {

	template<typename T>
	class UnaryExpressionModel : public UnaryExpression<T>,public Expression<T>{

	public:
		UnaryExpressionModel(UnaryExpression<T>*, Expression<T>*);
		virtual ~UnaryExpressionModel() = default;
		T evaluate() const;
		T evaluate(Expression<T>*) const;

	private:
		UnaryExpression<T>* operat;
		Expression<T>* operand;
	};

	template<typename T>
	UnaryExpressionModel<T>::UnaryExpressionModel(UnaryExpression<T>* _e1, Expression<T>* _e2) :
		operat(_e1), operand(_e2)
	{
	}

	template<typename T>
	T UnaryExpressionModel<T>::evaluate() const
	{
		if (operand != nullptr) {
			return evaluate(operand);
		}
	}

	template<typename T>
	T UnaryExpressionModel<T>::evaluate(Expression<T>* o) const
	{
		if (operat != nullptr) {
			return operat->evaluate(o);
		}
	}
	
}


#endif
