#pragma once

#include "GaussianBayesClassifier.hpp"

namespace Classifier::Bayes
{
	class GaussianBayesClassifierBuilder {
	public:
		template <typename Class>
		using Classes = typename std::vector<Class>;

		template <typename ...Ts>
		using Features = typename std::vector<Data::Features<Ts...>>;

		template<typename Class, typename ...Ts>
		struct Builder {
			GaussianBayesClassifier<Class, sizeof...(Ts)> operator()(Classes<Class>& classes, Features<Ts...>& features)
			{
				ClassGaussianCardinality<Class> classCardinality;
				ClassGaussianFeatures<Class, sizeof...(Ts)> gaussianFeatures;

				for (auto iter = classes.begin(); iter < classes.end(); iter++)
				{
					classCardinality[*iter]++;
				}

				{
					auto classIter = classes.begin();
					auto dataIter = features.begin();
					for (; classIter < classes.end(); classIter++, dataIter++)
					{
						for (int i = 0; i < sizeof...(Ts); i++)
						{
							gaussianFeatures[*classIter][i].mean += (*dataIter).get<double>(i) / classCardinality[*classIter];
						}
					}
				}

				{
					auto classIter = classes.begin();
					auto dataIter = features.begin();
					for (; classIter < classes.end(); classIter++, dataIter++)
					{
						for (int i = 0; i < sizeof...(Ts); i++)
						{
							gaussianFeatures[*classIter][i].standardDeviation +=
								std::pow((*dataIter).get<double>(i) - gaussianFeatures[*classIter][i].mean, 2);
						}
					}
				}

				for (auto& c : gaussianFeatures)
				{
					for (int i = 0; i < sizeof...(Ts); i++)
					{
						c.second[i].standardDeviation =
							std::sqrt(c.second[i].standardDeviation / classCardinality[c.first]);
					}
				}

				return GaussianBayesClassifier<Class, sizeof...(Ts)>(classCardinality, gaussianFeatures);
			}
		};

	private:
		template<typename, typename>
		struct BuilderType;

		template<typename Class, size_t ...N>
		struct BuilderType<Class, std::index_sequence<N...>>
		{
			using type = Builder<Class, typename std::conditional<N == N, double, double>::type...>;
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
		static GaussianBayesClassifier<Class, sizeof...(Ts)> from(
			std::vector<Class>& classes,
			Data::FeatureSet<Ts...>& features)
		{
			return get_builder<Class, Ts...>()(classes, features);
		}
	};
}