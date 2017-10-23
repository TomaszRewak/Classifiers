#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace Classifier::Parser
{
	class CsvParser : public std::ifstream 
	{
	private:
		std::string emptyValue;

		std::string getNext()
		{
			std::string part;
			std::getline(*this, part, ',');

			return part;
		}

	public:
		CsvParser(std::string emptyValue = "") :
			emptyValue(emptyValue)
		{ }

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

		template<typename T>
		bool tryGet(T& value) = 0;

		template<>
		bool tryGet<int>(int& value)
		{
			std::string next = getNext();

			if (next == emptyValue)
				return false;

			value = stoi(next);

			return true;
		}

		template<>
		bool tryGet<double>(double& value)
		{
			std::string next = getNext();

			if (next == emptyValue)
				return false;

			value = stod(next);

			return true;
		}

		template<>
		bool tryGet<std::string>(std::string& value)
		{
			std::string next = getNext();

			if (next == emptyValue)
				return false;

			value = next;

			return true;
		}
	};
}