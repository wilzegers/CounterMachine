#pragma once

#include "BoostIncludes.h"

#include "Execution/Instruction.h"

#include "Exceptions.h"

#include "Descriptors/Computation.h"

namespace Execution
{
    using InstructionVector = std::vector<std::unique_ptr<Instruction>>;

    struct NoAction
    {
        void operator()(const State&/* state*/) {}
    };

    class Computation
    {
        State state;
        RegisterName result_reg;
        InstructionVector instructions;
        RegisterValue result{ std::numeric_limits<RegisterValue>::max() };
    public:

        Computation(const Descriptors::Computation& descriptor,
            const RegisterValueMap& input_regs);

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

        RegisterValue GetResult() const
        {
            return result;
        }

    private:
        static InstructionVector TransformInstructions(const Descriptors::InstructionVector& source);
        static std::unique_ptr<Instruction> TransformInstruction(const std::unique_ptr<Descriptors::Instruction>& source);


        static std::vector<RegisterValue> CreateRegisters(const Descriptors::Computation& descriptor,
            const RegisterValueMap& input_regs);
    };

}
