#include "../core/expression.h"
#ifndef IS_H
#define IS_H


namespace fuzzy {

	template<typename T>
	class is :public core::UnaryExpression<T> {
	};
	/*triangle*/
	template<typename T>
	class isTriangle : public is<T> {
	public:
		isTriangle(const T& _min = T(0), const T& _mid = T(0), const T& _max = T(0));
		virtual ~isTriangle() = default;

		T getMin()const;
		T getMax()const;
		T getMid()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T min, mid, max;
	};

	template<typename T>
	isTriangle<T>::isTriangle(const T& _min, const T& _mid, const T& _max) :
		min(_min), mid(_mid), max(_max)
	{
	}

	template<typename T>
	T isTriangle<T>::getMin()const
	{
		return min;
	}

	template<typename T>
	T isTriangle<T>::getMid()const
	{
		return mid;
	}

	template<typename T>
	T isTriangle<T>::getMax()const
	{
		return max;
	}

	template<typename T>
	T isTriangle<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();

		if ((ev < min) || (ev > max)) {
			return 0;
		}

		if (ev <= mid) {
			return (ev - min) / (mid - min);
		}

		return (max - ev) / (max - mid);
	}

	/*trapeze*/

	template<typename T>
	class isTrapeze : public is<T> {
	public:
		isTrapeze(const T& _min = T(0), const T& _mid1 = T(0), const T& _mid2 = T(0), const T& _max = T(0));
		virtual ~isTrapeze() = default;

		T getMin()const;
		T getMax()const;
		T getMid1()const;
		T getMid2()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T min, mid1, mid2, max;
	};

	template<typename T>
	isTrapeze<T>::isTrapeze(const T& _min, const T& _mid1, const T& _mid2, const T& _max) :
		min(_min), mid1(_mid1), mid2(_mid2), max(_max)
	{
	}

	template<typename T>
	T isTrapeze<T>::getMin()const
	{
		return min;
	}

	template<typename T>
	T isTrapeze<T>::getMid1()const
	{
		return mid1;
	}
	template<typename T>
	T isTrapeze<T>::getMid2()const
	{
		return mid2;
	}

	template<typename T>
	T isTrapeze<T>::getMax()const
	{
		return max;
	}

	template<typename T>
	T isTrapeze<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();

		if ((ev < min) || (ev > max)) {
			return 0;
		}

		if ((ev < mid1) && (ev >= min)) {
			return (ev - min) / (mid1 - min);
		}

		if ((ev <= mid2) && (ev >= mid1)) {
			return 1;
		}

		return (max - ev) / (max - mid2);
	}

	/*trapeze gauche*/
	template<typename T>
	class isTrapezeLeft : public is<T> {
	public:
		isTrapezeLeft(const T& _mid = T(0), const T& _max = T(0));
		virtual ~isTrapezeLeft() = default;

		T getMax()const;
		T getMid()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T mid, max;
	};

	template<typename T>
	isTrapezeLeft<T>::isTrapezeLeft(const T& _mid, const T& _max) :
		mid(_mid), max(_max)
	{
	}


	template<typename T>
	T isTrapezeLeft<T>::getMid()const
	{
		return mid;
	}
	

	template<typename T>
	T isTrapezeLeft<T>::getMax()const
	{
		return max;
	}

	template<typename T>
	T isTrapezeLeft<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();

		if (ev <= mid) {
			return 1;
		}

		if ((ev > mid) && (ev < max)) {
			return (max - ev) / (max - mid);
		}

		return 0;
	}

	/*trapeze droite*/
	template<typename T>
	class isTrapezeRight : public is<T> {
	public:
		isTrapezeRight(const T& _mid = T(0), const T& _max = T(0));
		virtual ~isTrapezeRight() = default;

		T getMax()const;
		T getMid()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T mid, max;
	};

	template<typename T>
	isTrapezeRight<T>::isTrapezeRight(const T& _mid, const T& _max) :
		mid(_mid), max(_max)
	{
	}


	template<typename T>
	T isTrapezeRight<T>::getMid()const
	{
		return mid;
	}


	template<typename T>
	T isTrapezeRight<T>::getMax()const
	{
		return max;
	}

	template<typename T>
	T isTrapezeRight<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();

		if (ev <= mid) {
			return 0;
		}

		if ((ev > mid) && (ev < max)) {
			return (ev - mid) / (max - mid);
		}

		return 1;
	}

	/*gaussian*/
	template<typename T>
	class isGaussian : public is<T> {
	public:
		isGaussian(const T& _tau = T(0), const T& _c = T(0));
		virtual ~isGaussian() = default;

		T getC()const;
		T getTau()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T c, tau;
	};

	template<typename T>
	isGaussian<T>::isGaussian(const T& _c, const T& _tau) :
		c(_c), tau(_tau)
	{
	}


	template<typename T>
	T isGaussian<T>::getC()const
	{
		return c;
	}


	template<typename T>
	T isGaussian<T>::getTau()const
	{
		return tau;
	}

	template<typename T>
	T isGaussian<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();


		return exp(-(ev - c)*(ev - c)/(2*tau*tau));
	}

	/*bell*/
	template<typename T>
	class isBell : public is<T> {
	public:
		isBell(const T& _min = T(0), const T& _mid = T(0), const T& _max = T(0));
		virtual ~isBell() = default;

		T getMin()const;
		T getMax()const;
		T getMid()const;

		virtual T evaluate(core::Expression<T>*)const;

	private:
		T min, mid, max;
	};

	template<typename T>
	isBell<T>::isBell(const T& _min, const T& _mid, const T& _max) :
		min(_min), mid(_mid), max(_max)
	{
	}

	template<typename T>
	T isBell<T>::getMin()const
	{
		return min;
	}

	template<typename T>
	T isBell<T>::getMid()const
	{
		return mid;
	}

	template<typename T>
	T isBell<T>::getMax()const
	{
		return max;
	}

	template<typename T>
	T isBell<T>::evaluate(core::Expression<T>* _e1)const
	{
		const T ev = _e1->evaluate();

		return 1 / (1 + pow(abs((ev - max) / min), 2 * mid));
	}
}

#endif