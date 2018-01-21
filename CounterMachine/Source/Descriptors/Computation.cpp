#include "Descriptors/Computation.h"

namespace Descriptors
{
    Computation::Computation(const InstructionVector& instructions,
        const RegisterNameSet& input_regs,
        const RegisterValueMap& register_inits,
        RegisterName result_reg,
        size_t register_count)
        : input_regs{ input_regs },
        register_inits{ register_inits },
        instructions{ CloneContainer(instructions) },
        result_reg{ result_reg },
        register_count{ register_count }
    {
    }

    std::ostream& operator<<(std::ostream& os, const Descriptors::Computation& comp)
    {
        os << Constants::Labels::reg_number << ":" << comp.register_count << std::endl;
        os << Constants::Labels::reg_init << ":" << std::endl;
        for (size_t i = 0; i < comp.register_count; ++i)
        {
            if (comp.input_regs.count(i) != 0)
            {
                os << i << ":" << Constants::Labels::input << std::endl;
            }
            else
            {
                os << i << ":" << comp.register_inits.at(i) << std::endl;
            }
        }
        os << Constants::Labels::output_reg << ":" << comp.result_reg << std::endl;

        os << Constants::Labels::progam << ":" << std::endl;
        for (size_t i = 0; i < comp.instructions.size(); ++i)
        {
            os << i << "." << comp.instructions[i]->ToString() << std::endl;
        }

        return os;
    }
}