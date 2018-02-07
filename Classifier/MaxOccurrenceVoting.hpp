#pragma once

#include <vector>
#include <map>
#include <algorithm>

namespace Classifier::ClassificationSet::Voting
{
	template<typename Class>
	class MaxOccurrenceVoting
	{
	public:
		Class select(std::vector<Class>& decisions)
		{
			std::map<Class, int> cardinalities;

			for (auto& decision : decisions)
				cardinalities[decision]++;

			int max = -1;
			for (auto&&[k, v] : cardinalities)
				max = std::max(max, v);

			for (auto&&[k, v] : cardinalities)
				if (v == max)
					return k;
		}

		void nextClassifier(const std::vector<Class>& predicted, const std::vector<Class>& expected)
		{ }
	};
}