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
}