#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Transformation/TransformedComputation.h"
#include "Descriptors/Computation.h"

namespace Transformation
{

    RegisterReference::~RegisterReference()
    {
        if (to_unreg)
        {
            free_helper_registers.push_back(reg_name);
        }
    }

    RegisterReference::operator RegisterName() const
    {
        return reg_name;
    }

    RegisterReference::RegisterReference(std::vector<RegisterName>& free_custom_registers)
        : reg_name{ free_custom_registers.back() },
        free_helper_registers{ free_custom_registers }
    {
         free_custom_registers.pop_back();
    }

    RegisterReference::RegisterReference(RegisterReference&& other)
        : free_helper_registers{ other.free_helper_registers }
    {
        other.to_unreg = false;
    }

    Descriptors::InstructionVector& TransformedComputation::GetInstructions()
    {
        return instructions;
    }
    
    const Descriptors::InstructionVector& TransformedComputation::GetInstructions() const
    {
        return instructions;
    }

    TransformedComputation::TransformedComputation(const Descriptors::Computation& descriptor)
        : instructions{ CloneContainer(descriptor.instructions) },
        register_count{ descriptor.register_count },
        result_reg{ descriptor.result_reg }
    {
    }

    TransformedComputation& TransformedComputation::operator=(TransformedComputation&& other)
    {
        instructions = std::move(other.instructions);
        free_helper_registers = other.free_helper_registers;
        ReadRegistersFrom(other);

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

    RegisterReference TransformedComputation::RequestHelperRegister()
    {
        if (free_helper_registers.size() == 0)
        {
            free_helper_registers.push_back(register_count++);
        }
        return { free_helper_registers };
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
        currently_added_lines = 0;
    }

    void TransformedComputation::EndRule()
    {
        new_line_locations.push_back(new_line_locations.back() + currently_added_lines);
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

    RuleGuard::RuleGuard(TransformedComputation& comp) : comp{ comp }
    {
        comp.StartRule();
    }

    RuleGuard::~RuleGuard()
    {
        comp.EndRule();
    }

}