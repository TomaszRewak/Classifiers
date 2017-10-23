#pragma once

#include "ValidationStatistics.hpp"

namespace Classifier::Validation
{
	template<typename T>
	struct ConfusionMatrix
	{
		T positiveValue;

		int count = 0;

		int TP = 0,
			FP = 0,
			TN = 0,
			FN = 0;

		ConfusionMatrix(T positiveValue) :
			positiveValue(positiveValue)
		{ }

		void add(T& predicted, T& expected)
		{
			count++;

			if (predicted == positiveValue)
			{
				if (expected == positiveValue)
					TP++;
				else
					FP++;
			}
			else
			{
				if (expected == positiveValue)
					FN++;
				else
					TN++;
			}
		}

		ValidationStatistics get()
		{
			return ValidationStatistics(TP, TN, FP, FN);
		}
	};
}