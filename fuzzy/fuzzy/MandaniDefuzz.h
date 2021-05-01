#ifndef MANDANIDEFUZ_H
#define MANDANIDEFUZ_H

#include "../core/evaluator.h"
#include "../core/expression.h"

namespace fuzzy {

	template<typename T>
	class MandaniDefuzz : public core::BinaryExpression<T> {

	public:
		MandaniDefuzz();
		MandaniDefuzz(T&, T&, T&);
		virtual ~MandaniDefuzz() = default;
		virtual T evaluate(core::Expression<T>*,core::Expression<T>*)const;
		typedef pair<vector<T>, vector<T>>Shape;
		virtual T defuzz(const Shape&)const= 0;

		virtual void setMin(const T& _min);
		virtual void setMax(const T& _max);
		virtual void setStep(const T& _step);

	private:
		T min, max, step;
	};

	template<typename T>
	MandaniDefuzz<T>::MandaniDefuzz():
		min(T(0)),max(T(10)),step(T(0.5))
	{
	}

	template<typename T>
	MandaniDefuzz<T>::MandaniDefuzz(T& _min, T& _max, T& _step):
		min(_min),max(_max),step(_step)
	{
	}
	template<typename T>
	T MandaniDefuzz<T>::evaluate(core::Expression<T>* _e1, core::Expression<T>* _e2)const {
		core::Evaluator<T> e;
		return defuzz(e.BuildShape(min, max, step,(core::valueModel<T>*) _e1, _e2));
	}

	template<typename T>
	void MandaniDefuzz<T>::setMin(const T& _min)
	{
		min = _min;
	}

	template<typename T>
	void MandaniDefuzz<T>::setMax(const T& _max)
	{
		max = _max;
	}

	template<typename T>
	void MandaniDefuzz<T>::setStep(const T& _step)
	{
		step = _step;
	}

}


#endif