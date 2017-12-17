#pragma once 

#include "FeatureSet.hpp"

namespace Classifier::KNN::Distance
{
	template<size_t k>
	class EuclideanDistance 
	{
	private:
		template<typename>
		struct FeaturesType;

		template<size_t ...N>
		struct FeaturesType<std::index_sequence<N...>>
		{
			using type = Data::Features<typename std::conditional<N == N, double, double>::type...>;
		};
		using Features = typename FeaturesType<std::make_index_sequence<k>>::type;

	public:
		double between(Features& a, Features& b)
		{
			double sum = 0;

			for (size_t i = 0; i < k; i++)
				sum += std::pow(a.get<double>(i) - b.get<double>(i), 2);

			return std::sqrt(sum);
		}
	};
}