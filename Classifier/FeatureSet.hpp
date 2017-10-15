#pragma once

#include <vector>
#include <iostream>
#include <functional>

#include "Features.hpp"

namespace Classifier::Data
{
	template<class ...FeatureTypes>
	class FeatureSet {
	private:
		std::vector<Features<FeatureTypes...>> features;

		template<typename... NewFearureTyps>
		auto make_newSet(Features<NewFearureTyps...>) const 
		{
			return FeatureSet<NewFearureTyps...>{};
		}

	public:
		void add(FeatureTypes... values)
		{
			features.push_back(Features<FeatureTypes...>(values...));
		}

		void add(const Features<FeatureTypes...>& newFearures)
		{
			features.push_back(newFearures);
		}

		void print() const
		{
			for (auto& object : features)
			{
				object.print();

				std::cout << std::endl;
			}
		}

		template<size_t Index, typename Function>
		auto transform(Function transformer) const
		{
			using NewSet = decltype(make_newSet(features[0].transform<Index>(transformer)));

			NewSet newSet;

			for (auto& object : features)
			{
				newSet.add(object.transform<Index>(transformer));
			}

			return newSet;
		}

		template<size_t Index>
		auto remove() const
		{
			using NewSet = decltype(make_newSet(features[0].remove<Index>()));

			NewSet newSet;

			for (auto& object : features)
			{
				newSet.add(object.remove<Index>());
			}

			return newSet;
		}

		template<typename Type>
		auto add() const
		{
			using NewSet = decltype(make_newSet(features[0].add<Type>()));

			NewSet newSet;

			for (auto& object : features)
			{
				newSet.add(object.add<Type>());
			}

			return newSet;
		}

		template<size_t First, size_t Second>
		auto reorder() const
		{
			using NewSet = decltype(make_newSet(features[0].reorder<First, Second>()));

			NewSet newSet;

			for (auto& object : features)
			{
				newSet.add(object.reorder<First, Second>());
			}

			return newSet;
		}

		template<typename Function>
		auto process(Function& function) const
		{
			for (auto& object : features)
			{
				function(object);
			}
		}
	};
}