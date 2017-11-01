#pragma once

#include "KMeansDiscretizer.hpp"

namespace Classifier::Data::Transformation
{
	class KMeansDiscretizerBuilder
	{
	public:
		template<typename Iterator>
		static KMeansDiscretizer from(int classes, Iterator begin, Iterator end)
		{
			std::vector<double> centers;

			std::vector<int> clusters;
			std::vector<double> values;

			double min = std::numeric_limits<double>::max();
			double max = std::numeric_limits<double>::min();

			for (auto iter = begin; iter < end; iter++) {
				min = std::min(min, *iter);
				max = std::max(max, *iter);

				values.push_back(*iter);
				clusters.push_back(0);
			}

			{
				std::vector<double> values;

				for (auto iter = begin; iter < end; iter++)
					values.push_back(*iter);

				std::sort(values.begin(), values.end());

				std::vector<double> ranges;

				for (int i = 1; i < classes; i++)
					centers.push_back(values[(double)i / classes * values.size()]);
			}

			for (bool changed = true; changed; )
			{
				for (int i = 0; i < values.size(); i++) {
					double bestDistence = std::numeric_limits<double>::max();

					for (int c = 0; c < centers.size(); c++)
					{
						double classDistance = std::pow(values[i] - centers[c], 2);

						if (classDistance < bestDistence)
						{
							bestDistence = classDistance;
							clusters[i] = c;
						}
					}
				}

				changed = false;

				for (int c = 0; c < centers.size(); c++)
				{
					int inCluster = 0;
					double summedPosition = 0;

					for (int i = 0; i < values.size(); i++)
					{
						if (clusters[i] == c)
						{
							summedPosition += values[i];
							inCluster++;
						}
					}

					double newCenter = inCluster != 0 ? summedPosition / inCluster : min;

					if (centers[c] != newCenter)
					{
						centers[c] = newCenter;
						changed = true;
					}
				}

				std::cout << ".";
			}

			std::cout << "----" << std::endl;
			for (auto& c : centers)
				std::cout << c << ", ";
			std::cout << "----" << std::endl;

			return KMeansDiscretizer(centers);
		}

		template<size_t N, typename FeatureSet>
		static KMeansDiscretizer from(int classes, FeatureSet set)
		{
			return from(classes, set.beginF<N>(), set.endF<N>());
		}
	};
}