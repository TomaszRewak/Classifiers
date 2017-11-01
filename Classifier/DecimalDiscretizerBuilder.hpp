#pragma once

#include "DecimalDiscretizer.hpp"

namespace Classifier::Data::Transformation
{
	class DecimalDiscretizerBuilder {
	public:
		template<typename Iterator>
		static DecimalDiscretizer from(int classes, Iterator begin, Iterator end)
		{
			double min = std::numeric_limits<double>::max();
			double max = std::numeric_limits<double>::min();

			for (auto iter = begin; iter < end; iter++) {
				min = std::min(min, *iter);
				max = std::max(max, *iter);
			}

			return DecimalDiscretizer(min, max, classes);
		}

		template<size_t N, typename FeatureSet>
		static DecimalDiscretizer from(int classes, FeatureSet set)
		{
			return from(classes, set.beginF<N>(), set.endF<N>());
		}
	};
}