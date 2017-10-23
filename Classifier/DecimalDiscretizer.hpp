#pragma once

#include <vector>
#include <limits>
#include <algorithm>

namespace Classifier::Data::Transformation
{
	class DecimalDiscretizer
	{
	private:
		int classes;
		double min, max;

	public:
		DecimalDiscretizer(double min, double max, int classes) :
			min(min),
			max(max),
			classes(classes)
		{ }

		int operator()(double value) {
			return std::min((int)(classes * (value - min) / (max - min)), classes - 1);
		}
	};

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