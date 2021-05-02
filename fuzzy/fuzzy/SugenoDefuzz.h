#ifndef SUGENODEFUZZ_H
#define SUGENODEFUZZ_H

#include "../core/Expression.h"
#include <vector>
namespace fuzzy {

	template<typename T>
	class sugenoDefuzz :core::NaryExpression<T> {
	public:
		virtual ~sugenoDefuzz() = default;
		T evaluate(std::vector<core::Expression<T>*>&);
	};
	template<typename T>
	T sugenoDefuzz<T>::evaluate(std::vector<core::Expression<T>*>& operands)
	{
		std::vector<core::Expression<T>*>::iterator it;

		T num = 0;
		T denum = 0;

		// calcul somme des wi
		for (it = operands->begin(); it != operands->end(); it++)
		{
			core::BinaryExpressionModel<T>* bem = (core::BinaryExpressionModel<T>*)  (*it);
			BinaryShadowExpression<T>* bse = (BinaryShadowExpression<T>*) bem->getOpe();
			SugenoThen<T>* sth = (SugenoThen<T>*) bse->getTarget();

			num += (*it)->evaluate();
			denum += sth->getPremiseValue();
		}

		if (denum != 0)
			return num / denum;
		else
			return 0;
	}
}
#endif
