#pragma once

#include "Execution/State.h"

namespace Execution
{

	State::State(const std::vector<RegisterValue>& init_values) :
		registers(init_values),
		next_instruction{ 0 },
		done{ false }
	{
	}

}