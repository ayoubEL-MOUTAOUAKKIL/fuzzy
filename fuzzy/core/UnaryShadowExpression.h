#ifndef UNARYSHADOWEXPRESSION_H
#define UNARYSHADOWEXPRESSION_H

#include "expression.h"
namespace core {


	template<typename T>
	class UnaryShadowExpression : public UnaryExpression<T>
	{
	public:
		UnaryShadowExpression(UnaryExpression<T>*);
		virtual ~UnaryShadowExpression() = default;
		virtual T evaluate(Expression<T>*)const;

		void changeTarget(UnaryExpression<T>*);

	private:
		UnaryExpression<T>* target;
	};
	template<typename T>
	UnaryShadowExpression<T>::UnaryShadowExpression(UnaryExpression<T>* _e):
		target(_e)
	{
	}
	template<typename T>
	T UnaryShadowExpression<T>::evaluate(Expression<T>* o)const
	{
		if (target != nullptr) {
			return target->evaluate(o);
		}
	}

	template<typename T>
	void UnaryShadowExpression<T>::changeTarget(UnaryExpression<T>* _t) {
		target(_t);
	}
}


#endif