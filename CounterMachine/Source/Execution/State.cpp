#include "Execution/State.h"

namespace Execution
{

    State::State(const std::vector<RegisterValue>& init_values) :
        done{ false },
        registers(init_values),
        next_instruction{ 0 }
    {
    }

}