#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include "expression.h"
#include "valueModel.h"
#include <ostream>
using namespace std;

namespace core {

	template<class T>
	class Evaluator {
	public:
		class EvalFunc
		{
		public:
			virtual T operator () (const T&) = 0;
		};
		typedef pair<vector<T>, vector<T>>Shape;

		static Shape BuildShape(const T&, const T& ,const T&,valueModel<T>*,Expression<T>*);
		static ostream& PrintShape(ostream&,const Shape& s);
	};

	template<class T>
	typename Evaluator<T>::Shape Evaluator<T>::BuildShape(const T& min, const T& max, const T& step, valueModel<T>* vm, Expression<T>* e)
	{
		vector<T> x, y;

		for (T i = min; i <= max; i += step) {
			vm->setValue(i);
			y.push_back(e->evaluate());
			x.push_back(i);
		}

		return Shape(x, y);

	}

	template<class T>
	ostream& Evaluator<T>::PrintShape(ostream& os, const Shape& s) {
		typename vector<T>::const_iterator it = s.first.begin();
		for (; it != s.first.end(); ++it) {
			os << *it << ';';
		}
		os << endl;

		it = s.second.begin();
		for (; it != s.second.end(); ++it) {
			os << *it << ';';
		}
		return os;

	}

	
}



#endif