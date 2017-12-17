#pragma once

#include "DecimalNormalizer.hpp"

namespace Classifier::Data::Transformation
{
	class DecimalNormalizerBuilder {
	public:
		template<typename Iterator>
		static DecimalNormalizer from(Iterator begin, Iterator end)
		{
			double min = std::numeric_limits<double>::max();
			double max = std::numeric_limits<double>::min();

			for (auto iter = begin; iter < end; iter++) {
				min = std::min(min, *iter);
				max = std::max(max, *iter);
			}

			return DecimalNormalizer(min, max);
		}

		template<size_t N, typename FeatureSet>
		static DecimalNormalizer from(FeatureSet set)
		{
			return from(set.beginF<N>(), set.endF<N>());
		}
	};
}