#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"
#include "ClassSet.hpp"
#include "TransformerBuilder.hpp"
#include "DecimalDiscretizerBuilder.hpp"
#include "EvenDecimalDiscretizerBuilder.hpp"
#include "DiscreteDiscretizerBuilder.hpp"
#include "BayesClassifierBuilder.hpp"
#include "GaussianBayesClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;


namespace Classifier::Test::BayesTest {
	void ecoli_bayes_test()
	{
		cout << "ECOLI" << endl;

		using InitialSetType = FeatureSet<double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<string>;

		InitialSetType initialSet;
		ClassSetType classSet;

		Parser::CsvParser input;
		input.open("../Data/ecoli.data");
		for (int i = 0; i < 336; i++)
		{
			string name;
			double mcg;
			double gvh;
			double lip;
			double chg;
			double aac;
			double alm1;
			double alm2;
			string type;

			name = input.get<string>();
			mcg = input.get<double>();
			gvh = input.get<double>();
			lip = input.get<double>();
			chg = input.get<double>();
			aac = input.get<double>();
			alm1 = input.get<double>();
			alm2 = input.get<double>();
			type = input.get<string>();

			initialSet.push_back(mcg, gvh, lip, chg, aac, alm1, alm2);
			classSet.push_back(type);
		}
		input.close();

		//for (int i = 5; i < 100; i += 5)
		//{
		//	cout << i << endl;
		//
		//	auto featureSet = TransformerBuilder::from(initialSet)
		//		.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(i, initialSet))
		//		.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(i, initialSet))
		//		.add<2, int>(DiscreteDiscretizerBuilder::from<2>(initialSet))
		//		.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
		//		.add<4, int>(EvenDecimalDiscretizerBuilder::from<4>(i, initialSet))
		//		.add<5, int>(EvenDecimalDiscretizerBuilder::from<5>(i, initialSet))
		//		.add<6, int>(EvenDecimalDiscretizerBuilder::from<6>(i, initialSet))
		//		.transform();
		//
		//	auto crossValidator = Validation::CrossValidatorBuilder::from(
		//		Bayes::BayesClassifierBuilder::builder<string, 7>(),
		//		classSet,
		//		featureSet
		//	);
		//
		//	Validation::ValidationStatistics stats;
		//	for (int i = 0; i < 10; i++)
		//	{
		//		stats += crossValidator.validate(10);
		//	}
		//	cout << stats;
		//}

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(DecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(DecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(DiscreteDiscretizerBuilder::from<2>(initialSet))
			.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
			.add<4, int>(DecimalDiscretizerBuilder::from<4>(5, initialSet))
			.add<5, int>(DecimalDiscretizerBuilder::from<5>(5, initialSet))
			.add<6, int>(DecimalDiscretizerBuilder::from<6>(5, initialSet))
			.transform();



		//auto crossValidator = Validation::CrossValidatorBuilder::from(
		//	Bayes::GaussianBayesClassifierBuilder::builder<string, 7>(),
		//	classSet,
		//	initialSet
		//);

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			Bayes::BayesClassifierBuilder::builder<string, 7>(),
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 10; i++)
		{
			stats += crossValidator.validate(10);
		}
		cout << stats;
	}
}