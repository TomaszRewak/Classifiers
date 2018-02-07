#pragma once

#include "MultiClassifiers.hpp"

namespace Classifier::ClassificationSet::Builders::Bagging
{
	class BaggingClassifierBuilder {
	public:
		template<typename BaseClassifier, typename BaseBuilder, typename Voting, typename Class, typename Features>
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
				Voting voting;

				std::vector<BaseClassifier> classifiers;

				for (int i = 0; i < number; i++)
				{
					std::vector<Class> subClasses;
					std::vector<Features> subFeatures;

					for (int i = 0; i < classes.size(); i++)
					{
						int example = std::rand() % classes.size();

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
		template<typename Voting, typename BaseBuilder>
		static auto builder(BaseBuilder baseBuilder, int number)
		{
			return Builder<
				typename BaseBuilder::classifier_type,
				BaseBuilder,
				Voting,
				typename BaseBuilder::class_type,
				typename BaseBuilder::features_type
			>(baseBuilder, number);
		}
	};
}