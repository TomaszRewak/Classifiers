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

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;
using namespace Classifier::Test::Readers;

namespace Classifier::Test::ILATest {
	void example_ila_test()
	{
		cout << "ILA EXAMPLE" << endl;

		using InitialSetType = FeatureSet<int, int, int>;
		using ClassSetType = ClassSet<bool>;

		InitialSetType featureSet;
		ClassSetType classSet;

		featureSet.push_back(1, 2, 0); classSet.push_back(true);
		featureSet.push_back(0, 0, 1); classSet.push_back(false);
		featureSet.push_back(0, 0, 2); classSet.push_back(true);
		featureSet.push_back(2, 0, 1); classSet.push_back(false);
		featureSet.push_back(2, 1, 3); classSet.push_back(true);
		featureSet.push_back(2, 0, 3); classSet.push_back(false);
		featureSet.push_back(2, 1, 2); classSet.push_back(true);

		auto ila = ILA::ILAClassifierBuilder::from(classSet, featureSet, true);
	}
}