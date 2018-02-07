#pragma once

#include <vector>

namespace Classifier::ClassificationSet
{
	template<typename Classifier, typename Voting, typename Class, typename Features>
	class MultiClassifier
	{
	private:
		using Classifiers = std::vector<Classifier>;
		using Classes = std::vector<Class>;

		Classifiers classifiers;
		Voting voting;

	public:
		MultiClassifier(Classifiers classifiers, Voting voting) :
			classifiers(classifiers),
			voting(voting)
		{ }

		Class classify(Features& specimen)
		{
			Classes decisions;

			for (auto& classifier : classifiers)
				decisions.push_back(
					classifier.classify(specimen)
				);

			return voting.select(decisions);
		}
	};
}