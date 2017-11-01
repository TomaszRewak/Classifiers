#pragma once

#include <map>
#include <limits>
#include <algorithm>

namespace Classifier::Data::Transformation
{
	template<typename T>
	class DiscreteDiscretizer
	{
	private:
		std::map<T, int> mapper;

	public:
		DiscreteDiscretizer(std::map<T, int> mapper) :
			mapper(mapper)
		{ }

		int operator()(T value) {
			return mapper[value];
		}
	};
}