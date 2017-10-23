#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"
#include "ClassSet.hpp"
#include "Transformer.hpp"
#include "DecimalDiscretizer.hpp"
#include "EvenDecimalDiscretizer.hpp"
#include "BayesClassifier.hpp"
#include "CrossValidator.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;


namespace Classifier::Test::Glass {
	void glass_test()
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

			initialSet.push_back(RI, Na, Mg, Al, Si, K, Ca, Ba, Fe);
			classSet.push_back(Type);
		}
		input.close();

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

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			Bayes::BayesClassifierBuilder::builder<int, 9>(),
			classSet, 
			featureSet
		);
		crossValidator.validate(10);
	}
}