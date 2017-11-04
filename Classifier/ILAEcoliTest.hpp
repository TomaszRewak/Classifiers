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
#include "ILAClassifierBuilder.hpp"
#include "GaussianBayesClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"
#include "EcoliReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;


namespace Classifier::Test::ILATest {
	void ecoli_ila_test()
	{
		cout << "ILA ECOLI" << endl;

		auto[initialSet, classSet] = EcoliReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(DiscreteDiscretizerBuilder::from<2>(initialSet))
			.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
			.add<4, int>(EvenDecimalDiscretizerBuilder::from<4>(5, initialSet))
			.add<5, int>(EvenDecimalDiscretizerBuilder::from<5>(5, initialSet))
			.add<6, int>(EvenDecimalDiscretizerBuilder::from<6>(5, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			ILA::ILAClassifierBuilder::builder<string, 7>("other"),
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats = crossValidator.validate(10);
		cout << stats;
	}
}