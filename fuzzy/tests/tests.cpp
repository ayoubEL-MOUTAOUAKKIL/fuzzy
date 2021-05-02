#include <iostream>
#include <fstream>
#include <cassert>

#include "../core/expression.h"
#include "../core/valueModel.h"
#include "../core/BinaryExpressionModel.h"
#include "../core/UnaryExpressionModel.h"
#include "../core/BinaryShadowExpression.h"
#include "../core/UnaryShadowExpression.h"
#include "../core/factory.h"

#include "../fuzzy/CogDefuzz.h"
#include "../fuzzy/SugenoConclusion.h"
#include "../fuzzy/SugenoDefuzz.h"
#include "../core/evaluator.h"
#include "../fuzzy/or.h"
#include "../fuzzy/and.h"
#include "../fuzzy/then.h"
#include "../fuzzy/agg.h"
#include "../fuzzy/not.h"
#include "../fuzzy/is.h"
#include "../fuzzy/fuzzyfactory.h"


#include "tests.h"
#include "../fuzzy/CogDefuzz.h"



using NUMERIC = double;

void testValueModel() {
	std::cout << std::endl << "-------------------ValueModelTest--------------------";
	core::valueModel<NUMERIC> v1;
	assert(v1.evaluate() == 0);

	v1.setValue(0.2);
	assert(v1.evaluate() == 0.2);

	std::cout << std::endl << "passed";
}

void testOrMax() {
	std::cout << std::endl << "-------------------OrMaxTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::OrMax<NUMERIC> orMax;

	v1.setValue(0.5);
	v2.setValue(0.6);
	assert(orMax.evaluate(&v1, &v2) == 0.6);

	std::cout << std::endl << "passed";
}

void testOrPlus() {
	std::cout << std::endl << "-------------------OrPlusTest-----------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::OrPlus<NUMERIC> orPlus;

	v1.setValue(0.5);
	v2.setValue(0.6);
	const NUMERIC res = round(orPlus.evaluate(&v1, &v2) * 100);
	assert(res == 80);

	std::cout << std::endl << "passed";
}

void testAndMin() {
	std::cout << std::endl << "-------------------AndMinTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::AndMin<NUMERIC> andMin;

	v1.setValue(0.2);
	v2.setValue(0.4);
	assert(andMin.evaluate(&v1, &v2) == 0.2);

	std::cout << std::endl << "passed";
}

void testAndMult() {
	std::cout << std::endl << "-------------------AndMultTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::AndMult<NUMERIC> andMult;

	v1.setValue(0.4);
	v2.setValue(0.6);
	assert(andMult.evaluate(&v1, &v2) == 0.24);

	std::cout << std::endl << "passed";
}

void testThenMin() {
	std::cout << std::endl << "-------------------ThenMinTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::ThenMin<NUMERIC> thenMin;

	v1.setValue(0.5);
	v2.setValue(0.6);
	assert(thenMin.evaluate(&v1, &v2) == 0.5);

	std::cout << std::endl << "passed";
}

void testThenMult() {
	std::cout << std::endl << "-------------------ThenMultTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::ThenMult<NUMERIC> thenMult;

	v1.setValue(0.4);
	v2.setValue(0.5);
	assert(thenMult.evaluate(&v1, &v2) == 0.20);

	std::cout << std::endl << "passed";
}

void testSugenoThen() {
	std::cout << std::endl << "-------------------SugenoThenTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::SugenoThen<NUMERIC> sugenoThen;

	v1.setValue(0.4);
	v2.setValue(0.5);
	assert(sugenoThen.evaluate(&v1, &v2) == 0.20);
	assert(sugenoThen.premiseValue() == 0.4);

	std::cout << std::endl << "passed";
}


void testAggMax() {
	std::cout << std::endl << "-------------------AggMaxTest------------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::AggMax<NUMERIC> aggMax;

	v1.setValue(0.4);
	v2.setValue(0.9);
	assert(aggMax.evaluate(&v1, &v2) == 0.9);

	std::cout << std::endl << "passed";
}

