#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace Classifier::Parser
{
	class CsvParser : public std::ifstream 
	{
	private:
		std::string getNext()
		{
			std::string part;
			std::getline(*this, part, ',');

			return part;
		}

	public:
		template<typename T>
		T get() = 0;

		template<>
		int get<int>()
		{
			return stoi(getNext());
		}

		template<>
		double get<double>()
		{
			return stod(getNext());
		}

		template<>
		std::string get<std::string>()
		{
			return getNext();
		}
	};
}