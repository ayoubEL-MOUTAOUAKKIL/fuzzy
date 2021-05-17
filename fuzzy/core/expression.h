#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
namespace core {

	template<typename T>
	class Expression {
	public:
		virtual ~Expression() = default;
		virtual T evaluate()const = 0;
	};

	template<typename T>
	class UnaryExpression {
	public:
		virtual ~UnaryExpression() = default;
                virtual T evaluate(Expression<T>*) const = 0;
	};

	template<typename T>
	class BinaryExpression {
	public:
		virtual ~BinaryExpression() = default;
		virtual T evaluate(Expression<T>*, Expression<T>*)const = 0;
	};

	template<typename T>
	class NaryExpression {
	public:
		virtual ~NaryExpression() = default;
		virtual T evaluate(std::vector<Expression<T>*>&) const = 0;
	};
}


#endif
