#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Transformation/TransformationRules.h"
#include "Descriptors/Computation.h"


namespace Transformation
{

    void Skip(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.SkipInstruction(std::move(instr));
    }

    void Set1_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::Clear>();

        const auto instruction_number = comp.GetInstructions().size();

        const auto zero = comp.RequestZeroRegister();

        comp.Add(new Descriptors::JumpIfZero{ actual_instr->reg_name, instruction_number + 3 });    // 0
        comp.Add(new Descriptors::Decrease{ actual_instr->reg_name });                              // 1
        comp.Add(new Descriptors::JumpIfZero{ zero, instruction_number + 0 });                      // 2
    }

    void Set1_Copy(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::Copy>();
        const auto zero = comp.RequestZeroRegister();
        const auto custom = comp.RequestHelperRegister();

        comp.Add(new Descriptors::Clear{ actual_instr->to_register });

        const auto algo_start = comp.GetInstructions().size();

        comp.Add(new Descriptors::JumpIfZero{ actual_instr->from_register, algo_start + 5 });       // 0
        comp.Add(new Descriptors::Decrease{ actual_instr->from_register });                         // 1
        comp.Add(new Descriptors::Increase{ custom });                                              // 2
        comp.Add(new Descriptors::Increase{ actual_instr->to_register });                           // 3
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start });                                  // 4

        comp.Add(new Descriptors::JumpIfZero{ custom, algo_start + 9 });                            // 5
        comp.Add(new Descriptors::Decrease{ custom });                                              // 6
        comp.Add(new Descriptors::Increase{ actual_instr->from_register });                         // 7
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start + 5 });                              // 8
    }

    void Set1_JumpIfEqual(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        const RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::JumpIfEqual>();

        const auto zero = comp.RequestZeroRegister();
        const auto custom1 = comp.RequestHelperRegister();
        const auto custom2 = comp.RequestHelperRegister();

        comp.Add(new Descriptors::Copy{ actual_instr->register_a, custom1 });
        comp.Add(new Descriptors::Copy{ actual_instr->register_b, custom2 });

        const auto algo_start = comp.GetInstructions().size();

        comp.Add(new Descriptors::JumpIfZero{ custom1, algo_start + 5 });                               // 0
        comp.Add(new Descriptors::JumpIfZero{ custom2, algo_start + 6 });                               // 1
        comp.Add(new Descriptors::Decrease{ custom1 });                                                 // 2
        comp.Add(new Descriptors::Decrease{ custom2 });                                                 // 3
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start });                                      // 4
        comp.AddOuterJump(new Descriptors::JumpIfZero{ custom2, actual_instr->jump_destination });      // 5
        comp.Add(new Descriptors::Clear{ custom1 });                                                    // 6
        comp.Add(new Descriptors::Clear{ custom2 });                                                    // 7

    }

    void Set2_Decrease(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::Decrease>();

        auto custom1 = comp.RequestHelperRegister();
        auto custom2 = comp.RequestHelperRegister();

        const auto algo_start = comp.GetInstructions().size();

        comp.Add(new Descriptors::JumpIfEqual{ actual_instr->reg_name, custom1, algo_start + 3 });  // 0
        comp.Add(new Descriptors::Increase{ custom1 });                                             // 1
        comp.Add(new Descriptors::JumpIfEqual{ custom1, custom1, algo_start });                           // 2
        comp.Add(new Descriptors::Clear{ actual_instr->reg_name });                                 // 3
        comp.Add(new Descriptors::Increase{ custom2 });                                             // 4
        comp.Add(new Descriptors::JumpIfEqual{ custom1, custom2, algo_start + 9 });                 // 5
        comp.Add(new Descriptors::Increase{ custom2 });                                             // 6
        comp.Add(new Descriptors::Increase{ actual_instr->reg_name });                              // 7
        comp.Add(new Descriptors::JumpIfEqual{ custom1, custom1, algo_start + 5 });                       // 8
        comp.Add(new Descriptors::Clear{ custom1 });                                                // 9
        comp.Add(new Descriptors::Clear{ custom2 });                                                //10
    }

    void Set2_JumpIfZero(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::JumpIfZero>();
        const auto zero = comp.RequestZeroRegister();

        comp.AddOuterJump(new Descriptors::JumpIfEqual{ actual_instr->register_name, zero, actual_instr->jump_destination });
    }

    void Set3_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        RuleGuard guard{ comp };

        auto actual_instr = instr->As<Descriptors::Clear>();
        const auto zero = comp.RequestZeroRegister();

        comp.Add(new Descriptors::Copy{ zero, actual_instr->reg_name });
    }

}