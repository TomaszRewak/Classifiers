#pragma once

#include "EvenDecimalDiscretizer.hpp"

namespace Classifier::Data::Transformation
{
	class EvenDecimalDiscretizerBuilder {
	public:
		template<typename Iterator>
		static EvenDecimalDiscretizer from(int classes, Iterator begin, Iterator end)
		{
			std::vector<double> values;

			for (auto iter = begin; iter < end; iter++)
				values.push_back(*iter);

			std::sort(values.begin(), values.end());

			std::vector<double> ranges;

			for (int i = 1; i < classes; i++)
				ranges.push_back(values[(double)i / classes * values.size()]);

			return EvenDecimalDiscretizer(ranges);
		}

		template<size_t N, typename FeatureSet>
		static EvenDecimalDiscretizer from(int classes, FeatureSet set)
		{
			return from(classes, set.beginF<N>(), set.endF<N>());
		}
	};
}