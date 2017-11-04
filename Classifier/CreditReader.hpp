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
	class CreditReader {
	public:
		using InitialSetType = FeatureSet<string, double, double, string, string, string, string, double, string, string, double, string, string, double, double>;
		using ClassSetType = ClassSet<string>;

		static std::tuple<InitialSetType, ClassSetType> read()
		{
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

			return std::make_tuple(initialSet, classSet);
		}
	};
}