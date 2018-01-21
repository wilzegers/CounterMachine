#pragma once

#include <vector>

#include "BoostIncludes.h"
#include "Descriptors/Instruction.h"

namespace Descriptors
{

	struct Computation
	{
		std::vector<std::unique_ptr<Instruction>> instructions;
		boost::container::flat_set<size_t> input_regs;
		boost::container::flat_map<size_t, RegisterValue> register_inits;
		size_t result_reg;
		size_t register_count;

		Computation(Computation&&) = default;

		Computation(const std::vector<std::unique_ptr<Descriptors::Instruction>>& instructions,
			const boost::container::flat_set<size_t>& input_regs,
			const boost::container::flat_map<size_t, RegisterValue>& register_inits,
			size_t result_reg,
			size_t register_count);
	};

	std::ostream& operator<<(std::ostream& os, const Descriptors::Computation& comp);
}