#ifndef FACTORY_H
#define FACTORY_H

#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "valueModel.h"
#include <set>

namespace core
{

	template <typename T>
	class ExpressionFactory
	{
	public:
		using Memory = std::set<Expression<T>*>;

	public:
		virtual ~ExpressionFactory();

		virtual valueModel<T>* newValue(const T& value = T(0));
		virtual Expression<T>* hold(Expression<T>*);
		virtual BinaryExpressionModel<T>* newBinary(BinaryExpression<T>*, Expression<T>*, Expression<T>*);
		virtual UnaryExpressionModel<T>* newUnary(UnaryExpression<T>*, Expression<T>*);

	private:
		Memory memory;
	};

	
	template<typename T>
	ExpressionFactory<T>::~ExpressionFactory()
	{
		for (Expression<T>* e : memory) {
			delete e;
		}
	}


	template<typename T>
	Expression<T>* ExpressionFactory<T>::hold(Expression<T>* _e)
	{
		memory.insert(_e);
		return _e;
	}

	template<typename T>
	BinaryExpressionModel<T>* ExpressionFactory<T>::newBinary(BinaryExpression<T>* _oper, Expression<T>* _left, Expression<T>* _right)
	{
		return (BinaryExpressionModel<T>*)hold(new BinaryExpressionModel<T>(_oper,_left,_right));
	}

	template<typename T>
	UnaryExpressionModel<T>* ExpressionFactory<T>::newUnary(UnaryExpression<T>* _oper, Expression<T>* _operand)
	{
		return (UnaryExpressionModel<T>*)hold(new UnaryExpressionModel<T>(_oper, _operand));
	}

	template<typename T>
	valueModel<T>* ExpressionFactory<T>::newValue(const T& _value)
	{
		return (valueModel<T>*)hold(new valueModel<T>(_value));
	}

}




#endif