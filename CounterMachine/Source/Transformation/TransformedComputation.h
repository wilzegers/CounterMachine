#pragma once

#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Descriptors/Computation.h"


namespace Transformation
{

	struct RegisterReference
	{
		RegisterName reg_name;
		bool to_unreg{ true };

		~RegisterReference();

		operator RegisterName() const;

		RegisterReference(const RegisterReference&) = delete;
		RegisterReference(RegisterReference&&);
		RegisterReference(std::vector<RegisterName>& free_custom_registers);

	private:
		std::vector<RegisterName>& free_custom_registers;
	};

	struct TransformedComputation
	{
		Descriptors::InstructionVector instructions;
		RegisterName result_reg;

		TransformedComputation() = default;

		TransformedComputation(const Descriptors::Computation& descriptor);

		TransformedComputation& operator=(TransformedComputation&& other);

		TransformedComputation(TransformedComputation&& other);

		void ReadRegistersFrom(const TransformedComputation& other);

		size_t GetRegisterCount() const;

		RegisterReference RequestCustomRegister();

		RegisterName RequestZeroRegister();

		template<typename InstructionType>
		void Add(InstructionType* instr)
		{
			++currently_added_lines;
			instructions.push_back(std::unique_ptr<InstructionType>(instr));
		}

		template<typename InstructionType>
		void AddOuterJump(InstructionType* instr)
		{
			jumps_to_update.push_back(instructions.size());
			Add<InstructionType>(instr);
		}

		void StartRule();

		void EndRule();

		void SkipInstruction(std::unique_ptr<Descriptors::Instruction>&& instr);

		void FinishedTransformationIteration();

	private:

		void UpdateJumpDestination(size_t& jump_destination) const;

		std::vector<RegisterName> free_helper_registers;
		size_t register_count;
		bool has_zero_register;
		RegisterName zero_register_name;
		std::vector<size_t> new_line_locations{ { 0 } };
		std::vector<size_t> jumps_to_update;
		size_t current_line{ 0 };
		size_t currently_added_lines{ 0 };
		size_t in_rule_call_count{ 0 };
	};

}
