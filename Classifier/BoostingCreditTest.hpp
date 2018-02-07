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
#include "CrossValidatorBuilder.hpp"
#include "BoostingClassifierBuilder.hpp"
#include "MaxOccurrenceVoting.hpp"
#include "ErrorVoting.hpp"
#include "LinearVoting.hpp"
#include "AdaBoost.hpp"
#include "CreditReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;


namespace Classifier::Test::BoostingTest {
	void credit_boosting_test()
	{
		cout << "Boosting CREDIT" << endl;

		auto[initialSet, classSet] = CreditReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(DiscreteDiscretizerBuilder::from<0>(initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
			.add<4, int>(DiscreteDiscretizerBuilder::from<4>(initialSet))
			.add<5, int>(DiscreteDiscretizerBuilder::from<5>(initialSet))
			.add<6, int>(DiscreteDiscretizerBuilder::from<6>(initialSet))
			.add<7, int>(EvenDecimalDiscretizerBuilder::from<7>(5, initialSet))
			.add<8, int>(DiscreteDiscretizerBuilder::from<8>(initialSet))
			.add<9, int>(DiscreteDiscretizerBuilder::from<9>(initialSet))
			.add<10, int>(EvenDecimalDiscretizerBuilder::from<10>(5, initialSet))
			.add<11, int>(DiscreteDiscretizerBuilder::from<11>(initialSet))
			.add<12, int>(DiscreteDiscretizerBuilder::from<12>(initialSet))
			.add<13, int>(EvenDecimalDiscretizerBuilder::from<13>(5, initialSet))
			.add<14, int>(EvenDecimalDiscretizerBuilder::from<14>(5, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			ClassificationSet::Builders::Boosting::BoosingClassifierBuilder::builder<
			ClassificationSet::Builders::Boosting::BoostingAlgorithm::AdaBoost<string>,
			ClassificationSet::Voting::MaxOccurrenceVoting<string>
			>(
				Bayes::BayesClassifierBuilder::builder<string, 15>(),
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