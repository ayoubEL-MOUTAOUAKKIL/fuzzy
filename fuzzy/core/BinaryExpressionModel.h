#ifndef BINARYEXPRESSIONMODEL_H
#define BINARYEXPRESSIONMODEL_H
#include "expression.h"

namespace core {

	template<typename T>
	class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {

	public:
		BinaryExpressionModel(BinaryExpression<T>*, Expression<T>*,Expression<T>*);
		virtual ~BinaryExpressionModel() = default;
		T evaluate() const;
		T evaluate(Expression<T>*,Expression<T>*) const;

	private:
		BinaryExpression<T>* operat;
		Expression<T>* l;
		Expression<T>* r;
	};


	template<typename T>
	BinaryExpressionModel<T>::BinaryExpressionModel(BinaryExpression<T>* o, Expression<T>* _l,Expression<T>* _r):
		operat(o),l(_l),r(_r)
	{
	}

	template<typename T>
	T BinaryExpressionModel<T>::evaluate() const
	{
		if (l != nullptr && r !=nullptr) {
			return evaluate(l,r);
		}
	}

	template<typename T>
	T BinaryExpressionModel<T>::evaluate(Expression<T>* l,Expression<T>*r) const
	{
		if (operat != nullptr) {
			return operat->evaluate(l,r);
		}
	}

}
#endif
