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
#include "IrisReader.hpp"
#include "EuclideanDistance.hpp"
#include "ManhattanDistance.hpp"
#include "FrequencyVoting.hpp"
#include "WeightedVoting.hpp"
#include "DistanceVoting.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::KNNTest {
	void iris_knn_test()
	{
		cout << "KNN Iris" << endl;

		auto[initialSet, classSet] = IrisReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, double>(DecimalNormalizerBuilder::from<0>(initialSet))
			.add<1, double>(DecimalNormalizerBuilder::from<1>(initialSet))
			.add<2, double>(DecimalNormalizerBuilder::from<2>(initialSet))
			.add<3, double>(DecimalNormalizerBuilder::from<3>(initialSet))
			.transform();

		auto builder = KNN::KNNClassifierBuilder::builder<
			KNN::Distance::EuclideanDistance<4>,
			KNN::Voting::FrequencyVoting<string>,
			string, 4
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