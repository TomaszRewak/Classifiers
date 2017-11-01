#pragma once

#include <vector>
#include <array>
#include <map>

#include "FeatureSet.hpp"

namespace Classifier::Bayes
{
	struct GaussianFeatures
	{
		double standardDeviation = 0;
		double mean = 0;
	};

	template<typename Class>
	using ClassGaussianCardinality = std::map<Class, int>;

	template<typename Class, size_t Features>
	using ClassGaussianFeatures = std::map<Class, std::array<GaussianFeatures, Features>>;

	template<typename Class, size_t Features>
	class GaussianBayesClassifier
	{
	private:
		ClassGaussianCardinality<Class> classCardinality;
		ClassGaussianFeatures<Class, Features> gaussianFeatures;

	public:
		GaussianBayesClassifier(ClassGaussianCardinality<Class> classCardinality, ClassGaussianFeatures<Class, Features> gaussianFeatures) :
			classCardinality(classCardinality),
			gaussianFeatures(gaussianFeatures)
		{ }

		template<typename ...Ts>
		Class classify(Data::Features<Ts...> specimen)
		{
			Class bestClass;
			double bestClassProbability = -1;

			for (auto& c : classCardinality)
			{
				Class currentClass = c.first;

				double currentClassCardinality = c.second;
				auto& currentFeatures = gaussianFeatures[currentClass];

				double currentFeaturesProbability = 1;

				for (int i = 0; i < Features; i++)
				{
					currentFeaturesProbability *=
						std::exp(
							-std::pow(
								specimen.get<double>(i) - currentFeatures[i].mean,
								2)
							/
							(
								2 *
								std::pow(
									currentFeatures[i].standardDeviation,
									2
								)))
						/
						std::sqrt(2 * 3.1415 * std::pow(currentFeatures[i].standardDeviation, 2));
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