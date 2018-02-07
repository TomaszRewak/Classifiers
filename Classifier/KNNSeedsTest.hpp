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
#include "SeedsReader.hpp"
#include "EuclideanDistance.hpp"
#include "FrequencyVoting.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::KNNTest {
	void seeds_knn_test()
	{
		cout << "KNN Seeds" << endl;

		auto[initialSet, classSet] = SeedsReader::read();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, double>(DecimalNormalizerBuilder::from<0>(initialSet))
			.add<1, double>(DecimalNormalizerBuilder::from<1>(initialSet))
			.add<2, double>(DecimalNormalizerBuilder::from<2>(initialSet))
			.add<3, double>(DecimalNormalizerBuilder::from<3>(initialSet))
			.add<4, double>(DecimalNormalizerBuilder::from<4>(initialSet))
			.add<5, double>(DecimalNormalizerBuilder::from<5>(initialSet))
			.add<6, double>(DecimalNormalizerBuilder::from<6>(initialSet))
			.transform();

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::EuclideanDistance<7>,
				KNN::Voting::FrequencyVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::EuclideanDistance<7>,
				KNN::Voting::DistanceVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::EuclideanDistance<7>,
				KNN::Voting::WeightedVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::ManhattanDistance<7>,
				KNN::Voting::FrequencyVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::ManhattanDistance<7>,
				KNN::Voting::DistanceVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}

		cout << "---" << endl;
		for (int j = 1; j < 210; j++)
		{
			auto builder = KNN::KNNClassifierBuilder::builder<
				KNN::Distance::ManhattanDistance<7>,
				KNN::Voting::WeightedVoting<int>,
				int, 7
			>(j);

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
			cout << j << ",\t" << stats << endl;
		}
	}
}