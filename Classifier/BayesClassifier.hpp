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
		Class classify(Data::Features<Ts...> specimen)
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

	class BayesClassifierBuilder {
	public:
		template <typename Class>
		using Classes = typename std::vector<Class>;

		template <typename ...Ts>
		using Features = typename std::vector<Data::Features<Ts...>>;

		template<typename Class, typename ...Ts>
		struct Builder {
			BayesClassifier<Class, sizeof...(Ts)> operator()(Classes<Class>& classes, Features<Ts...>& features)
			{
				ClassCardinality<Class, sizeof...(Ts)> classCardinality;
				FeaturesCardinality<Class, sizeof...(Ts)> featuresCardinality;

				for (auto iter = classes.begin(); iter < classes.end(); iter++)
				{
					classCardinality[*iter]++;
				}

				auto classIter = classes.begin();
				auto dataIter = features.begin();
				for (; classIter < classes.end(); classIter++, dataIter++)
				{
					for (int i = 0; i < sizeof...(Ts); i++)
					{
						featuresCardinality[*classIter][i][(*dataIter).get<int>(i)]++;
					}
				}

				return BayesClassifier<Class, sizeof...(Ts)>(classCardinality, featuresCardinality);
			}
		};

	private:
		template<typename, typename>
		struct BuilderType;

		template<typename Class, size_t ...N>
		struct BuilderType<Class, std::index_sequence<N...>>
		{
			using type = Builder<Class, typename std::conditional<N == N, int, int>::type...>;
		};

		template<typename Class, size_t N>
		using BuilderType_t = typename BuilderType<Class, std::make_index_sequence<N>>::type;

		template<typename Class, typename ...Ts>
		static Builder<Class, Ts...> get_builder()
		{
			return Builder<Class, Ts...>();
		}

	public:
		template<typename Class, size_t N>
		static auto builder()
		{
			return BuilderType_t<Class, N>();
		}

		template<typename Class, typename ...Ts>
		static BayesClassifier<Class, sizeof...(Ts)> from(
			std::vector<Class>& classes,
			Data::FeatureSet<Ts...>& features)
		{
			return get_builder<Class, Ts...>()(classes, features);
		}
	};
}