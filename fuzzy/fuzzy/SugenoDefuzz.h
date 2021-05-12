#ifndef SUGENODEFUZZ_H
#define SUGENODEFUZZ_H

#include "../core/Expression.h"
#include "../core/BinaryShadowExpression.h"
#include "then.h"
#include <vector>
namespace fuzzy {

	template<typename T>
	class sugenoDefuzz :core::NaryExpression<T> {
	public:
		sugenoDefuzz() {};
		virtual ~sugenoDefuzz() = default;
		T evaluate(std::vector<core::Expression<T>*>&);
	};
	template<typename T>
	T sugenoDefuzz<T>::evaluate(std::vector<core::Expression<T>*>& operands)
	{
		typename std::vector<core::Expression<T>*>::iterator it;

		T num = 0;
		T denum = 0;

		
		for (it = operands.begin(); it != operands.end(); it++)
		{
			core::BinaryExpressionModel<T>* bem = (core::BinaryExpressionModel<T>*)  (*it);
			core::BinaryShadowExpression<T>* bse = (core::BinaryShadowExpression<T>*) bem->getOperat();
			SugenoThen<T>* sth = (SugenoThen<T>*)bse->getTarget();

			num += (*it)->evaluate();
			denum += sth->premiseValue();
		}

		if (denum != 0)
			return num / denum;
		else
			return 0;
	}
}
#endif
