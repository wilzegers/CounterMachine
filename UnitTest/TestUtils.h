#pragma once

#include <chrono>

#include "CppUnitTest.h"

#include "Execution/Computation.h"

inline Descriptors::Computation MakeTrivialComputation(std::unique_ptr<Descriptors::Instruction>&& instr,
    const std::vector<size_t>& registers_necessary)
{
    RegisterValueMap registers;
    for (auto reg : registers_necessary)
    {
        registers.emplace(reg, std::hash<RegisterValue>()(reg) % 19 + 2);
    }
    Descriptors::InstructionVector vec;

    vec.push_back(instr->Clone());
    vec.push_back(std::move(instr));
    vec.push_back(std::make_unique<Descriptors::Halt>());

    return Descriptors::Computation{
        std::move(vec),
        RegisterNameSet{},
        registers,
        registers_necessary.front(),
        registers_necessary.size()
    };
}

template <typename AfterFunc = Execution::NoAction, typename DurationT = std::chrono::seconds>
void RunWithTimeOut(Execution::Computation& comp, AfterFunc func = {}, DurationT duration = std::chrono::seconds{ 1 })
{
    auto start = std::chrono::system_clock::now();
    while (!comp.IsDone() && (std::chrono::system_clock::now() - start) < duration)
    {
        comp.StepWith(func);
    }
    if (!comp.IsDone())
    {
        Assert::Fail(L"Timeout during simulation");
    }
}