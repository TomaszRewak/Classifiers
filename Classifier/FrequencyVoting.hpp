#pragma once

#include "KNNClassifier.hpp"

namespace Classifier::KNN::Voting 
{
	template<typename Class>
	class FrequencyVoting
	{
	private:
		using Candidates = typename std::vector<KNNCandidate<Class>>;

	public:
		Class select(Candidates& candidates)
		{
			std::map<Class, int> cardinalities;

			for (auto& candidate : candidates)
				cardinalities[candidate.value]++;

			Class best;
			int bestCount = -1;

			for (const auto& element : cardinalities)
			{
				if (element.second > bestCount)
				{
					best = element.first;
					bestCount = element.second;
				}
			}

			return best;
		}
	};
}