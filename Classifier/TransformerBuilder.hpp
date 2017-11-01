#pragma once

#include "Transformer.hpp"

namespace Classifier::Data::Transformation
{
	class TransformerBuilder
	{
	public:
		template<typename ...Ts>
		static Transformer<InputFeatures<Ts...>, OutputFeatures<Ts...>> from(FeatureSet<Ts...>& set)
		{
			return Transformer<InputFeatures<Ts...>, OutputFeatures<Ts...>>(set);
		}
	};
}