#pragma once

#include "DiscreteDiscretizer.hpp"

namespace Classifier::Data::Transformation
{
	class DiscreteDiscretizerBuilder {
	public:
		template<typename T, typename Iterator>
		static DiscreteDiscretizer<T> from(Iterator begin, Iterator end)
		{
			std::map<T, int> mapper;

			for (auto iter = begin; iter < end; iter++)
			{
				if (!mapper.count(*iter))
				{
					int c = mapper.size();
					mapper[*iter] = c;
				}
			}

			return DiscreteDiscretizer<T>(mapper);
		}

		template<size_t N, typename FeatureSet>
		static auto from(FeatureSet set)
		{
			return from<typename FeatureSet::type<N>>(set.beginF<N>(), set.endF<N>());
		}
	};
}