void testAggPlus() {
	std::cout << std::endl << "-------------------AggPlusTest-----------------------";
	core::valueModel<NUMERIC> v1;
	core::valueModel<NUMERIC> v2;

	fuzzy::OrPlus<NUMERIC> orPlus;

	v1.setValue(0.5);
	v2.setValue(0.6);
	const NUMERIC res = round(orPlus.evaluate(&v1, &v2) * 100);
	assert(res == 80);

	std::cout << std::endl << "passed";
}


void testNotMinus1() {
	std::cout << std::endl << "-------------------NotMinus1Test-----------------------";
	core::valueModel<NUMERIC> v1(0.9);
	fuzzy::NotMinus1<NUMERIC> e;

	const NUMERIC res = round(e.evaluate(&v1) * 100);
	assert(res == 10);

	std::cout << std::endl << "passed";
}

void testIsTriangle()
{
	std::cout << std::endl << "-------------------IsTriangleTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isTriangle<NUMERIC> triangle(3, 5, 8);
	core::UnaryExpressionModel<NUMERIC> enTriangle(&triangle, &v);
	std::ofstream fout("triangle.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enTriangle);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "triangle.csv generated";
}

void testIsTrapeze()
{
	std::cout << std::endl << "-------------------IsTrapezeTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isTrapeze<NUMERIC> trapeze(0,3, 5, 7);
	core::UnaryExpressionModel<NUMERIC> enTrapeze(&trapeze, &v);
	std::ofstream fout("trapeze.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enTrapeze);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "trapeze.csv generated";
}

void testIsTrapezeLeft()
{
	std::cout << std::endl << "-------------------IsTrapezeLeftTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isTrapezeLeft<NUMERIC> trapezeLeft(5, 7);
	core::UnaryExpressionModel<NUMERIC> enTrapezeLeft(&trapezeLeft, &v);
	std::ofstream fout("trapezeLeft.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enTrapezeLeft);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "trapezeLeft.csv generated";
}

void testIsTrapezeRight()
{
	std::cout << std::endl << "-------------------IsTrapezeRightTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isTrapezeRight<NUMERIC> trapezeRight(5, 7);
	core::UnaryExpressionModel<NUMERIC> enTrapezeRight(&trapezeRight, &v);
	std::ofstream fout("trapezeRight.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enTrapezeRight);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "trapezeRight.csv generated";
}

void testIsGaussian()
{
	std::cout << std::endl << "-------------------IsGaussianTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isGaussian<NUMERIC> gaussian(6, 2);
	core::UnaryExpressionModel<NUMERIC> enGaussian(&gaussian, &v);
	std::ofstream fout("gaussian.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enGaussian);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "gaussian.csv generated";
}

void testIsBell()
{
	std::cout << std::endl << "-------------------IsBellTest-----------------------";
	core::valueModel<NUMERIC> v;
	fuzzy::isBell<NUMERIC> bell(1,3,7 );
	core::UnaryExpressionModel<NUMERIC> enBell(&bell, &v);
	std::ofstream fout("bell.csv");
	const core::Evaluator<NUMERIC>::Shape shape = core::Evaluator<NUMERIC>::BuildShape(0, 10, 0.5, &v, &enBell);
	core::Evaluator<NUMERIC>::PrintShape(fout, shape);

	std::cout << std::endl << "bell.csv generated";
}


void testTips() {
	using namespace fuzzy;
	using namespace core;

	using Not = fuzzy::NotMinus1<NUMERIC>;
	using AndMin = fuzzy::AndMin<NUMERIC>;
	using OrMax = fuzzy::OrMax<NUMERIC>;
	using ThenMin = fuzzy::ThenMin<NUMERIC>;
	using AggMax = fuzzy::AggMax<NUMERIC>;
	using CogDefuzz = fuzzy::CogDefuzz<NUMERIC>;
	using FuzzyExpressionFactory = FuzzyExpressionFactory<NUMERIC>;
	using IsTriangle = fuzzy::isTriangle<NUMERIC>;
	using Value = core::valueModel<NUMERIC>;
	using Expression = core::Expression<NUMERIC>;


	Not opNot;
	AndMin opAnd;
	OrMax opOr;
	ThenMin opThen;
	AggMax opAgg;
	CogDefuzz opMDefuzz;

	FuzzyExpressionFactory f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMDefuzz);

	IsTriangle poor(-5, 0, 5);
	IsTriangle good(0, 5, 10);
	IsTriangle excellent(5, 10, 15);

	IsTriangle cheap(0, 5, 10);
	IsTriangle average(10, 15, 20);
	IsTriangle generous(20, 25, 30);

	Value service(0);
	Value food(5);
	Value tips(0);

	Expression* r =
		f.newAgg(
			f.newAgg(
				f.newThen(
					f.newIs(&poor, &service),
					f.newIs(&cheap, &tips)
				),
				f.newThen(
					f.newIs(&good, &service),
					f.newIs(&average, &tips)
				)
			),
			f.newThen(
				f.newIs(&excellent, &service),
				f.newIs(&generous, &tips)
			)
		);

	Expression* system = f.newMandanidaniDefuzz(&tips, r, 0, 30, 1);

	NUMERIC s = 1;

	while (s >= 0) {
		std::cout << std::endl << "service : "; std::cin >> s;
		service.setValue(s);
		std::cout << std::endl << "tips -> ";
		std::cout << system->evaluate();
	}
	

}

void testSugeno() {
	using namespace fuzzy;
	using namespace core;

	using Not = fuzzy::NotMinus1<NUMERIC>;
	using AndMin = fuzzy::AndMin<NUMERIC>;
	using OrMax = fuzzy::OrMax<NUMERIC>;
	using ThenMin = fuzzy::ThenMin<NUMERIC>;
	using AggMax = fuzzy::AggMax<NUMERIC>;
	using CogDefuzz = fuzzy::CogDefuzz<NUMERIC>;
	using FuzzyExpressionFactory = FuzzyExpressionFactory<NUMERIC>;
	using IsTriangle = fuzzy::isTriangle<NUMERIC>;
	using Value = core::valueModel<NUMERIC>;
	using Expression = core::Expression<NUMERIC>;


	Not opNot;
	AndMin opAnd;
	OrMax opOr;
	ThenMin opThen;
	AggMax opAgg;
	CogDefuzz opMDefuzz;

	FuzzyExpressionFactory f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opMDefuzz);

	IsTriangle poor(-5, 0, 5);
	IsTriangle good(0, 5, 10);
	IsTriangle excellent(5, 10, 15);

	IsTriangle cheap(0, 5, 10);
	IsTriangle average(10, 15, 20);
	IsTriangle generous(20, 25, 30);

	Value service(0);
	Value food(5);
	Value tips(0);
	Expression* r =
		f.newAgg(
			f.newAgg(
				f.newThen(
					f.newIs(&poor, &service),
					f.newIs(&cheap, &tips)
				),
				f.newThen(
					f.newIs(&good, &service),
					f.newIs(&average, &tips)
				)
			),
			f.newThen(
				f.newIs(&excellent, &service),
				f.newIs(&generous, &tips)
			)
		);

	Expression* r2 =
		f.newAgg(
			f.newAgg(
				f.newThen(
					f.newIs(&poor, &service),
					f.newIs(&cheap, &tips)
				),
				f.newThen(
					f.newIs(&good, &service),
					f.newIs(&average, &tips)
				)
			),
			f.newThen(
				f.newIs(&excellent, &service),
				f.newIs(&generous, &tips)
			)
		);

	std::vector<NUMERIC> v;
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	std::vector<core::Expression<NUMERIC>*> e;
	e.push_back(r);
	e.push_back(r2);
	fuzzy::SugenoConclusion<NUMERIC> a(v);
	fuzzy::sugenoDefuzz<NUMERIC> ab();

}

void tests()
{
	testValueModel();
	testOrMax();
	testOrPlus();
	testAndMin();
	testAndMult();
	testThenMin();
	testThenMult();
	testSugenoThen();
	testAggMax();
	testAggPlus();
	testNotMinus1();
	testIsTriangle();
	testIsTrapeze();
	testIsTrapezeLeft();
	testIsTrapezeRight();
	testIsGaussian();
	testIsBell();
	testSugeno();
	testTips();
}