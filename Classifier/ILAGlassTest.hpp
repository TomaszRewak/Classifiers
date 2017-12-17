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
#include "ILAClassifierBuilder.hpp"
#include "GaussianBayesClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"
#include "GlassReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::ILATest {
	void glass_ila_test()
	{
		cout << "ILA GLASS" << endl;

		auto[initialSet, classSet] = GlassReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(3, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(3, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(3, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(3, initialSet))
			.add<4, int>(EvenDecimalDiscretizerBuilder::from<4>(3, initialSet))
			.add<5, int>(EvenDecimalDiscretizerBuilder::from<5>(3, initialSet))
			.add<6, int>(EvenDecimalDiscretizerBuilder::from<6>(3, initialSet))
			.add<7, int>(EvenDecimalDiscretizerBuilder::from<7>(3, initialSet))
			.add<8, int>(EvenDecimalDiscretizerBuilder::from<8>(3, initialSet))
			.transform();

		auto builder = ILA::ILAClassifierBuilder::builder<int, 9>(-1);

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			builder,
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 10; i++)
			stats = crossValidator.validate(10);

		cout << "," << stats << builder.usedExamples() << endl;
	}
}