#pragma once

#include <vector>
#include <limits>

namespace Classifier::Data::Transformation
{
	class KMeansDiscretizer
	{
	private:
		std::vector<double> centers;

	public:
		KMeansDiscretizer(std::vector<double> centers):
			centers(centers)
		{ }

		int operator()(double value)
		{
			double closestDistance = std::numeric_limits<double>::max();
			int closestClass = -1;

			for (int i = 0; i < centers.size(); i++)
			{
				if (std::pow(value - centers[i], 2) < closestDistance)
				{
					closestDistance = centers[i];
					closestClass = i;
				}
			}

			return closestClass;
		}
	};
}