#pragma once

namespace Classifier::Validation
{
	struct Metrice
	{
		int count;
		double value;

		Metrice() :
			count(0)
		{ }

		Metrice(double value, int count, bool hasValue = true) :
			value(value),
			count(hasValue ? count : 0)
		{ }

		Metrice operator+(const Metrice& second)
		{
			if (count && second.count)
				return Metrice(
					(value * count + second.value * second.count) / (count + second.count), 
					count + second.count);
			if (count)
				return *this;
			return second;
		}
	};

	std::ostream& operator<<(std::ostream& stream, const Metrice& m)
	{
		if (m.count)
			stream << m.value;
		else
			stream << "-";

		return stream;
	}

	struct ValidationStatistics
	{
		Metrice acc;
		Metrice prec;
		Metrice rec;
		Metrice fscore;

		ValidationStatistics()
		{ }

		ValidationStatistics(int TP, int TN, int FP, int FN)
		{
			int total = TP + TN + FP + FN;

			acc = Metrice(
				(double)(TP + TN) / (TP + TN + FP + FN), 
				total
			);

			prec = Metrice(
				(double)TP / (TP + FP), 
				total, 
				TP + FP != 0
			);

			rec = Metrice(
				(double)TP / (TP + FN), 
				total, 
				TP + FN != 0
			);

			fscore = Metrice(
				2 * prec.value * rec.value / (prec.value + rec.value), 
				total, 
				prec.count != 0 && rec.count != 0 && prec.value * rec.value != 0
			);
		}

		void operator+=(const ValidationStatistics& second)
		{
			acc = acc + second.acc;
			prec = prec + second.prec;
			rec = rec + second.rec;
			fscore = fscore + second.fscore;
		}
	};

	std::ostream& operator<<(std::ostream& stream, const ValidationStatistics& stats)
	{
		std::cout 
			<< "acc (" << stats.acc << "), \t" 
			<< "prec (" << stats.prec << "), \t"
			<< "rec (" << stats.rec << "), \t" 
			<< "fscore (" << stats.fscore << ")" << std::endl;

		return stream;
	}
}