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
#include "BayesClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"
#include "IrisReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::BayesTest {
	void iris_bayes_test()
	{
		cout << "Bayes IRIS" << endl;

		auto[initialSet, classSet] = IrisReader::read();

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

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 10; i++)
		{
			stats += crossValidator.validate(10);
		}
		cout << stats;
	}
}