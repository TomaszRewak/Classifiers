#pragma once

#include <vector>
#include <map>
#include <algorithm>

namespace Classifier::ClassificationSet::Voting
{
	template<typename Class>
	class ErrorVoting
	{
	private:
		std::vector<double> errors;

	public:
		Class select(std::vector<Class>& decisions)
		{
			double minError = *std::min_element(errors.begin(), errors.end());
			double maxError = *std::max_element(errors.begin(), errors.end());

			std::map<Class, double> cardinalities;

			for (int i = 0; i < decisions.size(); i++)
				cardinalities[decisions[i]] += 1 - (errors[i] - minError) / (maxError - minError);

			double max = -1;
			for (auto&&[k, v] : cardinalities)
				max = std::max(max, v);

			for (auto&&[k, v] : cardinalities)
				if (v == max)
					return k;
		}

		void nextClassifier(const std::vector<Class>& predicted, const std::vector<Class>& expected)
		{ 
			double classifierError = 0;

			for (int i = 0; i < predicted.size(); i++)
				if (predicted[i] != expected[i])
					classifierError += 1;

			classifierError /= predicted.size();

			errors.push_back(classifierError);
		}
	};
}