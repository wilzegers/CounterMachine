#pragma once

#include <vector>

#include "BoostIncludes.h"

#include "Constants.h"
#include "Utility.h"

namespace Execution
{

    class State
    {
        bool done;
        std::vector<RegisterValue> registers;
        size_t next_instruction;

    public:

        State(const std::vector<RegisterValue>& init_values);

        bool IsDone() const { return done; }

        void Halt() { done = true; }

        size_t GetNextInstruction() const { return next_instruction; }

        size_t& GetNextInstruction() { return next_instruction; }

        RegisterValue& GetRegisterValue(RegisterName name) { return registers[name]; }

        const std::vector<RegisterValue>& GetRegisterValues() const { return registers; }

        RegisterValue GetRegisterValue(RegisterName name) const { return registers[name]; }

    };

}