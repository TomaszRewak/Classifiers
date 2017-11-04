#pragma once

#include <vector>
#include <array>
#include <map>

#include "FeatureSet.hpp"

namespace Classifier::ILA
{
	struct ILACondition
	{
		bool selected = false;
		int value = 0;
	};

	template<typename Class, typename ...Ts>
	struct ILARule
	{
		std::array<ILACondition, sizeof...(Ts)> conditions;
		Class result;

		ILARule()
		{ }

		ILARule(Class result) :
			result(result)
		{ }

		bool match(Data::Features<Ts...>& data)
		{
			for (size_t i = 0; i < conditions.size(); i++)
			{
				ILACondition& condition = conditions[i];

				if (condition.selected && data.get<int>(i) != condition.value)
					return false;
			}

			return true;
		}
	};

	template<typename Class, typename ...Ts>
	using ILARules = std::vector<ILARule<Class, Ts...>>;

	template<typename Class, typename ...Ts>
	class ILAClassifier
	{
	private:
		Class defaultClass;
		ILARules<Class, Ts...> rules;

	public:
		ILAClassifier(ILARules<Class, Ts...> rules, Class defaultClass) :
			rules(rules), defaultClass(defaultClass)
		{ }

		template<typename ...Ts>
		Class classify(Data::Features<Ts...> specimen)
		{
			for (auto& rule : rules)
				if (rule.match(specimen))
					return rule.result;

			return defaultClass;
		}
	};
}