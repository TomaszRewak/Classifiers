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
#include "ILAClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"
#include "IrisReader.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::ILATest {
	void iris_ila_test()
	{
		cout << "ILA IRIS" << endl;

		auto[initialSet, classSet] = IrisReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(5, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(5, initialSet))
			.transform();

		auto builder = ILA::ILAClassifierBuilder::builder<string, 4>("other");

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			builder,
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats = crossValidator.validate(10);

		cout << stats << builder.usedExamples() << endl;
	}
}