#include "CppUnitTest.h"

#include "Execution\Instruction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(InstructionTest)
    {

        TEST_METHOD(Instruction_Halt)
        {
            {
                Execution::State state{ { 10, 0 } };
                Execution::Halt{}.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 10 });
                Assert::AreEqual(state.GetRegisterValue(1), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 0 });
                Assert::IsTrue(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_Increase)
        {
            {
                Execution::State state{ {10} };
                Execution::Increase{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 11 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { std::numeric_limits<RegisterValue>::max() } };
                Execution::Increase{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { 0 } };
                Execution::Increase{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 1 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_Decrease)
        {
            {
                Execution::State state{ { 10 } };
                Execution::Decrease{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 9 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { std::numeric_limits<RegisterValue>::max() } };
                Execution::Decrease{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ std::numeric_limits<RegisterValue>::max() - 1 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { 0 } };
                Execution::Decrease{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ std::numeric_limits<RegisterValue>::max() });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_Clear)
        {
            {
                Execution::State state{ { 10 } };
                Execution::Clear{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { std::numeric_limits<RegisterValue>::max() } };
                Execution::Clear{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { 0 } };
                Execution::Clear{ 0 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_Copy)
        {
            {
                Execution::State state{ { 10, 0 } };
                Execution::Copy{ 0, 1 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(1), RegisterValue{ 10 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_JumpIfZero)
        {
            {
                Execution::State state{ { 0 } };
                Execution::JumpIfZero{ 0, 3}.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 3 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { 1 } };
                Execution::JumpIfZero{ 0, 3 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 1 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }

        TEST_METHOD(Instruction_JumpIfEqual)
        {
            {
                Execution::State state{ { 0, 0 } };
                Execution::JumpIfEqual{ 0, 1, 3 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetRegisterValue(1), RegisterValue{ 0 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 3 });
                Assert::IsFalse(state.IsDone());
            }
            {
                Execution::State state{ { 0, 1 } };
                Execution::JumpIfEqual{ 0, 1, 3 }.Execute(state);
                Assert::AreEqual(state.GetRegisterValue(0), RegisterValue{ 0 });
                Assert::AreEqual(state.GetRegisterValue(1), RegisterValue{ 1 });
                Assert::AreEqual(state.GetNextInstruction(), size_t{ 1 });
                Assert::IsFalse(state.IsDone());
            }
        }
    };
}