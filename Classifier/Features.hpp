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
		template<size_t Offset = 0>
		constexpr auto order() const { return std::make_index_sequence<sizeof...(FeatureTypes) + Offset>{}; };

		template<size_t Index, size_t... Order>
		constexpr auto orderWithout(std::index_sequence<Order...>) const {
			return std::index_sequence<(Order + (Order >= Index ? 1 : 0))...>{};
		}

		template<size_t Index>
		constexpr auto orderWithout() const {
			return orderWithout<Index>(order<-1>());
		}
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

	public:
		Features() {

		}

		Features(FeatureTypes ...values) : std::tuple<FeatureTypes...>(values...) {
		}

		template<size_t ...Order>
		void print(std::index_sequence<Order...>) const
		{
			int _[] = { (std::cout << std::get<Order>(*this) << "\t", 0)... };
		}

		void print() const
		{
			print(order());
		}

		template<size_t Index, typename Function, size_t ...Order>
		auto transform(Function function, std::index_sequence<Order...>) const
		{
			auto transformers = std::make_tuple((get_transformer<Order>(function, std::integral_constant<bool, Order == Index>{}))...);

			return makeNew((std::get<Order>(transformers)(std::get<Order>(*this)))...);
		}

		template<size_t Index, typename Function>
		auto transform(Function function) const
		{
			return transform<Index>(function, order());
		}

		template<size_t Index, size_t ...Order>
		auto remove(std::index_sequence<Order...>) const
		{
			return makeNew((std::get<Order>(*this))...);
		}

		template<size_t Index>
		auto remove() const
		{
			return remove<Index>(orderWithout<Index>());
		}

		template<typename Type, size_t ...Order>
		auto add(std::index_sequence<Order...>) const
		{
			return makeNew((std::get<Order>(*this))..., Type());
		}

		template<typename Type>
		auto add() const
		{
			return add<Type>(order());
		}

		template<size_t First, size_t Second, size_t ...Order>
		auto reorder(std::index_sequence<Order...>) const
		{
			return makeNew((std::get<(Order == First ? Second : Order == Second ? First : Order)>(*this))...);
		}

		template<size_t First, size_t Second>
		auto reorder() const
		{
			return reorder<First, Second>(order<>());
		}
	};
}