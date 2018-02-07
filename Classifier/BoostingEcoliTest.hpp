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
#include "BoostingClassifierBuilder.hpp"
#include "ErrorVoting.hpp"
#include "MaxOccurrenceVoting.hpp"
#include "ErrorVoting.hpp"
#include "LinearVoting.hpp"
#include "MultiplyBoost.hpp"
#include "BoostingClassifierBuilder.hpp"
#include "AdaBoost.hpp"
#include "EcoliReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;


namespace Classifier::Test::BoostingTest {
	void ecoli_boosting_test()
	{
		cout << "BOOSTING ECOLI" << endl;

		auto[initialSet, classSet] = EcoliReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(DecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(DecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(DiscreteDiscretizerBuilder::from<2>(initialSet))
			.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
			.add<4, int>(DecimalDiscretizerBuilder::from<4>(5, initialSet))
			.add<5, int>(DecimalDiscretizerBuilder::from<5>(5, initialSet))
			.add<6, int>(DecimalDiscretizerBuilder::from<6>(5, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			ClassificationSet::Builders::Boosting::BoosingClassifierBuilder::builder<
			ClassificationSet::Builders::Boosting::BoostingAlgorithm::AdaBoost<string>,
			ClassificationSet::Voting::LinearVoting<string>
			>(
				Bayes::BayesClassifierBuilder::builder<string, 7>(),
				20
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