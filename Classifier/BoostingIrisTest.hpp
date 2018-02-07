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
#include "BoostingClassifierBuilder.hpp"
#include "AdaBoost.hpp"
#include "MaxOccurrenceVoting.hpp"
#include "ErrorVoting.hpp"
#include "CrossValidatorBuilder.hpp"
#include "IrisReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::BoostingTest {
	void iris_boosting_test()
	{
		cout << "Boosting IRIS" << endl;

		auto[initialSet, classSet] = IrisReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(5, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			ClassificationSet::Builders::Boosting::BoosingClassifierBuilder::builder<
			ClassificationSet::Builders::Boosting::BoostingAlgorithm::AdaBoost<string>,
			ClassificationSet::Voting::MaxOccurrenceVoting<string>
			>(
				Bayes::BayesClassifierBuilder::builder<string, 4>(),
				10
				),
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 100; i++)
		{
			stats += crossValidator.validate(10);
		}
		cout << stats << endl;
	}
}