#pragma once

#include <vector>
#include <array>
#include <map>

#include "FeatureSet.hpp"

namespace Classifier::Bayes
{
	template<typename Class, size_t Features>
	using ClassCardinality = std::map<Class, int>;

	template<typename Class, size_t Features>
	using FeaturesCardinality = std::map<Class, std::array<std::map<int, int>, Features>>;

	template<typename Class, size_t Features>
	class BayesClassifier
	{
	private:
		ClassCardinality<Class, Features> classCardinality;
		FeaturesCardinality<Class, Features> featuresCardinality;

	public:
		BayesClassifier(ClassCardinality<Class, Features> classCardinality, FeaturesCardinality<Class, Features> featuresCardinality) :
			classCardinality(classCardinality), featuresCardinality(featuresCardinality)
		{ }

		template<typename ...Ts>
		Class classify(Data::Features<Ts...>& specimen)
		{
			Class bestClass;
			double bestClassProbability = -1;

			for (auto& c : classCardinality)
			{
				Class currentClass = c.first;

				double currentClassCardinality = c.second;
				double currentFeaturesProbability = 1;

				for (int i = 0; i < Features; i++)
				{
					currentFeaturesProbability *= featuresCardinality[currentClass][i][specimen.get<int>(i)];
					currentFeaturesProbability /= currentClassCardinality;
				}

				double probability = currentClassCardinality * currentFeaturesProbability;

				if (probability > bestClassProbability)
				{
					bestClass = currentClass;
					bestClassProbability = probability;
				}
			}

			return bestClass;
		}
	};
}