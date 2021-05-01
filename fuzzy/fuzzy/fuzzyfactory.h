#ifndef FUZZYFACRORY_H
#define FUZZYFACTORY_H

#include "../core/factory.h"
#include "is.h"
#include "and.h"
#include  "or.h"
#include  "agg.h"
#include "then.h"
#include "not.h"
#include "MandaniDefuzz.h"

namespace fuzzy
{
	template <typename T>
	class FuzzyExpressionFactory : public core::ExpressionFactory<T>
	{
	public:
		FuzzyExpressionFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MandaniDefuzz<T>*);
		virtual ~FuzzyExpressionFactory() = default;

		void changeNot(Not<T>*);
		void changeAnd(And<T>*);
		void changeOr(Or<T>*);
		void changeThen(Then<T>*);
		void changeAgg(Agg<T>*);
		void changeMandanyDefuzz(MandaniDefuzz<T>*);

		virtual core::Expression<T>* newNot(core::Expression<T>*);
		virtual core::Expression<T>* newAnd(core::Expression<T>*,core::Expression<T>*);
		virtual core::Expression<T>* newOr(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newThen(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newAgg(core::Expression<T>*, core::Expression<T>*);
		virtual core::Expression<T>* newMandanidaniDefuzz(core::Expression<T>*, core::Expression<T>*,const T&, const T&, const T&);
		virtual core::Expression<T>* newIs(is<T>*, core::Expression<T>*);

	private:
		core::UnaryShadowExpression<T> opNot;
		core::BinaryShadowExpression<T> opAnd;
		core::BinaryShadowExpression<T> opOr;
		core::BinaryShadowExpression<T> opThen;
		core::BinaryShadowExpression<T> opAgg;
		core::BinaryShadowExpression<T> opMandaniDefuzz;
	};
	
	template<typename T>
	FuzzyExpressionFactory<T>::FuzzyExpressionFactory(Not<T>* _not, And<T>* _and, Or<T>* _or, Then<T>* _then, Agg<T>* _agg, MandaniDefuzz<T>* _defuzz):
		opNot((core::UnaryExpression<T>*)_not),
		opAnd((core::BinaryExpression<T>*)_and),
		opOr((core::BinaryExpression<T>*)_or),
		opThen((core::BinaryExpression<T>*)_then),
		opAgg((core::BinaryExpression<T>*)_agg),
		opMandaniDefuzz((core::BinaryExpression<T>*)_defuzz)
	{
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeNot(Not<T>* _o)
	{
		opNot.changeTarget(_o);
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeAnd(And<T>* _o)
	{
		opAnd.changeTarget(_o);
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeAgg(Agg<T>* _o)
	{
		opAgg.changeTarget(_o);
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeThen(Then<T>* _o)
	{
		opThen.changeTarget(_o);
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeOr(Or<T>* _o)
	{
		opOr.changeTarget(_o);
	}

	template<typename T>
	void FuzzyExpressionFactory<T>::changeMandanyDefuzz(MandaniDefuzz<T>* _o)
	{
		opMandaniDefuzz.changeTarget(_o);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newNot(core::Expression<T>* _o)
	{
		return this->newUnary((core::UnaryExpression<T>*) &opNot, _o);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newAnd(core::Expression<T>*_l, core::Expression<T>*_r)
	{
		return this->newBinary((core::BinaryExpression<T>*)&opAnd,_l,_r);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newOr(core::Expression<T>* _l, core::Expression<T>* _r)
	{
		return this->newBinary((core::BinaryExpression<T>*) &opOr, _l, _r);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newThen(core::Expression<T>* _l, core::Expression<T>* _r)
	{
		return this->newBinary((core::BinaryExpression<T>*) &opThen, _l, _r);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newAgg(core::Expression<T>* _l, core::Expression<T>* _r)
	{
		return this->newBinary((core::BinaryExpression<T>*) &opAgg, _l, _r);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newMandanidaniDefuzz(core::Expression<T>* _l, core::Expression<T>* _r, const T& _min, const T& _max, const T& _step)
	{
		core::BinaryExpression<T>* p = opMandaniDefuzz.getTarget();
		MandaniDefuzz<T>* m = (MandaniDefuzz<T>*) p;
		m->setMin(_min);
		m->setMax(_max);
		m->setMin(_step);
		return this->newBinary((core::BinaryExpression<T>*) &opMandaniDefuzz, _l, _r);
	}

	template<typename T>
	core::Expression<T>* FuzzyExpressionFactory<T>::newIs(is<T>* _i, core::Expression<T>* _o)
	{
		return this->newUnary((core::UnaryExpression<T>*) _i, _o);
	}


}

#endif