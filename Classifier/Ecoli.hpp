#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"
#include "ClassSet.hpp"
#include "Transformer.hpp"
#include "DecimalDiscretizer.hpp"
#include "EvenDecimalDiscretizer.hpp"
#include "DiscreteDiscretizer.hpp"
#include "BayesClassifier.hpp"
#include "CrossValidator.hpp"

using namespace std;
using namespace Classifier::Data;
using namespace Classifier::Data::Transformation;


namespace Classifier::Test::Ecoli {
	void ecoli_test()
	{
		cout << "ECOLI" << endl;

		using InitialSetType = FeatureSet<double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<string>;

		InitialSetType initialSet;
		ClassSetType classSet;

		Parser::CsvParser input;
		input.open("../Data/ecoli.data");
		for (int i = 0; i < 336; i++)
		{
			string name;
			double mcg;
			double gvh;
			double lip;
			double chg;
			double aac;
			double alm1;
			double alm2;
			string type;

			name = input.get<string>();
			mcg = input.get<double>();
			gvh = input.get<double>();
			lip = input.get<double>();
			chg = input.get<double>();
			aac = input.get<double>();
			alm1 = input.get<double>();
			alm2 = input.get<double>();
			type = input.get<string>();

			initialSet.push_back(mcg, gvh, lip, chg, aac, alm1, alm2);
			classSet.push_back(type);
		}
		input.close();

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
			Bayes::BayesClassifierBuilder::builder<string, 7>(),
			classSet,
			featureSet
		);
		crossValidator.validate(10);
	}
}