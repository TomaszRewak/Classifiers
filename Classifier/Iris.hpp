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

namespace Classifier::Test::Iris {
	void iris_test()
	{
		cout << "IRIS" << endl;

		using InitialSetType = FeatureSet<double, double, double, double>;
		using ClassSetType = ClassSet<string>;

		InitialSetType initialSet;
		ClassSetType classSet;

		Parser::CsvParser input;
		input.open("../Data/iris.data");
		for (int i = 0; i < 150; i++)
		{
			double sepal_length = input.get<double>();
			double sepal_width = input.get<double>();
			double petal_length = input.get<double>();
			double petal_width = input.get<double>();
			string Type = input.get<string>();

			initialSet.push_back(sepal_length, sepal_width, petal_length, petal_width);
			classSet.push_back(Type);
		}
		input.close();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(5, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			Bayes::BayesClassifierBuilder::builder<string, 4>(),
			classSet,
			featureSet
		);
		crossValidator.validate(10);
	}
}