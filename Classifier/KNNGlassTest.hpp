#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"
#include "ClassSet.hpp"
#include "TransformerBuilder.hpp"
#include "DecimalNormalizerBuilder.hpp"
#include "KNNClassifierBuilder.hpp"
#include "CrossValidatorBuilder.hpp"
#include "GlassReader.hpp"
#include "EuclideanDistance.hpp"
#include "FrequencyVoting.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::KNNTest {
	void glass_knn_test()
	{
		cout << "KNN Glass" << endl;

		auto[initialSet, classSet] = GlassReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, double>(DecimalNormalizerBuilder::from<0>(initialSet))
			.add<1, double>(DecimalNormalizerBuilder::from<1>(initialSet))
			.add<2, double>(DecimalNormalizerBuilder::from<2>(initialSet))
			.add<3, double>(DecimalNormalizerBuilder::from<3>(initialSet))
			.add<4, double>(DecimalNormalizerBuilder::from<4>(initialSet))
			.add<5, double>(DecimalNormalizerBuilder::from<5>(initialSet))
			.add<6, double>(DecimalNormalizerBuilder::from<6>(initialSet))
			.add<7, double>(DecimalNormalizerBuilder::from<7>(initialSet))
			.add<8, double>(DecimalNormalizerBuilder::from<8>(initialSet))
			.transform();

		auto builder = KNN::KNNClassifierBuilder::builder<
			KNN::Distance::EuclideanDistance<9>,
			KNN::Voting::FrequencyVoting<int>,
			int, 9
		>(5);

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			builder,
			classSet,
			featureSet
		);

		Validation::ValidationStatistics stats;
		for (int i = 0; i < 10; i++)
		{
			stats += crossValidator.validate(10);
		}
		cout << stats << endl;
	}
}