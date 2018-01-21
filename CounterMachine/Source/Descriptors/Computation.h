#pragma once

#include <vector>

#include "BoostIncludes.h"
#include "Descriptors/Instruction.h"

using RegisterNameSet = boost::container::flat_set<RegisterName>;
using RegisterValueMap = boost::container::flat_map<RegisterName, RegisterValue>;

namespace Descriptors
{
    using InstructionVector = std::vector<std::unique_ptr<Instruction>>;

    struct Computation
    {
        InstructionVector instructions;
        RegisterNameSet input_regs;
        RegisterValueMap register_inits;
        RegisterName result_reg;
        size_t register_count;

        Computation(Computation&&) = default;

        Computation(const InstructionVector& instructions,
            const RegisterNameSet& input_regs,
            const RegisterValueMap& register_inits,
            RegisterName result_reg,
            size_t register_count);
    };

    std::ostream& operator<<(std::ostream& os, const Descriptors::Computation& comp);
}