#pragma once

#include "KNNClassifier.hpp"

namespace Classifier::KNN
{
	class KNNClassifierBuilder {
	public:
		template <typename Class>
		using Classes = typename std::vector<Class>;

		template <typename ...Ts>
		using Features = typename std::vector<Data::Features<Ts...>>;

		template<typename Distance, typename Voting, typename Class, typename ...Ts>
		struct Builder {
		private:
			size_t k;

		public:
			Builder(size_t k) : k(k)
			{ }

			KNNClassifier<Distance, Voting, Class, Ts...> operator()(Classes<Class>& classes, Features<Ts...>& features)
			{
				return KNNClassifier<Distance, Voting, Class, Ts...>(k, classes, features);
			}
		};

	private:
		template<typename, typename, typename, typename>
		struct BuilderType;

		template<typename Distance, typename Voting, typename Class, size_t ...N>
		struct BuilderType<Distance, Voting, Class, std::index_sequence<N...>>
		{
			using type = Builder<Distance, Voting, Class, typename std::conditional<N == N, double, double>::type...>;
		};

		template<typename Distance, typename Voting, typename Class, size_t N>
		using BuilderType_t = typename BuilderType<Distance, Voting, Class, std::make_index_sequence<N>>::type;

		template<typename Distance, typename Voting, typename Class, typename ...Ts>
		static Builder<Distance, Voting, Class, Ts...> get_builder(size_t k)
		{
			return Builder<Distance, Voting, Class, Ts...>(k);
		}

	public:
		template<typename Distance, typename Voting, typename Class, size_t N>
		static auto builder(size_t k)
		{
			return BuilderType_t<Distance, Voting, Class, N>(k);
		}

		template<typename Distance, typename Voting, typename Class, typename ...Ts>
		static KNNClassifier<Distance, Voting, Class, Ts...> from(
			std::vector<Class>& classes,
			Data::FeatureSet<Ts...>& features,
			size_t k)
		{
			return get_builder<Distance, Voting, Class, Ts...>(k)(classes, features);
		}
	};
}