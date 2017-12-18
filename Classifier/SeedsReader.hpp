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
	class SeedsReader {
	public:
		using InitialSetType = FeatureSet<double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<int>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
			InitialSetType initialSet;
			ClassSetType classSet;

			Parser::CsvParser input;
			input.open("../Data/seeds.data");
			for (int i = 0; i < 210; i++)
			{
				double area = input.get<double>();
				double perimeter = input.get<double>();
				double compactness = input.get<double>();
				double length_of_kernel = input.get<double>();
				double width_of_kernel = input.get<double>();
				double asymmetry_coefficient = input.get<double>();
				double length_of_kernel_groove = input.get<double>();

				int Type = input.get<int>();

				initialSet.push_back(area, perimeter, compactness, length_of_kernel, width_of_kernel, asymmetry_coefficient, length_of_kernel_groove);
				classSet.push_back(Type);
			}
			input.close();

			return std::make_tuple(initialSet, classSet);
		}
	};
}