#pragma once

#include <array>

#include "Descriptors/Computation.h"

#include "Transformation/MachineTransformer.h"
#include "Transformation/TransformationRuleService.h"


namespace Transformation
{

    Descriptors::Computation MachineTransformer::Transform(size_t desired_set, const Descriptors::Computation& initial_state)
    {
        TransformedComputation transformed{ initial_state };
        for (size_t i = 0; i < desired_set; ++i)
        {
            bool changed;
            do {
                changed = false;
                TransformedComputation temp;
                temp.ReadRegistersFrom(transformed);

                for (auto& current_instruction : transformed.instructions)
                {
                    InstructionType instruction_type = current_instruction->GetType();

                    bool will_transform_later = std::any_of(Forward(service.GetSets().begin(), i),
                        Forward(service.GetSets().begin(), desired_set), [=](auto set)
                    {
                        return set.count(instruction_type) != 0;
                    });

                    bool no_need_to_transform = service.GetSets()[desired_set - 1].find(instruction_type)
                        != service.GetSets()[desired_set - 1].end();

                    bool skippable = instruction_type == InstructionType::Halt
                        || will_transform_later || no_need_to_transform;

                    if (skippable)
                    {
                        service.GetSkip()(temp, std::move(current_instruction));
                    }
                    else
                    {
                        changed = true;
                        service.GetRuleFor(i, instruction_type)(temp, std::move(current_instruction));
                    }
                }
                temp.FinishedTransformationIteration();
                transformed = std::move(temp);
            } while (changed);
        }

        Descriptors::Computation result{ transformed.instructions, initial_state.input_regs, initial_state.register_inits,
            initial_state.result_reg, transformed.GetRegisterCount() };

        for (size_t i = initial_state.register_count; i < result.register_count; ++i)
        {
            result.register_inits.emplace(i, 0);
        }

        return result;
    }

    bool MachineTransformer::IsSkippable(InstructionType type, size_t transform_to, size_t desired_set) const
    {
        return type == InstructionType::Halt
            || service.GetSets()[desired_set - 1].find(type) != service.GetSets()[desired_set - 1].end()
            || std::any_of(Forward(service.GetSets().begin(), transform_to), Forward(service.GetSets().begin(), desired_set), [=](auto set)
            {
                return set.find(type) != set.end();
            });
    }

}
