#pragma once

#include <iostream>
#include <string>

#include "BayesIrisTest.hpp"
#include "BayesGlassTest.hpp"
#include "BayesCreditTest.hpp"
#include "BayesEcoliTest.hpp"

#include "ILAIrisTest.hpp"

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);

	//Classifier::Test::BayesTest::iris_bayes_test();
	//Classifier::Test::BayesTest::glass_bayes_test();
	//Classifier::Test::BayesTest::credit_bayes_test();
	//Classifier::Test::BayesTest::ecoli_bayes_test();

	Classifier::Test::ILATest::iris_ila_test();

	getchar();
}