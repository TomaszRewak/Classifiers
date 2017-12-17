#pragma once

#include "ILAClassifier.hpp"

#include <set>

namespace Classifier::ILA
{
	class Combinations {
	private:
		size_t _n, _r;
		std::vector<bool> _mask;
		std::vector<size_t> _combination;

		void fill()
		{
			_combination.clear();

			for (size_t i = 0; i < _n; ++i)
				if (_mask[i])
					_combination.push_back(i);
		}

	public:
		Combinations(size_t n, size_t r) :
			_n(n),
			_r(r),
			_mask(n)
		{
			std::fill(_mask.begin(), _mask.begin() + _r, true);
			fill();
		}

		bool next()
		{
			bool hasNext = std::prev_permutation(_mask.begin(), _mask.end());

			if (hasNext)
				fill();

			return hasNext;
		}

		std::vector<size_t>& current()
		{
			return _combination;
		}
	};

	class ILAClassifierBuilder {
	public:
		template <typename Class>
		using Classes = typename std::vector<Class>;

		template <typename ...Ts>
		using Features = typename std::vector<Data::Features<Ts...>>;

		template<typename Class, typename ...Ts>
		struct Builder {
		private:
			Class defaultClass;
			int actuallyMarked = 0,
				toBeMarked = 0;

		public:
			Builder(Class defaultClass) : defaultClass(defaultClass)
			{ }

			ILAClassifier<Class, Ts...> operator()(Classes<Class>& classes, Features<Ts...>& features)
			{
				constexpr size_t N = sizeof...(Ts);
				using Rule = ILARule<Class, Ts...>;

				std::vector<Rule> rules;

				std::set<Class> distinctClasses;
				for (auto c : classes)
					distinctClasses.insert(c);

				for (Class currnetClass : distinctClasses)
				{
					Features<Ts...> currentClassExamples;
					Features<Ts...> otherClassExamples;

					for (size_t i = 0; i < features.size(); i++)
					{
						if (classes[i] == currnetClass)
							currentClassExamples.push_back(features[i]);
						else
							otherClassExamples.push_back(features[i]);
					}

					std::vector<bool> marked(currentClassExamples.size());
					std::vector<bool> considered(currentClassExamples.size());

					for (size_t j = 1; j <= N; )
					{
						int best_amount = 0;
						Rule best_rule;

						Combinations combinations(N, j);

						do
						{
							auto& combination = combinations.current();

							std::fill(considered.begin(), considered.end(), false);

							for (size_t example_i = 0; example_i < currentClassExamples.size(); example_i++)
							{
								if (considered[example_i])
									continue;

								Rule newRule(currnetClass);
								for (size_t combination_v : combination)
								{
									newRule.conditions[combination_v].selected = true;
									newRule.conditions[combination_v].value = currentClassExamples[example_i].get<int>(combination_v);
								}

								int matchesSame = 0;
								for (size_t same_i = example_i; same_i < currentClassExamples.size(); same_i++)
									if (!marked[same_i] && newRule.match(currentClassExamples[same_i]))
									{
										matchesSame++;
										considered[same_i] = true;
									}

								bool matchesOther = false;
								for (size_t other_i = 0; !matchesOther && other_i < otherClassExamples.size(); other_i++)
									if (newRule.match(otherClassExamples[other_i]))
										matchesOther = true;

								if (!matchesOther && matchesSame > best_amount)
								{
									best_amount = matchesSame;
									best_rule = newRule;
								}
							}

						} while (combinations.next());

						if (best_amount)
						{
							rules.push_back(best_rule);

							for (size_t example_i = 0; example_i < currentClassExamples.size(); example_i++)
								if (!marked[example_i] && best_rule.match(currentClassExamples[example_i]))
									marked[example_i] = true;
						}
						else
							j++;
					}

					for (int i = 0; i < currentClassExamples.size(); i++)
					{
						toBeMarked++;
						if (marked[i])
							actuallyMarked++;
					}
				}

				return ILAClassifier<Class, Ts...>(rules, defaultClass);
			}

			double usedExamples()
			{
				return (double)actuallyMarked / toBeMarked;
			}
		};

	private:
		template<typename, typename>
		struct BuilderType;

		template<typename Class, size_t ...N>
		struct BuilderType<Class, std::index_sequence<N...>>
		{
			using type = Builder<Class, typename std::conditional<N == N, int, int>::type...>;
		};

		template<typename Class, size_t N>
		using BuilderType_t = typename BuilderType<Class, std::make_index_sequence<N>>::type;

		template<typename Class, typename ...Ts>
		static Builder<Class, Ts...> get_builder(Class defaultClass)
		{
			return Builder<Class, Ts...>(defaultClass);
		}

	public:
		template<typename Class, size_t N>
		static auto builder(Class defaultClass)
		{
			return BuilderType_t<Class, N>(defaultClass);
		}

		template<typename Class, typename ...Ts>
		static ILAClassifier<Class, Ts...> from(
			std::vector<Class>& classes,
			Data::FeatureSet<Ts...>& features,
			Class defaultClass)
		{
			return get_builder<Class, Ts...>(defaultClass)(classes, features);
		}
	};
}