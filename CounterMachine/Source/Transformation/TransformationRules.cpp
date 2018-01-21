#include <algorithm>
#include <vector>

#include "BoostIncludes.h"

#include "Transformation/TransformationRules.h"
#include "Descriptors/Computation.h"


namespace Transformation
{

    void Set1_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.StartRule();

        auto actual_instr = instr->As<Descriptors::Clear>();

        size_t instruction_number = comp.instructions.size();

        auto zero = comp.RequestZeroRegister();

        comp.Add(new Descriptors::JumpIfZero{ actual_instr->reg_name, instruction_number + 3 });    // 0
        comp.Add(new Descriptors::Decrease{ actual_instr->reg_name });                            // 1
        comp.Add(new Descriptors::JumpIfZero{ zero, instruction_number + 0 });                    // 2

        comp.EndRule();
    }

    void Set1_UnsafeCopyImpl(TransformedComputation& comp, const ViewPtr<Descriptors::Copy> actual_instr)
    {
        comp.StartRule();

        auto zero = comp.RequestZeroRegister();
        auto custom = comp.RequestCustomRegister();

        size_t algo_start = comp.instructions.size();

        comp.Add(new Descriptors::JumpIfZero{ actual_instr->from_register, algo_start + 5 }); // 0
        comp.Add(new Descriptors::Decrease{ actual_instr->from_register });                        // 1
        comp.Add(new Descriptors::Increase{ custom });                                            // 2
        comp.Add(new Descriptors::Increase{ actual_instr->to_register });                        // 3
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start });                                // 4

        comp.Add(new Descriptors::JumpIfZero{ custom, algo_start + 9 });                        // 5
        comp.Add(new Descriptors::Decrease{ custom });                                            // 6
        comp.Add(new Descriptors::Increase{ actual_instr->from_register });                        // 7
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start + 5 });                            // 8

        comp.EndRule();
    }

    void Set1_Copy(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.StartRule();

        auto actual_instr = instr->As<Descriptors::Copy>();

        Set1_Clear(comp, std::make_unique<Descriptors::Clear>(actual_instr->to_register));
        Set1_UnsafeCopyImpl(comp, actual_instr);

        comp.EndRule();
    }

    void Set1_JumpIfEqual(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        auto actual_instr = instr->As<Descriptors::JumpIfEqual>();

        auto zero = comp.RequestZeroRegister();
        auto custom1 = comp.RequestCustomRegister();
        auto custom2 = comp.RequestCustomRegister();

        comp.StartRule();

        Set1_UnsafeCopyImpl(comp, std::make_unique<Descriptors::Copy>(actual_instr->register_a, custom1).get());
        Set1_UnsafeCopyImpl(comp, std::make_unique<Descriptors::Copy>(actual_instr->register_b, custom2).get());

        size_t algo_start = comp.instructions.size();
        size_t placeholder = std::numeric_limits<size_t>::max();

        auto jump1 = new Descriptors::JumpIfZero(custom1, placeholder);
        auto jump2 = new Descriptors::JumpIfZero(custom2, placeholder);

        comp.Add(jump1); // 0
        comp.Add(jump2); // 1

        size_t algo_middle = comp.instructions.size();

        comp.Add(new Descriptors::Decrease{ custom1 });                                            // 0
        comp.Add(new Descriptors::Decrease{ custom2 });                                            // 1
        comp.Add(new Descriptors::JumpIfZero{ zero, algo_start });                                // 2
        comp.AddOuterJump(new Descriptors::JumpIfZero{ custom2, actual_instr->jump_destination });    // 3
        Set1_Clear(comp, std::make_unique<Descriptors::Clear>(custom1));                        // 4 - ?
        Set1_Clear(comp, std::make_unique<Descriptors::Clear>(custom2));                        // ?

        jump1->jump_destination = algo_middle + 3;
        jump2->jump_destination = algo_middle + 4;

        comp.EndRule();

    }

    void Skip(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.SkipInstruction(std::move(instr));
    }

    void Set2_Decrease(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.StartRule();

        auto actual_instr = instr->As<Descriptors::Decrease>();

        auto custom1 = comp.RequestCustomRegister();
        auto custom2 = comp.RequestCustomRegister();
        auto zero = comp.RequestZeroRegister();

        size_t algo_start = comp.instructions.size();

        comp.Add(new Descriptors::JumpIfEqual{ actual_instr->reg_name, custom1, algo_start + 3 });    // 0
        comp.Add(new Descriptors::Increase{ custom1 });                                                // 1
        comp.Add(new Descriptors::JumpIfEqual{ zero, zero, algo_start });                                // 2
        comp.Add(new Descriptors::Clear{ actual_instr->reg_name });                                    // 3

        comp.Add(new Descriptors::Increase{ custom2 });                                // 4
        comp.Add(new Descriptors::JumpIfEqual{ custom1, custom2, algo_start + 9 });    // 5
        comp.Add(new Descriptors::Increase{ custom2 });                                // 6
        comp.Add(new Descriptors::Increase{ actual_instr->reg_name });                // 7
        comp.Add(new Descriptors::JumpIfEqual{ zero, zero, algo_start + 5 });            // 8
        comp.Add(new Descriptors::Clear{ custom1 });                                    // 9
        comp.Add(new Descriptors::Clear{ custom2 });                                    //10

        comp.EndRule();
    }

    void Set2_JumpIfZero(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.StartRule();

        auto actual_instr = instr->As<Descriptors::JumpIfZero>();
        auto zero = comp.RequestZeroRegister();

        comp.AddOuterJump(new Descriptors::JumpIfEqual{ actual_instr->register_name, zero, actual_instr->jump_destination });

        comp.EndRule();
    }

    void Set3_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)
    {
        comp.StartRule();

        auto actual_instr = instr->As<Descriptors::Clear>();
        auto zero = comp.RequestZeroRegister();

        comp.Add(new Descriptors::Copy{ zero, actual_instr->reg_name });

        comp.EndRule();
    }

}