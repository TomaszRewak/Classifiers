#pragma once

#include "KNNClassifier.hpp"

namespace Classifier::KNN::Voting
{
	template<typename Class>
	class DistanceVoting
	{
	private:
		using Candidates = typename std::vector<KNNCandidate<Class>>;

	public:
		Class select(Candidates& candidates)
		{
			std::map<Class, double> distances;

			for (auto& candidate : candidates)
				distances[candidate.value] += 1 / candidate.distance;

			Class best;
			double bestDistance = -1;

			for (const auto& element : distances)
			{
				if (element.second > bestDistance)
				{
					best = element.first;
					bestDistance = element.second;
				}
			}

			return best;
		}
	};
}