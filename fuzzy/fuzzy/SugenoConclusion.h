#ifndef SUGENOCONCLUSION_H
#define SUGENOCONCLUSION_H

#include "../core/Expression.h"
#include <vector>


namespace fuzzy {
	template<typename T>
	class SugenoConclusion :public core::NaryExpression<T> {

	public:
		SugenoConclusion(std::vector<T>&);
		virtual ~SugenoConclusion() = default;
		virtual T evaluate(std::vector<core::Expression<T>*>&)const;
		std::vector<core::Expression<T>*> getCoeff() const;

	private:
		std::vector<T> coeff;
	};

	


	template<typename T>
	SugenoConclusion<T>::SugenoConclusion(std::vector<T>& _coeff):
		coeff(_coeff)
	{
	}

	template <class T>
	T SugenoConclusion<T>::evaluate(std::vector<core::Expression<T>*>& operands) const
	{
		typename vector<T>::const_iterator it = coeff.begin();
		typename vector<core::Expression<T>*>::const_iterator ite = operands.begin();
			
		T z = 0;

		for (; ite != operands.end() && it != coeff.end(); ite++, it++)
		{
			T eval = (*ite)->evaluate();
			z += (*it) * eval;
		}

		return z;
	}

	template<typename T>
	std::vector<core::Expression<T>*> SugenoConclusion<T>::getCoeff()const
	{
		return coeff;
	}



}




#endif