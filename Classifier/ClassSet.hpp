#pragma once

#include <vector>

namespace Classifier::Data
{
	template<typename ClassType>
	class ClassSet : public std::vector<ClassType>
	{ };
}