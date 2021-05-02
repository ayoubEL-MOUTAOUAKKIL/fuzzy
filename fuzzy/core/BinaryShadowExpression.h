#ifndef BINARYSHADOWEXPRESSION_H
#define BINARYSHADOWEXPRESSION_H

#include "expression.h"
namespace core {

	template<typename T>
	class BinaryShadowExpression : public BinaryExpression<T>
	{
	public:
		BinaryShadowExpression(BinaryExpression<T>*);
		virtual ~BinaryShadowExpression() = default;
		virtual T evaluate(Expression<T>*, Expression<T>*)const;

		void changeTarget(BinaryExpression<T>*);

		BinaryExpression<T>* getTarget()const;

	private:
		BinaryExpression<T>* target;
	};
	template<typename T>
	BinaryShadowExpression<T>::BinaryShadowExpression(BinaryExpression<T>* _e) :
		target(_e)
	{
	}
	template<typename T>
	T BinaryShadowExpression<T>::evaluate(Expression<T>* _l, Expression<T>* _r)const
	{
		if (target != nullptr) {
			return target->evaluate(_l, _r);
		}
	}

	template<typename T>
	void BinaryShadowExpression<T>::changeTarget(BinaryExpression<T>* _t) {
		target(_t);
	}
	template<typename T>
	BinaryExpression<T>* BinaryShadowExpression<T>::getTarget() const
	{
		return target;
	}
}

#endif