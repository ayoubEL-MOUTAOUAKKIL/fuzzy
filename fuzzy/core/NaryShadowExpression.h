#ifndef NARYSHADOWEXPRESSION_H
#define SHADOWNARYEXPRESSION_H



#include "expression.h"
#include <vector>
namespace core {


	template<typename T>
	class NaryShadowExpression : public NaryExpression<T>
	{
	public:
		NaryShadowExpression(NaryExpression<T>*);
		virtual ~NaryShadowExpression() = default;
		virtual T evaluate(std::vector<Expression<T>*>&)const;

		void changeTarget(NaryExpression<T>*);

	private:
		NaryExpression<T>* target;
	};
	template<typename T>
	NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T>* _e) :
		target(_e)
	{
	}
	template<typename T>
	T NaryShadowExpression<T>::evaluate(std::vector<Expression<T>*>& o)const
	{
		if (target != nullptr) {
			return target->evaluate(o);
		}
	}

	template<typename T>
	void NaryShadowExpression<T>::changeTarget(NaryExpression<T>* _t) {
		target(_t);
	}
}




#endif
