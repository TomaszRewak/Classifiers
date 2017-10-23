#pragma once

#include <vector>
#include <limits>
#include <algorithm>

namespace Classifier::Data::Transformation
{
	class EvenDecimalDiscretizer
	{
	private:
		std::vector<double> ranges;

	public:
		EvenDecimalDiscretizer(std::vector<double> ranges) :
			ranges(ranges)
		{ }

		int operator()(double value) {
			int classInRange = 0;

			for (; classInRange < ranges.size() && value > ranges[classInRange]; classInRange++);

			return classInRange;
		}
	};

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