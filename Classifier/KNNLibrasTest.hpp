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
#include "LibrasReader.hpp"
#include "EuclideanDistance.hpp"
#include "FrequencyVoting.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::KNNTest {
	void libras_knn_test()
	{
		cout << "KNN Libras" << endl;

		auto[initialSet, classSet] = LibrasReader::read();

		auto featureSet = initialSet;

		auto builder = KNN::KNNClassifierBuilder::builder<
			KNN::Distance::EuclideanDistance<90>,
			KNN::Voting::FrequencyVoting<int>,
			int, 90
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