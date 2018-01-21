#pragma once

#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Transformation/TransformedComputation.h"
#include "Descriptors/Computation.h"

namespace Transformation
{

	RegisterReference::~RegisterReference()
	{
	}

	RegisterReference::operator RegisterName() const
	{
		return reg_name;
	}

	RegisterReference::RegisterReference(std::vector<RegisterName>& free_custom_registers)
		: free_custom_registers{ free_custom_registers },
		reg_name{ free_custom_registers.back() }
	{
		if (to_unreg)
		{
			free_custom_registers.pop_back();
		}
	}

	RegisterReference::RegisterReference(RegisterReference&& other)
		: free_custom_registers{ other.free_custom_registers }
	{
		other.to_unreg = false;
	}

	TransformedComputation::TransformedComputation(const Descriptors::Computation& descriptor)
		: instructions{ CloneContainer(descriptor.instructions) },
		register_count{ descriptor.register_count },
		result_reg{ descriptor.result_reg },
		has_zero_register{ false }
	{
	}

	TransformedComputation& TransformedComputation::operator=(TransformedComputation&& other)
	{
		instructions = std::move(other.instructions);
		register_count = other.register_count;
		result_reg = other.result_reg;
		has_zero_register = other.has_zero_register;
		zero_register_name = other.zero_register_name;
		free_helper_registers = other.free_helper_registers;

		return *this;
	}


	TransformedComputation::TransformedComputation(TransformedComputation&& other)
	{
		*this = std::move(other);
	}


	void TransformedComputation::ReadRegistersFrom(const TransformedComputation& other)
	{
		register_count = other.register_count;
		result_reg = other.result_reg;
		has_zero_register = other.has_zero_register;
		zero_register_name = other.zero_register_name;
	}

	size_t TransformedComputation::GetRegisterCount() const
	{
		return register_count;
	}

	RegisterReference TransformedComputation::RequestCustomRegister()
	{
		if (free_helper_registers.size() == 0)
		{
			free_helper_registers.push_back(register_count++);
		}
		return{ free_helper_registers };
	}

	size_t TransformedComputation::RequestZeroRegister()
	{
		if (!has_zero_register)
		{
			has_zero_register = true;
			zero_register_name = register_count++;
		}
		return zero_register_name;
	}

	void TransformedComputation::StartRule()
	{
		++in_rule_call_count;
		if (in_rule_call_count == 1)
		{
			currently_added_lines = 0;
		}
	}

	void TransformedComputation::EndRule()
	{
		--in_rule_call_count;
		if (in_rule_call_count == 0)
		{
			new_line_locations.push_back(new_line_locations.back() + currently_added_lines);
		}
	}

	void TransformedComputation::SkipInstruction(std::unique_ptr<Descriptors::Instruction>&& instr)
	{
		new_line_locations.push_back(new_line_locations.back() + 1);
		if (instr->IsA<Descriptors::JumpIfEqual>() || instr->IsA<Descriptors::JumpIfZero>())
		{
			jumps_to_update.push_back(instructions.size());
		}
		instructions.push_back(std::move(instr));
	}

	void TransformedComputation::FinishedTransformationIteration()
	{
		for (auto i : jumps_to_update)
		{
			if (instructions[i]->IsA<Descriptors::JumpIfEqual>())
			{
				UpdateJumpDestination(instructions[i]->As<Descriptors::JumpIfEqual>()->jump_destination);
			}
			else if (instructions[i]->IsA<Descriptors::JumpIfZero>())
			{
				UpdateJumpDestination(instructions[i]->As<Descriptors::JumpIfZero>()->jump_destination);
			}
		}
	}

	void TransformedComputation::UpdateJumpDestination(size_t& jump_destination) const
	{
		jump_destination = new_line_locations[jump_destination];
	}

}