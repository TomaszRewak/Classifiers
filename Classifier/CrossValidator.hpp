#pragma once

#include <algorithm>
#include <random>
#include <chrono>
#include <set>

#include "FeatureSet.hpp"
#include "ClassSet.hpp"
#include "ConfusionMatrix.hpp"

namespace Classifier::Validation
{
	template<typename Builder, typename Class, typename ...Ts>
	class CrossValidator
	{
	private:
		Builder builder;

		std::set<Class> uniqueClasses;

		Data::ClassSet<Class> classes;
		Data::FeatureSet<Ts...> features;

	public:
		CrossValidator(
			Builder builder,
			Data::ClassSet<Class> classes,
			Data::FeatureSet<Ts...> features
		) :
			builder(builder),
			classes(classes),
			features(features)
		{
			for (Class& c : classes)
				uniqueClasses.insert(c);
		}

		ValidationStatistics validate(size_t chunks)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

			std::shuffle(this->classes.begin(), this->classes.end(), std::default_random_engine(seed));
			std::shuffle(this->features.begin(), this->features.end(), std::default_random_engine(seed));

			ValidationStatistics metrices;

			int totalCount = classes.size();
			int chunkSize = totalCount / chunks;

			for (int i = 0; i < chunks; i++)
			{
				Data::ClassSet<Class> trainClasses, testClasses;
				Data::FeatureSet<Ts...> trainFeatures, testFeatures;

				for (int j = 0; j < classes.size(); j++)
				{
					if (j / chunkSize == i)
					{
						testClasses.push_back(classes[j]);
						testFeatures.push_back(features[j]);
					}
					else
					{
						trainClasses.push_back(classes[j]);
						trainFeatures.push_back(features[j]);
					}
				}

				auto classifier = builder(trainClasses, trainFeatures);

				int positive = 0;
				std::vector<ConfusionMatrix<Class>> confusionMatrixes;
				for (const Class& c : uniqueClasses)
					confusionMatrixes.push_back(ConfusionMatrix<Class>(c));

				for (int j = 0; j < testClasses.size(); j++)
				{
					Class realClass = testClasses[j];
					Class predictedClass = classifier.classify(testFeatures[j]);

					if (realClass == predictedClass)
						positive++;

					for (ConfusionMatrix<Class>& cm : confusionMatrixes)
						cm.add(predictedClass, realClass);
				}

				//cout << positive << "/" << testClasses.size() << " (" << (100 * positive / testClasses.size()) << "%)" << endl;

				ValidationStatistics chunkMetrices;

				for (ConfusionMatrix<Class>& cm : confusionMatrixes) {
					auto classMetrices = cm.get();
					
					//std::cout << cm;
					//std::cout << classMetrices;

					chunkMetrices += classMetrices;
				}

				metrices += chunkMetrices;

				//std::cout << chunkMetrices;
				//cout << std::endl;
			}

			//std::cout << metrices;

			return metrices;
		}
	};
}