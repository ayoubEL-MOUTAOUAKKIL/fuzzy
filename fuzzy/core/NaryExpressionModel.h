#ifndef NARYEXPRESSIONMODEL_H
#define NARYEXPRESSIONMODEL_H

#include "expression.h"
#include <vector>

namespace core {

	template<typename T>
	class NaryExpressionModel : public NaryExpression<T>, Expression<T> {

	public:
		NaryExpressionModel(Expression<T>*, std::vector<Expression<T>*>&);
		virtual T evaluate()const;
		virtual T evaluate(std::vector<Expression<T>*>&)const;

	private:
		Expression<T>* operat;
		std::vector<Expression<T>*>& operands;

	};

	template<typename T>
	NaryExpressionModel<T>::NaryExpressionModel(Expression<T>* _operat, std::vector<Expression<T>*>& _operands):
		operat(_operat),operands(_operands)
	{
	}

	template<typename T>
	T NaryExpressionModel<T>::evaluate() const
	{
		if (operands != NULL) {
			return evaluate(operands)
		}
	}
	template<typename T>
	inline T NaryExpressionModel<T>::evaluate(std::vector<Expression<T>*>& _operands) const
	{
		if (operat != = nullptr) {
			return  operat->evaluate(operands);
		}
	}
}






#endif
