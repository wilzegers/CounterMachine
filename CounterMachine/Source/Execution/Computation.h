#pragma once

#include "BoostIncludes.h"

#include "Execution/Instruction.h"

#include "Exceptions.h"

#include "Descriptors/Computation.h"

namespace Execution
{

	struct NoAction
	{
		void operator()(const State&/* state*/) {}
	};

	class Computation
	{
		State state;
		size_t result_reg;
		std::vector<std::unique_ptr<Instruction>> instructions;
		size_t result{ std::numeric_limits<size_t>::max() };
	public:

		Computation(const Descriptors::Computation& descriptor,
			const boost::container::flat_map<size_t, RegisterValue>& input_regs);

		~Computation() = default;

		void Run()
		{
			RunWith(NoAction());
		}

		template<class Functor>
		void RunWith(Functor action_after_run)
		{
			while (!state.IsDone())
			{
				if (state.GetNextInstruction() >= instructions.size())
				{
					throw ExceptionNoLocation(Constants::ErrorMessages::instruction_out_of_range,
						state.GetNextInstruction());
				}
				instructions[state.GetNextInstruction()]->Execute(state);
			}

			action_after_run(std::as_const(state));
			result = state.GetRegisterValue(result_reg);
		}

		void Step()
		{
			StepWith(NoAction());
		}

		template<class Functor>
		void StepWith(Functor action_after_instruction)
		{
			if (!state.IsDone())
			{
				if (state.GetNextInstruction() >= instructions.size())
				{
					throw ExceptionNoLocation(Constants::ErrorMessages::instruction_out_of_range,
						state.GetNextInstruction());
				}
				instructions[state.GetNextInstruction()]->Execute(state);

				action_after_instruction(std::as_const(state));
				if (state.IsDone())
				{
					result = state.GetRegisterValue(result_reg);
				}
			}
		}

		bool IsDone() const
		{
			return state.IsDone();
		}

		size_t GetResult() const
		{
			return result;
		}

	private:
		static std::vector<std::unique_ptr<Instruction>> TransformInstructions(const std::vector<std::unique_ptr<Descriptors::Instruction>>& source);
		static std::unique_ptr<Instruction> TransformInstruction(const std::unique_ptr<Descriptors::Instruction>& source);


		static std::vector<RegisterValue> CreateRegisters(const Descriptors::Computation& descriptor,
			const boost::container::flat_map<size_t, RegisterValue>& input_regs);
	};

}
