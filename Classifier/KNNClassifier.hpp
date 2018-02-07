#pragma once

#include <vector>
#include <array>
#include <map>

#include "FeatureSet.hpp"

namespace Classifier::KNN
{
	template<typename Class>
	struct KNNCandidate
	{
		Class value;
		double distance;

		KNNCandidate()
		{ }

		KNNCandidate(Class value, double distance) :
			value(value),
			distance(distance)
		{ }
	};

	template<typename Distance, typename Voting, typename Class, typename ...Ts>
	class KNNClassifier
	{
	private:
		using Classes = typename std::vector<Class>;
		using Features = typename std::vector<Data::Features<Ts...>>;
		using Candidate = typename KNNCandidate<Class>;
		using Candidates = typename std::vector<Candidate>;

		size_t k;

		Classes classes;
		Features features;
		Candidates candidates;

		Distance distance;
		Voting voting;

	public:
		KNNClassifier(size_t k, Classes classes, Features features) :
			k(k), classes(classes), features(features)
		{ }

		template<typename ...Ts>
		Class classify(Data::Features<Ts...>& specimen)
		{
			candidates.clear();

			for (size_t example = 0; example < features.size(); example++)
			{
				Candidate candidate(
					classes[example],
					distance.between(specimen, features[example])
				);

				candidates.push_back(candidate);
			}

			std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b)
			{
				return a.distance < b.distance;
			});

			candidates.resize(k);

			return voting.select(candidates);
		}
	};
}