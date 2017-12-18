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
	class LibrasReader {
	public:
		using InitialSetType = FeatureSet<
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double,
			double, double, double, double, double, double, double, double, double, double
		>;
		using ClassSetType = ClassSet<int>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
			InitialSetType initialSet;
			ClassSetType classSet;

			Parser::CsvParser input;
			input.open("../Data/libras.data");
			for (int i = 0; i < 360; i++)
			{
				initialSet.push_back(
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(),
					input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>(), input.get<double>()
				);

				int Type = input.get<int>();
				classSet.push_back(Type);
			}
			input.close();

			return std::make_tuple(initialSet, classSet);
		}
	};
}