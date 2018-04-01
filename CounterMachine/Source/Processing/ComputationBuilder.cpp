#include "Processing/ComputationBuilder.h"
#include "Exceptions.h"
#include "Descriptors/Computation.h"

namespace Processing
{

    ComputationBuilder::ComputationBuilder(std::function<LocationInfo()> location_request) :
        location_request{ location_request }
    {
    }

    Descriptors::Computation ComputationBuilder::CreateComputation()
    {
        return Descriptors::Computation{ instructions, input_regs, register_inits, result_reg, reg_count };
    }

    void ComputationBuilder::ActOnRegisterCount(size_t register_count)
    {
        reg_count = register_count;
    }

    void ComputationBuilder::ActOnInputReg(RegisterName reg_name)
    {
        EnsureRegisterUniqueness(reg_name);
        input_regs.insert(reg_name);
    }

    void ComputationBuilder::ActOnOutputRegisterName(RegisterName result_register)
    {
        result_reg = result_register;
    }

    void ComputationBuilder::ActOnInitPair(RegisterName reg_name, RegisterValue init_value)
    {
        EnsureRegisterUniqueness(reg_name);
        register_inits.emplace(reg_name, init_value);
    }

    void ComputationBuilder::ActOnInstruction(const std::string& instruction_name, const std::vector<size_t>& arguments)
    {
        if (instruction_name == Constants::Instructions::clear)
        {
            CreateInstruction<Descriptors::Clear>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::increase)
        {
            CreateInstruction<Descriptors::Increase>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::decrease)
        {
            CreateInstruction<Descriptors::Decrease>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::copy)
        {
            CreateInstruction<Descriptors::Copy>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::jump_if_zero)
        {
            CreateInstruction<Descriptors::JumpIfZero>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::jump_if_equal)
        {
            CreateInstruction<Descriptors::JumpIfEqual>(instruction_name, arguments);
        }
        else if (instruction_name == Constants::Instructions::halt)
        {
            CreateInstruction<Descriptors::Halt>(instruction_name, arguments);
        }
        else
        {
            throw ExceptionWithLocation(location_request(), Constants::ErrorMessages::unknown_symbol_value,
                Constants::Symbols::instruction_name, instruction_name);
        }
    }

    void ComputationBuilder::EnsureRegisterUniqueness(RegisterName register_name) const
    {
        if (register_inits.count(register_name) || input_regs.count(register_name))
        {
            throw ExceptionWithLocation(location_request(), Constants::ErrorMessages::multiple_register_def,
                register_name);
        }
    }

}