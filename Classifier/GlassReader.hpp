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
	class GlassReader {
	public:
		using InitialSetType = FeatureSet<double, double, double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<int>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
			InitialSetType initialSet;
			ClassSetType classSet;

			Parser::CsvParser input;
			input.open("../Data/glass.data");
			for (int i = 0; i < 214; i++)
			{
				int Id = input.get<int>();
				double RI = input.get<double>();
				double Na = input.get<double>();
				double Mg = input.get<double>();
				double Al = input.get<double>();
				double Si = input.get<double>();
				double K = input.get<double>();
				double Ca = input.get<double>();
				double Ba = input.get<double>();
				double Fe = input.get<double>();
				int Type = input.get<int>();

				//if (Type == 1 || Type == 3)
				//	Type = 100;
				//else if (Type == 2 || Type == 4)
				//	Type = 101;
				//else 
				//	Type = 102;

				//if (Type == 1 || Type == 2)
				//	Type = 100;
				//else if (Type == 3 || Type == 4)
				//	Type = 101;
				//else 
				//	Type = 102;

				initialSet.push_back(RI, Na, Mg, Al, Si, K, Ca, Ba, Fe);
				classSet.push_back(Type);
			}
			input.close();

			return std::make_tuple(initialSet, classSet);
		}
	};
}