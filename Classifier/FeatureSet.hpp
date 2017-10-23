#pragma once

#include <vector>
#include <iostream>
#include <functional>

#include "Features.hpp"

namespace Classifier::Data
{
	template<class ...FeatureTypes>
	class FeatureSet : public std::vector<Features<FeatureTypes...>> {
	private:
		template<size_t N>
		using NthType = typename std::tuple_element<N, std::tuple<FeatureTypes...>>::type;

		template<typename... NewFearureTyps>
		auto make_newSet(Features<NewFearureTyps...>) const 
		{
			return FeatureSet<NewFearureTyps...>{};
		}

	public:
		template<size_t N>
		using type = NthType<N>;

		using std::vector<Features<FeatureTypes...>>::push_back;
		void push_back(FeatureTypes... values)
		{
			std::vector<Features<FeatureTypes...>>::push_back(Features<FeatureTypes...>(values...));
		}

		void print() const
		{
			for (auto& object : *this)
			{
				object.print();

				std::cout << std::endl;
			}
		}

	public:
		template<size_t N>
		class FreatureIterator : public std::iterator<std::forward_iterator_tag, NthType<N>>
		{
		private:
			typename std::vector<Features<FeatureTypes...>>::iterator iter;

		public:
			FreatureIterator(typename std::vector<Features<FeatureTypes...>>::iterator iter) :
				iter(iter)
			{ }
			FreatureIterator(const FreatureIterator<N>& mit) : iter(mit.iter) {}

			FreatureIterator<N>& operator++() { ++iter; return *this; }
			FreatureIterator<N> operator++(int) { FreatureIterator<N> tmp(*this); operator++(); return tmp; }
			bool operator==(const FreatureIterator<N>& rhs) const { return iter == rhs.iter; }
			bool operator!=(const FreatureIterator<N>& rhs) const { return iter != rhs.iter; }
			bool operator<(const FreatureIterator<N>& rhs) const { return iter < rhs.iter; }
			NthType<N>& operator*() { return std::get<N>(*iter); }
		};

		using std::vector<Features<FeatureTypes...>>::begin;
		using std::vector<Features<FeatureTypes...>>::end;

		template<size_t N>
		FreatureIterator<N> beginF() { return FreatureIterator<N>(this->begin()); }

		template<size_t N>
		FreatureIterator<N> endF() { return FreatureIterator<N>(this->end()); }
	};
}