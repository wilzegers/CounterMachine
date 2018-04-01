#pragma once

#include "BoostIncludes.h"

#include "Execution/Instruction.h"

#include "Exceptions.h"

#include "Descriptors/Computation.h"

namespace Execution
{
    /// Utasítások vektora.
    using InstructionVector = std::vector<std::unique_ptr<Instruction>>;

    /// Funktor, ami nem csinál semmit.
    /** Arra az esetre, ha futtatáskor nem akarjuk kinyerni a számlálógép jelenlegi állapotát. */
    struct NoAction
    {
        void operator()(const State&/* state*/) {}
    };

    /// Futtatható számlálógép-osztály.
    struct Computation
    {

        /// Konstruktor.
        /**
        * \param descriptor a futtatandó számlálógép leírója.
        * \param input_regs a bemeneti regiszterek értékei.
        */
        Computation(const Descriptors::Computation& descriptor,
            const RegisterValueMap& input_regs);

        /// A számlálógép futtatása.
        void Run()
        {
            RunWith(NoAction());
        }

        /// A számlálógép futtatása a végállapot kinyerésével.
        /**
        * \tparam Functor egy const Execution::State& paraméterrel hívható típus.
        * \param action_after_run const Execution::State& paraméterű hívható objektum.
        */
        template<class Functor>
        void RunWith(Functor action_after_run)
        {
            while (!state.IsDone())
            {
                if (state.GetNextInstruction() >= instructions.size())
                {
                    throw ExceptionNoLocation(Constants::ErrorMessages::instruction_out_of_range,
                        state.GetNextInstruction());
                }
                instructions[state.GetNextInstruction()]->Execute(state);
            }

            action_after_run(std::as_const(state));
            result = state.GetRegisterValue(result_reg);
        }

        /// A számlálógép léptetése.
        void Step()
        {
            StepWith(NoAction());
        }

        /// A számlálógép léptetése a lépés utáni állapot kinyerésével.
        /**
        * \tparam Functor egy const Execution::State& paraméterrel hívható típus.
        * \param action_after_step const Execution::State& paraméterű hívható objektum.
        */
        template<class Functor>
        void StepWith(Functor action_after_step)
        {
            if (!state.IsDone())
            {
                if (state.GetNextInstruction() >= instructions.size())
                {
                    throw ExceptionNoLocation(Constants::ErrorMessages::instruction_out_of_range,
                        state.GetNextInstruction());
                }
                instructions[state.GetNextInstruction()]->Execute(state);

                action_after_step(std::as_const(state));
                if (state.IsDone())
                {
                    result = state.GetRegisterValue(result_reg);
                }
            }
        }

        /// A számlálógép futási állapotának lekérdezése.
        /**
        * \return Igaz, ha vége a futásnak.
        */
        bool IsDone() const
        {
            return state.IsDone();
        }

        /// A számlálógép futtatási eredményének a lekérdezése.
        /**
        * \return a futtatási eredmény. Amennyiben a futtatás nem ért véget, a RegisterValue
        *         legnagyobb lehetséges értéke.
        */
        RegisterValue GetResult() const
        {
            return result;
        }

    private:

        /// Utasításleíró-vektort utasítás-vektorrá transformáló függvény.
        /**
        * \param source az utasítás-leíró vektor.
        * \return az utasítás-vektor.
        */
        static InstructionVector TransformInstructions(const Descriptors::InstructionVector& source);

        /// Utasításleírót utasítássá transformáló függvény.
        /**
        * \param source az utasítás-leíró.
        * \return az utasítás.
        */
        static std::unique_ptr<Instruction> TransformInstruction(const std::unique_ptr<Descriptors::Instruction>& source);

        /// A regiszter-vektort elkészítő függvény.
        /**
        * A konstruktor segédfüggvénye.
        * \param descriptor a futtatandó számlálógép leírója.
        * \param input_regs a bemeneti regiszterek értékei.
        */
        static std::vector<RegisterValue> CreateRegisters(const Descriptors::Computation& descriptor,
            const RegisterValueMap& input_regs);

        State state; ///< A számlálógép jelenlegi állapota.

        RegisterName result_reg; ///< A futtatás eredményét tartalmazó regiszter-cím.

        InstructionVector instructions; ///< Az utasításokat tartalmazó vektor.

        RegisterValue result{ std::numeric_limits<RegisterValue>::max() }; ///< A futtatás eredménye.
    };

}
