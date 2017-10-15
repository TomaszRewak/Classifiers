#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "CsvParser.hpp"
#include "FeatureSet.hpp"

using namespace std;

namespace Classifier::Test::Glass {
	void glass_test()
	{
		Data::FeatureSet<int, double, double, double, double, double, double, double, double, double, int> initialSet;

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

			initialSet.add(Id, RI, Na, Mg, Al, Si, K, Ca, Ba, Fe, Type);
		}
		input.close();

		auto fullDataSet =
			initialSet
			.remove<0>();

		fullDataSet.print();
	}
}