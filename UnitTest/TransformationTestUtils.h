#pragma once

#include <chrono>
#include <fstream>

#include "CppUnitTest.h"

#include "Transformation/MachineTransformer.h"
#include "Execution/Computation.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template <typename DurationT = std::chrono::seconds>
void TestNonJump(size_t set_number, std::unique_ptr<Descriptors::Instruction>&& instr,
    const std::vector<size_t>& registers_necessary, DurationT duration = std::chrono::seconds{ 1 })
{
    Descriptors::Computation base_instr{ MakeTrivialComputation(std::move(instr), registers_necessary) };
    Descriptors::Computation trans_result{ Transformation::MachineTransformer().Transform(set_number, base_instr) };

    Execution::Computation base_comp{ base_instr, {} };
    Execution::Computation trans_comp{ trans_result, {} };

    RunWithTimeOut(base_comp);
    RunWithTimeOut(trans_comp);

    Assert::AreEqual(base_comp.GetResult(), trans_comp.GetResult());
}

void TestClear(size_t set);

void TestIncrease(size_t set);

void TestDecrease(size_t set);

void TestCopy(size_t set);

void TestJumpIfZero(size_t set);

void TestJumpIfEqual(size_t set);

#define CREATE_INSTR_TEST(Instr, SetNo) TEST_METHOD(Set ## SetNo ## _ ## Instr) \
{ \
    Test ## Instr (SetNo); \
} \

#define CREATE_SET_TEST(SetNo) TEST_CLASS(Set ## SetNo ## Test) \
{ \
    CREATE_INSTR_TEST(Clear, SetNo) \
    CREATE_INSTR_TEST(Increase, SetNo) \
    CREATE_INSTR_TEST(Decrease, SetNo) \
    CREATE_INSTR_TEST(Copy, SetNo) \
    CREATE_INSTR_TEST(JumpIfZero, SetNo) \
    CREATE_INSTR_TEST(JumpIfEqual, SetNo) \
}