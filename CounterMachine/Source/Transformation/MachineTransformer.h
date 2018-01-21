#pragma once

#include <array>

#include "Descriptors/Computation.h"
#include "Transformation/TransformationRuleService.h"

namespace Transformation
{

	class MachineTransformer
	{
	public:

		Descriptors::Computation Transform(size_t set_number, const Descriptors::Computation& initial_state);

	private:
		bool IsSkippable(InstructionType type, size_t transform_to, size_t desired_set) const;

		TransformationRuleService service;

	};

}
