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


namespace Classifier::Test::Credit {
	void credit_test()
	{
		cout << "CREDIT" << endl;

		using InitialSetType = FeatureSet<string, double, double, string, string, string, string, double, string, string, double, string, string, double, double>;
		using ClassSetType = ClassSet<string>;

		InitialSetType initialSet;
		ClassSetType classSet;

		Parser::CsvParser input("?");
		input.open("../Data/credit.data");
		for (int i = 0; i < 690; i++)
		{
			string A1;
			double A2;
			double A3;
			string A4;
			string A5;
			string A6;
			string A7;
			double A8;
			string A9;
			string A10;
			double A11;
			string A12;
			string A13;
			double A14;
			double A15;
			string A16;

			bool emptyValues = false;

			emptyValues = !input.tryGet(A1) || emptyValues;
			emptyValues = !input.tryGet(A2) || emptyValues;
			emptyValues = !input.tryGet(A3) || emptyValues;
			emptyValues = !input.tryGet(A4) || emptyValues;
			emptyValues = !input.tryGet(A5) || emptyValues;
			emptyValues = !input.tryGet(A6) || emptyValues;
			emptyValues = !input.tryGet(A7) || emptyValues;
			emptyValues = !input.tryGet(A8) || emptyValues;
			emptyValues = !input.tryGet(A9) || emptyValues;
			emptyValues = !input.tryGet(A10) || emptyValues;
			emptyValues = !input.tryGet(A11) || emptyValues;
			emptyValues = !input.tryGet(A12) || emptyValues;
			emptyValues = !input.tryGet(A13) || emptyValues;
			emptyValues = !input.tryGet(A14) || emptyValues;
			emptyValues = !input.tryGet(A15) || emptyValues;
			emptyValues = !input.tryGet(A16) || emptyValues;

			if (emptyValues)
				continue;

			initialSet.push_back(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15);
			classSet.push_back(A16);
		}
		input.close();

		auto featureSet = TransformerBuilder::from(initialSet)
			.add<0, int>(DiscreteDiscretizerBuilder::from<0>(initialSet))
			.add<1, int>(EvenDecimalDiscretizerBuilder::from<1>(5, initialSet))
			.add<2, int>(EvenDecimalDiscretizerBuilder::from<2>(5, initialSet))
			.add<3, int>(DiscreteDiscretizerBuilder::from<3>(initialSet))
			.add<4, int>(DiscreteDiscretizerBuilder::from<4>(initialSet))
			.add<5, int>(DiscreteDiscretizerBuilder::from<5>(initialSet))
			.add<6, int>(DiscreteDiscretizerBuilder::from<6>(initialSet))
			.add<7, int>(EvenDecimalDiscretizerBuilder::from<7>(5, initialSet))
			.add<8, int>(DiscreteDiscretizerBuilder::from<8>(initialSet))
			.add<9, int>(DiscreteDiscretizerBuilder::from<9>(initialSet))
			.add<10, int>(EvenDecimalDiscretizerBuilder::from<10>(5, initialSet))
			.add<11, int>(DiscreteDiscretizerBuilder::from<11>(initialSet))
			.add<12, int>(DiscreteDiscretizerBuilder::from<12>(initialSet))
			.add<13, int>(EvenDecimalDiscretizerBuilder::from<13>(5, initialSet))
			.add<14, int>(EvenDecimalDiscretizerBuilder::from<14>(5, initialSet))
			.transform();

		//featureSet.print();

		auto crossValidator = Validation::CrossValidatorBuilder::from(
			Bayes::BayesClassifierBuilder::builder<string, 15>(),
			classSet,
			featureSet
		);
		crossValidator.validate(10);
	}
}