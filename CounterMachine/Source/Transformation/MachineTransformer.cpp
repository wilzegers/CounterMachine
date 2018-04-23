#include <array>

#include "Descriptors/Computation.h"

#include "Transformation/MachineTransformer.h"
#include "Transformation/TransformationRuleService.h"


namespace Transformation
{

    Descriptors::Computation MachineTransformer::Transform(size_t desired_set, const Descriptors::Computation& initial_state)
    {
        TransformedComputation transformed{ initial_state }; ///< Az iteráció előtti állapot.

        // Az algoritmus lefut sorban az elérhető halmazokra, amíg a kívántat nem érjük el.
        for (size_t i = 0; i < desired_set; ++i) 
        {
            bool changed; ///< Igaz, ha volt már az iterációban változtatva a számlálógép.
            // Az átírás addig iterál, amíg van új módosítás a számlálógépben egy iteráció végére.
            do {
                changed = false;
                TransformedComputation temp;
                temp.ReadRegistersFrom(transformed);

                // Az utasítások egyenkénti átírása.
                for (auto& current_instruction : transformed.GetInstructions())
                {
                    InstructionType instruction_type = current_instruction->GetType();

                    // Ha később lehet transformálni az utasítást, akkor most nem kell.
                    const bool will_transform_later = std::any_of(Forward(service.GetSets().begin(), i),
                        Forward(service.GetSets().begin(), desired_set), [=](auto set)
                    {
                        return set.count(instruction_type) != 0;
                    });

                    // Ha a célhalmazban benne van az utasítás, akkor nem kell most átírni.
                    const bool no_need_to_transform = service.GetSets()[desired_set - 1].count(instruction_type) != 0;

                    // Ha az eddigiek igazak, vagy HALT az utasítás, akkor kihagyható az átírás.
                    const bool skippable = instruction_type == InstructionType::Halt
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
                // Véglegesítjük az átírást, majd előkészítjük a terepet a következő iterációhoz.
                temp.FinishedTransformationIteration();
                transformed = std::move(temp);
            } while (changed);
        }

        Descriptors::Computation result{ transformed.GetInstructions(), initial_state.input_regs, initial_state.register_inits,
            initial_state.result_reg, transformed.GetRegisterCount() };

        // A hozzáadott regiszterek feltöltése. 0-val kell őket feltölteni, mert az az invariáns, hogy
        // az értékük 0, ha nincsenek éppen használatban.
        for (size_t i = initial_state.register_count; i < result.register_count; ++i)
        {
            result.register_inits.emplace(i, 0);
        }

        return result;
    }
}
