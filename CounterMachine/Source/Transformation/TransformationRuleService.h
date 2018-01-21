#pragma once

#include <array>

#include "BoostIncludes.h"

#include "Transformation/TransformationRules.h"
#include "Descriptors/Instruction.h"

namespace Transformation
{

	class TransformationRuleService
	{
	public:

		using InstructionSet = boost::container::flat_set<InstructionType>;
		using InstructionSets = std::array<InstructionSet, 3>;

		using Transformation = std::function<void(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)>;
		using Transformations = std::array<boost::container::flat_map<InstructionType, Transformation>, 3>;

		const InstructionSets& GetSets() const
		{
			return sets;
		}

		const Transformation GetSkip() const
		{
			return Skip;
		}

		const Transformation GetRuleFor(size_t set_number, InstructionType type)
		{
			return rules[set_number].at(type);
		}

	private:

		const InstructionSets sets
		{ {
			{
				InstructionType::Increase,
				InstructionType::Decrease,
				InstructionType::JumpIfZero
			},
			{
				InstructionType::Clear,
				InstructionType::Increase,
				InstructionType::JumpIfEqual
			},
			{
				InstructionType::Increase,
				InstructionType::Copy,
				InstructionType::JumpIfEqual
			}
		} };

		const Transformations rules
		{ {
			{
				{ InstructionType::Clear, Set1_Clear },
				{ InstructionType::Copy, Set1_Copy },
				{ InstructionType::JumpIfEqual, Set1_JumpIfEqual }
			},
			{
				{ InstructionType::Decrease, Set2_Decrease },
				{ InstructionType::JumpIfZero, Set2_JumpIfZero }
			},
			{
				{ InstructionType::Clear, Set3_Clear }
			}
		} };

	};

}
