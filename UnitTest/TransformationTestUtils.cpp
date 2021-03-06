#include "TransformationTestUtils.h"

void TestClear(size_t set)
{
    TestNonJump(set, std::make_unique<Descriptors::Clear>(0), { 0 });
}

void TestIncrease(size_t set)
{
    TestNonJump(set, std::make_unique<Descriptors::Increase>(0), { 0 });
}

void TestDecrease(size_t set)
{
    TestNonJump(set, std::make_unique<Descriptors::Decrease>(0), { 0 });
}

void TestCopy(size_t set)
{
    TestNonJump(set, std::make_unique<Descriptors::Copy>(1, 0), { 0, 1 });
}

void TestJumpIfZero(size_t set)
{
    Descriptors::InstructionVector instr_vector;
    instr_vector.push_back(std::make_unique<Descriptors::JumpIfZero>(0, 2));
    instr_vector.push_back(std::make_unique<Descriptors::JumpIfZero>(1, 3));
    instr_vector.push_back(std::make_unique<Descriptors::Halt>());
    instr_vector.push_back(std::make_unique<Descriptors::Halt>());

    Descriptors::Computation base{ instr_vector, RegisterNameSet{}, { { { 0, 1 },{ 1, 0 } } }, 0, 2 };
    Descriptors::Computation trans_result{ Transformation::MachineTransformer{}.Transform(set, base) };

    Execution::Computation base_comp{ base, {} };
    Execution::Computation trans_comp{ trans_result, {} };

    size_t instr_left_1 = 0;
    size_t instr_left_2 = 0;

    RunWithTimeOut(base_comp, [&instr_left_1, &trans_result](const Execution::State& state) {
        instr_left_1 = trans_result.instructions.size() - state.GetNextInstruction();
    });
    RunWithTimeOut(trans_comp, [&instr_left_2, &trans_result](const Execution::State& state) {
        instr_left_2 = trans_result.instructions.size() - state.GetNextInstruction();
    });

    Assert::AreEqual(instr_left_1, instr_left_2);
}

void TestJumpIfEqual(size_t set)
{
    Descriptors::InstructionVector instr_vector;
    instr_vector.push_back(std::make_unique<Descriptors::JumpIfEqual>(0, 1, 2));
    instr_vector.push_back(std::make_unique<Descriptors::JumpIfEqual>(1, 2, 3));
    instr_vector.push_back(std::make_unique<Descriptors::Halt>());
    instr_vector.push_back(std::make_unique<Descriptors::Halt>());

    Descriptors::Computation base{ instr_vector, RegisterNameSet{}, {{ { 0, 1 }, { 1, 0 }, { 2, 0 } }}, 0, 3 };
    Descriptors::Computation trans_result{ Transformation::MachineTransformer{}.Transform(set, base) };

    Execution::Computation base_comp{ base, {} };
    Execution::Computation trans_comp{ trans_result, {} };

    size_t instr_left_1 = 0;
    size_t instr_left_2 = 0;

    RunWithTimeOut(base_comp, [&instr_left_1, &base](const Execution::State& state) {
        instr_left_1 = base.instructions.size() - state.GetNextInstruction();
    });
    RunWithTimeOut(trans_comp, [&instr_left_2, &trans_result](const Execution::State& state) {
        instr_left_2 = trans_result.instructions.size() - state.GetNextInstruction();
    });

    Assert::AreEqual(instr_left_1, instr_left_2);
}