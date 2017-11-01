#pragma once

#include "FeatureSet.hpp"

namespace Classifier::Data::Transformation
{
	template<typename ...InputFearures>
	class InputFeatures {};

	template<typename ...OutputFeatures>
	class OutputFeatures {};

	template <typename... T>
	class Transformer;

	template <typename ...Input, typename ...Output>
	class Transformer<InputFeatures<Input...>, OutputFeatures<Output...>>
	{
	private:
		using Order = std::make_index_sequence<sizeof...(Output)>;
		using Transformers = std::tuple<std::function<Output(Input)>...>;

		template<size_t N>
		using NthOutput = typename std::tuple_element<N, std::tuple<Output...>>::type;

		template<size_t N>
		using NthTransformer = typename std::tuple_element<N, Transformers>::type;

		template<size_t, typename, typename>
		struct ReplacedType;

		template<size_t N, typename T, size_t ...Ns>
		struct ReplacedType<N, T, std::index_sequence<Ns...>>
		{
			using type = OutputFeatures<typename std::conditional<Ns == N, T, NthOutput<Ns>>::type...>;
		};

		template<size_t N, typename T>
		using ReplacedOutput = typename ReplacedType<N, T, Order>::type;

		template<typename>
		struct Transform;

		template<size_t ...Ns>
		Features<Output...> transform_v(Features<Input...>& object, std::index_sequence<Ns...> = Order{})
		{
			return Features<Output...>((std::get<Ns>(transformers)(std::get<Ns>(object)))...);
		}

		Features<Output...> transform_v(Features<Input...>& object)
		{
			return transform_v(object, Order{});
		}

		template<size_t N, typename Function>
		Function getTransformer_v(Function& function, std::true_type)
		{
			return function;
		}

		template<size_t N, typename Function>
		NthTransformer<N> getTransformer_v(Function& function, std::false_type)
		{
			return std::get<N>(transformers);
		}

		template<size_t N, typename To, typename Function, size_t ...Ns>
		auto getTransformers_v(Function f, std::index_sequence<Ns...>)
		{
			return std::make_tuple(
				(getTransformer_v<Ns>(f, std::bool_constant<N == Ns>{}))...
				);
		}

		template<size_t N, typename To, typename Function>
		auto getTransformers(Function f)
		{
			return getTransformers_v<N, To, Function>(f, Order{});
		}

	private:
		FeatureSet<Input...>& set;
		Transformers transformers;

	public:
		Transformer(FeatureSet<Input...>& set): 
			set(set),
			transformers(([](Input value) -> Output { return value; })...)
		{ }

		Transformer(FeatureSet<Input...>& set, Transformers& transformers) :
			set(set),
			transformers(transformers)
		{ }

		template<size_t N, typename To>
		Transformer<InputFeatures<Input...>, ReplacedOutput<N, To>> add(std::function<To(NthOutput<N>)> function)
		{
			auto newTransformers = getTransformers<N, To>(function);

			return Transformer<InputFeatures<Input...>, ReplacedOutput<N, To>>(set, newTransformers);
		}

		FeatureSet<Output...> transform()
		{
			FeatureSet<Output...> newSet;

			for (Features<Input...>& object : set)
			{
				newSet.push_back(
					transform_v(object)
				);
			}

			return newSet;
		}
	};
}