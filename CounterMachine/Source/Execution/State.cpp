#include "Execution/State.h"

namespace Execution
{

    State::State(const std::vector<RegisterValue>& init_values) :
        done{ false },
        registers(init_values),
        next_instruction{ 0 }
    {
    }

    RegisterValue& State::GetRegisterValue(RegisterName name)
    {
        if (name >= registers.size())
        {
            throw ExceptionNoLocation(Constants::ErrorMessages::nonexistant_register, name);
        }
        return registers[name];
    }

    RegisterValue State::GetRegisterValue(RegisterName name) const
    {
        if (name >= registers.size())
        {
            throw ExceptionNoLocation(Constants::ErrorMessages::nonexistant_register, name);
        }
        return registers[name];
    }

}