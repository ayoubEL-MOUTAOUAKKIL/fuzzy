#ifndef COGDEFUZZ_H
#define COGDEFUZZ_H

#include <numeric>
#include "../core/evaluator.h"
#include "MandaniDefuzz.h"
#include <vector>

namespace fuzzy {

	

	template<typename T>
	class CogDefuzz : public MandaniDefuzz<T> {

	public:
		virtual ~CogDefuzz() = default;
		typedef pair<vector<T>, vector<T>>Shape;
		virtual T defuzz(const Shape&)const;
	};

	template<typename T>
	T CogDefuzz<T>::defuzz(const Shape& s)const
	{

		typename vector<T>::const_iterator it = s.first.begin();
		typename vector<T>::const_iterator it2 = s.second.begin();

		T prod = T(0);

		vector<T> v; 
		vector<T> w; 

		for (; it != s.first.end(); ++it,++it2) {
			v.push_back((*it) * (*it2));
			w.push_back(*it2);
			//std::cout << std::endl << "-->" << *it2;
		}

		T sumXY = 0.0;
		T sumY = 0.0;
		//std::cout << std::endl << "-->left" << std::accumulate(v.begin(), v.end(), sumXY);
		//std::cout << std::endl << "-->right" << std::accumulate(w.begin(), w.end(), sumX)<< std::endl;
		return std::accumulate(v.begin(), v.end(), sumXY) / std::accumulate(w.begin(), w.end(), sumY);



	}

}











#endif
