#pragma once

#include "ValidationStatistics.hpp"

namespace Classifier::Validation
{
	template<typename T>
	struct ConfusionMatrix
	{
		T positiveValue;

		int acc = 0;

		int TP = 0,
			FP = 0,
			TN = 0,
			FN = 0;

		ConfusionMatrix(T positiveValue) :
			positiveValue(positiveValue)
		{ }

		void add(T& predicted, T& expected)
		{
			if (predicted == expected)
				acc++;

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
			return ValidationStatistics(acc, TP, TN, FP, FN);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, ConfusionMatrix<T>& cm)
	{
		std::cout << "for: " << cm.positiveValue << std::endl;
		std::cout << " \t P \t N" << std::endl;
		std::cout << "P \t " << cm.TP << " \t " << cm.FN << std::endl;
		std::cout << "N \t " << cm.FP << " \t " << cm.TN << std::endl;

		return stream;
	}
}