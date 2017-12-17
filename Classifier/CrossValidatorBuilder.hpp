#pragma once

#include "CrossValidator.hpp"

namespace Classifier::Validation
{
	class CrossValidatorBuilder
	{
	public:
		template<typename Builder, typename Class, typename ...Ts>
		static CrossValidator<Builder, Class, Ts...> from(
			Builder& builder,
			Data::ClassSet<Class> classes,
			Data::FeatureSet<Ts...> features)
		{
			return CrossValidator<Builder, Class, Ts...>(builder, classes, features);
		}
	};
}