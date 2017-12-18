#pragma once

#include <iostream>
#include <string>

#include "BayesIrisTest.hpp"
#include "BayesGlassTest.hpp"
#include "BayesCreditTest.hpp"
#include "BayesEcoliTest.hpp"

#include "ILAExampleTest.hpp"

#include "ILAIrisTest.hpp"
#include "ILACreditTest.hpp"
#include "ILAGlassTest.hpp"
#include "ILAEcoliTest.hpp"

#include "KNNIrisTest.hpp"
#include "KNNEcoliTest.hpp"
#include "KNNGlassTest.hpp"
#include "KNNSeedsTest.hpp"
#include "KNNLibrasTest.hpp"

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);

	//Classifier::Test::BayesTest::iris_bayes_test();
	//Classifier::Test::BayesTest::glass_bayes_test();
	//Classifier::Test::BayesTest::credit_bayes_test();
	//Classifier::Test::BayesTest::ecoli_bayes_test();

	//Classifier::Test::ILATest::example_1_ila_test();
	//Classifier::Test::ILATest::example_2_ila_test();

	//Classifier::Test::ILATest::iris_ila_test();
	//Classifier::Test::ILATest::glass_ila_test();
	//Classifier::Test::ILATest::credit_ila_test();
	//Classifier::Test::ILATest::ecoli_ila_test();

	Classifier::Test::KNNTest::iris_knn_test();
	//Classifier::Test::KNNTest::ecoli_knn_test();
	//Classifier::Test::KNNTest::glass_knn_test();
	//Classifier::Test::KNNTest::seeds_knn_test();
	//Classifier::Test::KNNTest::libras_knn_test();

	getchar();
}