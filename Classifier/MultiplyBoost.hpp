#pragma once

#include <vector>
#include <algorithm>

namespace Classifier::ClassificationSet::Builders::Boosting::BoostingAlgorithm
{
	template<typename Class>
	class MultiplyBoost : public std::vector<double>
	{
	public:
		MultiplyBoost(int size) :
			std::vector<double>(size)
		{
			for (auto& weight : *this)
				weight = 1.;
		}

		void add(std::vector<Class>& decisions, std::vector<Class>& expected)
		{
			for (int i = 0; i < this->size(); i++)
			{
				if (decisions[i] != expected[i])
				{
					double& weight = (*this)[i];

					weight *= 4;
				}
			}
		}
	};
}