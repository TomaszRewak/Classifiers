#pragma once

namespace Classifier::Abstraction
{
	class IClassifier
	{
	public:
		virtual void Classify() const = 0;
	};
}