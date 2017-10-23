#pragma once

#include <tuple>
#include <iostream>

namespace Classifier::Data
{
	template <typename ...FeatureTypes>
	class Features : public std::tuple<FeatureTypes...>
	{
	private:
#pragma region Variadic Templates
		constexpr auto order() const { return std::make_index_sequence<sizeof...(FeatureTypes)>{}; };
#pragma endregion

		template<size_t Index, typename Function>
		auto get_transformer(Function, std::false_type) const
		{
			using Type = typename std::tuple_element<Index, std::tuple<FeatureTypes...>>::type;

			return [](const Type& value) -> Type { return value; };
		}

		template<size_t Index, typename Function>
		auto get_transformer(Function function, std::true_type) const
		{
			return function;
		}

		template <typename ...NewFreatureTypes>
		auto makeNew(NewFreatureTypes... values) const
		{
			return Features<NewFreatureTypes...>(values...);
		}

		template<size_t ...Order>
		void print_v(std::index_sequence<Order...>) const
		{
			int _[] = { (std::cout << get<Order>() << "\t", 0)... };
		}

		template<typename T, size_t Index>
		T get_r(std::true_type)
		{
			return std::get<Index>(*this);
		}

		template<typename T, size_t Index>
		T get_r(std::false_type)
		{
			throw "Wrong type exception";
		}

		template<typename T>
		T get_v(size_t index, std::index_sequence<>)
		{
			throw "Index out of bounds exception";
		}

		template<typename T, size_t Index, size_t ...Next>
		T get_v(size_t index, std::index_sequence<Index, Next...>)
		{
			using T1 = decltype(std::get<Index>(*this));

			if (index == 0)
				return get_r<T, Index>(std::is_assignable<T1, T>{});
			else
				return get_v<T, Next...>(index - 1, std::index_sequence<Next...>{});
		}

	public:
		constexpr size_t size() { return sizeof...(FeatureTypes); }

		Features() {

		}

		Features(FeatureTypes ...values) : std::tuple<FeatureTypes...>(values...) {
		}

		template<size_t Index> 
		auto get() const
		{
			return std::get<Index>(*this);
		}

		template<typename T>
		T get(size_t index)
		{
			return get_v<T>(index, order());
		}

		void print() const
		{
			print_v(order());
		}
	};
}