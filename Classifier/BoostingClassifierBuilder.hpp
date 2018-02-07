#pragma once

#include "MultiClassifiers.hpp"

namespace Classifier::ClassificationSet::Builders::Boosting
{
	class BoosingClassifierBuilder {
	public:
		template<typename Boosting, typename BaseClassifier, typename BaseBuilder, typename Voting, typename Class, typename Features>
		struct Builder {
		private:
			BaseBuilder baseBuilder;
			int number;

		public:
			Builder(BaseBuilder baseBuilder, int number) :
				baseBuilder(baseBuilder),
				number(number)
			{ }

			MultiClassifier<BaseClassifier, Voting, Class, Features> operator()(std::vector<Class>& classes, std::vector<Features>& features)
			{
				Boosting boosting(classes.size());
				Voting voting;

				std::vector<BaseClassifier> classifiers;

				for (int i = 0; i < number; i++)
				{
					std::random_device randomDevice;
					std::mt19937 randomGenerator(randomDevice());
					std::discrete_distribution<> boostingDistribution(boosting.begin(), boosting.end());

					std::vector<Class> subClasses;
					std::vector<Features> subFeatures;

					for (int i = 0; i < classes.size(); i++)
					{
						int example = boostingDistribution(randomGenerator);

						subClasses.push_back(classes[example]);
						subFeatures.push_back(features[example]);
					}

					auto classifier = baseBuilder(subClasses, subFeatures);
					classifiers.push_back(baseBuilder(subClasses, subFeatures));

					std::vector<Class> predicted;
					for (auto& feature : features)
						predicted.push_back(
							classifier.classify(feature)
						);

					boosting.add(predicted, classes);
					voting.nextClassifier(predicted, classes);
				}

				return MultiClassifier<
					BaseClassifier,
					Voting,
					Class,
					Features
				>(classifiers, voting);
			}
		};

	public:
		template<typename Boosting, typename Voting, typename BaseBuilder>
		static auto builder(BaseBuilder baseBuilder, int number)
		{
			return Builder<
				Boosting,
				typename BaseBuilder::classifier_type,
				BaseBuilder,
				Voting,
				typename BaseBuilder::class_type,
				typename BaseBuilder::features_type
			>(baseBuilder, number);
		}
	};
}