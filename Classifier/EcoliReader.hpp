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
	class EcoliReader {
	public:
		using InitialSetType = FeatureSet<double, double, double, double, double, double, double>;
		using ClassSetType = ClassSet<string>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
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

			return std::make_tuple(initialSet, classSet);
		}
	};
}