#pragma once

#include "KNNClassifier.hpp"

namespace Classifier::KNN::Voting
{
	template<typename Class>
	class WeightedVoting
	{
	private:
		using Candidates = typename std::vector<KNNCandidate<Class>>;

	public:
		Class select(Candidates& candidates)
		{
			std::map<Class, int> weights;

			double weight = 1;
			for (auto& candidate : candidates) {
				weights[candidate.value] += weight;
				weight -= 1 / candidates.size();
			}

			Class best;
			double bestWeight = -1;

			for (const auto& element : weights)
			{
				if (element.second > bestWeight)
				{
					best = element.first;
					bestWeight = element.second;
				}
			}

			return best;
		}
	};
}