#include "BoostIncludes.h"
#include "Utility.h"
#include "Execution/Computation.h"
#include "Exceptions.h"

namespace Execution
{

    Computation::Computation(const Descriptors::Computation& descriptor,
        const RegisterValueMap& input_regs)
        :
        state{ CreateRegisters(descriptor, input_regs) },
        result_reg{ descriptor.result_reg },
        instructions{ TransformInstructions(descriptor.instructions) }
    {

    }

    InstructionVector Computation::TransformInstructions(const Descriptors::InstructionVector& source)
    {
        InstructionVector result;
        result.reserve(source.size());
        boost::transform(source, std::back_inserter(result), TransformInstruction);
        return result;
    }

    std::vector<RegisterValue> Computation::CreateRegisters(const Descriptors::Computation& descriptor,
        const RegisterValueMap& input_regs)
    {
        std::vector<RegisterValue> result;

        if (input_regs.size() != descriptor.input_regs.size())
        {
            throw ExceptionNoLocation(Constants::ErrorMessages::input_reg_count_mismatch,
                input_regs.size(), descriptor.input_regs.size());
        }

        for (auto& pair : input_regs)
        {
            if (descriptor.input_regs.count(pair.first) == 0)
            {
                throw ExceptionNoLocation(Constants::ErrorMessages::input_reg_name_mismatch, pair.first);
            }
        }

        result.resize(descriptor.register_count);

        for (auto init : descriptor.register_inits)
        {
            result[init.first] = init.second;
        }

        for (auto init : input_regs)
        {
            result[init.first] = init.second;
        }

        return result;
    }

    std::unique_ptr<Instruction> Computation::TransformInstruction(const std::unique_ptr<Descriptors::Instruction>& source)
    {
        switch (source->GetType())
        {
        case InstructionType::Increase:
        {
            auto actual_source = source->As<Descriptors::Increase>();
            return std::make_unique<Increase>(actual_source->reg_name);
        }
        case InstructionType::Decrease:
        {
            auto actual_source = source->As<Descriptors::Decrease>();
            return std::make_unique<Decrease>(actual_source->reg_name);
        }
        case InstructionType::Clear:
        {
            auto actual_source = source->As<Descriptors::Clear>();
            return std::make_unique<Clear>(actual_source->reg_name);
        }
        case InstructionType::Copy:
        {
            auto actual_source = source->As<Descriptors::Copy>();
            return std::make_unique<Copy>(actual_source->from_register, actual_source->to_register);
        }
        case InstructionType::JumpIfZero:
        {
            auto actual_source = source->As<Descriptors::JumpIfZero>();
            return std::make_unique<JumpIfZero>(actual_source->register_name, actual_source->jump_destination);
        }
        case InstructionType::JumpIfEqual:
        {
            auto actual_source = source->As<Descriptors::JumpIfEqual>();
            return std::make_unique<JumpIfEqual>(actual_source->register_a, actual_source->register_b, actual_source->jump_destination);
        }
        case InstructionType::Halt:
        {
            return std::make_unique<Halt>();
        }
        default:
            throw InternalError("Unknown InstructionType value");
        }
    }

}