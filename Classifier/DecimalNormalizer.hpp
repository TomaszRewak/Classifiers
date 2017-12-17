#pragma once

#include <vector>
#include <limits>
#include <algorithm>

namespace Classifier::Data::Transformation
{
	class DecimalNormalizer
	{
	private:
		double min, max;

	public:
		DecimalNormalizer(double min, double max) :
			min(min),
			max(max)
		{ }

		double operator()(double value) {
			return (value - min) / (max - min);
		}
	};
}