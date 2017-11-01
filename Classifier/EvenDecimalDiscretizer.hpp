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
}