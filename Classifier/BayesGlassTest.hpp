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
#include "KMeansDiscretizerBuilder.hpp"
#include "BayesClassifierBuilder.hpp"
#include "GaussianBayesClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;


namespace Classifier::Test::BayesTest {
	void glass_bayes_test()
	{
		cout << "GLASS" << endl;

		using InitialSetType = FeatureSet<double, double, double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<int>;

		InitialSetType initialSet;
		ClassSetType classSet;

		Parser::CsvParser input;
		input.open("../Data/glass.data");
		for (int i = 0; i < 214; i++)
		{
			int Id = input.get<int>();
			double RI = input.get<double>();
			double Na = input.get<double>();
			double Mg = input.get<double>();
			double Al = input.get<double>();
			double Si = input.get<double>();
			double K = input.get<double>();
			double Ca = input.get<double>();
			double Ba = input.get<double>();
			double Fe = input.get<double>();
			int Type = input.get<int>();

			//if (Type == 1 || Type == 3)
			//	Type = 100;
			//else if (Type == 2 || Type == 4)
			//	Type = 101;
			//else 
			//	Type = 102;

			//if (Type == 1 || Type == 2)
			//	Type = 100;
			//else if (Type == 3 || Type == 4)
			//	Type = 101;
			//else 
			//	Type = 102;

			initialSet.push_back(RI, Na, Mg, Al, Si, K, Ca, Ba, Fe);
			classSet.push_back(Type);
		}
		input.close();

		/*for (int i = 2; i < 30; i+=2)
		{
			cout << i << endl;

			auto featureSet = TransformerBuilder::from(initialSet)
				.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(i, initialSet))
				.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(i, initialSet))
				.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(i, initialSet))
				.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(i, initialSet))
				.add<4, int>(EvenDecimalDiscretizerBuilder::from<4>(i, initialSet))
				.add<5, int>(EvenDecimalDiscretizerBuilder::from<5>(i, initialSet))
				.add<6, int>(EvenDecimalDiscretizerBuilder::from<6>(i, initialSet))
				.add<7, int>(EvenDecimalDiscretizerBuilder::from<7>(i, initialSet))
				.add<8, int>(EvenDecimalDiscretizerBuilder::from<8>(i, initialSet))
				.transform();

			auto crossValidator = Validation::CrossValidatorBuilder::from(
				Bayes::BayesClassifierBuilder::builder<int, 9>(),
				classSet,
				featureSet
			);

			Validation::ValidationStatistics stats;
			for (int i = 0; i < 10; i++)
			{
				stats += crossValidator.validate(10);
			}
			cout << stats;
		}*/

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(5, initialSet))
			.add<4, int>(EvenDecimalDiscretizerBuilder::from<4>(5, initialSet))
			.add<5, int>(EvenDecimalDiscretizerBuilder::from<5>(5, initialSet))
			.add<6, int>(EvenDecimalDiscretizerBuilder::from<6>(5, initialSet))
			.add<7, int>(EvenDecimalDiscretizerBuilder::from<7>(5, initialSet))
			.add<8, int>(EvenDecimalDiscretizerBuilder::from<8>(5, initialSet))
			.transform();

		//auto featureSet = TransformerBuilder::from(initialSet)
		//	.add<0, int>(KMeansDiscretizerBuilder::from<0>(5, initialSet))
		//	.add<1, int>(KMeansDiscretizerBuilder::from<1>(5, initialSet))
		//	.add<2, int>(KMeansDiscretizerBuilder::from<2>(5, initialSet))
		//	.add<3, int>(KMeansDiscretizerBuilder::from<3>(5, initialSet))
		//	.add<4, int>(KMeansDiscretizerBuilder::from<4>(5, initialSet))
		//	.add<5, int>(KMeansDiscretizerBuilder::from<5>(5, initialSet))
		//	.add<6, int>(KMeansDiscretizerBuilder::from<6>(5, initialSet))
		//	.add<7, int>(KMeansDiscretizerBuilder::from<7>(5, initialSet))
		//	.add<8, int>(KMeansDiscretizerBuilder::from<8>(5, initialSet))
		//	.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			Bayes::BayesClassifierBuilder::builder<int, 9>(),
			classSet, 
			featureSet
		);

		//auto featureSet = initialSet;
		//
		//auto crossValidator = Validation::CrossValidatorBuilder::from(
		//	Bayes::GaussianBayesClassifierBuilder::builder<int, 9>(),
		//	classSet, 
		//	featureSet
		//);

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 10; i++)
		{
			stats += crossValidator.validate(10);
		}
		cout << stats;
	}
}