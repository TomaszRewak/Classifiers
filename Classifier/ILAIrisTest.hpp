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
			.add<0, int>(EvenDecimalDiscretizerBuilder::from<0>(3, initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(3, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(3, initialSet))
			.add<3, int>(EvenDecimalDiscretizerBuilder::from<3>(3, initialSet))
			.transform();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			ILA::ILAClassifierBuilder::builder<string, 4>("other"),
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats = crossValidator.validate(10);
		cout << stats;
	}
}