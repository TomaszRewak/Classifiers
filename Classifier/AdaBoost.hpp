#pragma once

#include <vector>
#include <algorithm>

namespace Classifier::ClassificationSet::Builders::Boosting::BoostingAlgorithm
{
	template<typename Class>
	class AdaBoost : public std::vector<double>
	{
	public:
		AdaBoost(int size) :
			std::vector<double>(size)
		{
			for (auto& weight : *this)
				weight = 1. / size;
		}

		void add(std::vector<Class>& decisions, std::vector<Class>& expected)
		{
			double error = 0;
			double errorWeight = 0;

			for (int i = 0; i < this->size(); i++)
			{
				double weight = (*this)[i];

				errorWeight += weight;

				if (decisions[i] != expected[i])
					error += weight;
			}
			error /= errorWeight;

			double stage = std::log((1 - error) / error);

			for (int i = 0; i < this->size(); i++)
			{
				if (decisions[i] != expected[i])
				{
					double& weight = (*this)[i];

					weight *= std::exp(stage);
				}
			}
		}
	};
}