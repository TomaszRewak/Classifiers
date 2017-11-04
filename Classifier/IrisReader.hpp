#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"
#include "ClassSet.hpp"

using namespace std;
using namespace Classifier::Data;

namespace Classifier::Test::Readers 
{
	class IrisReader {
	public:
		using InitialSetType = FeatureSet<double, double, double, double>;
		using ClassSetType = ClassSet<string>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
			InitialSetType initialSet;
			ClassSetType classSet;

			Parser::CsvParser input;
			input.open("../Data/iris.data");
			for (int i = 0; i < 150; i++)
			{
				double sepal_length = input.get<double>();
				double sepal_width = input.get<double>();
				double petal_length = input.get<double>();
				double petal_width = input.get<double>();
				string Type = input.get<string>();

				initialSet.push_back(sepal_length, sepal_width, petal_length, petal_width);
				classSet.push_back(Type);
			}
			input.close();

			return std::make_tuple(initialSet, classSet);
		}
	};
}