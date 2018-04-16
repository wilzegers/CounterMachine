#pragma once

#include "Execution/State.h"
#include "Constants.h"

#include "Descriptors/Instruction.h"

namespace Execution
{
    /// A végrehajtható utasítások közös őse.
    struct Instruction
    {
        /// Az utasítás végrehajtása
        /**
        * \param state a módosítandó programállapot.
        */
        void Execute(State& state)
        {
            ChangeRegisters(state);
            ToNextInstruction(state);
        }

        /// Polimorfizmushoz szükséges virtuális destruktor.
        virtual ~Instruction() = default;

        /// Az utasítás kihatása a regiszterek állapotára.
        /**
        * Alapértelmezett viselkedésben nem csinál semmit.
        */
        virtual void ChangeRegisters(State& /*state*/) {}

        /// Az utasítás kihatása a következő utasítás sorszámára.
        /**
        * Alapértelmezett viselkedésben a következőre áll.
        */
        virtual void ToNextInstruction(State& state)
        {
            ++state.GetNextInstruction();
        }
    };

    /// A végrehajtható Increase utasítás.
    struct Increase final : public Instruction
    {
        RegisterName register_name; ///< a növelendő regiszter címe.

        /// Konstruktor.
        /**
        * \param register_name a növelendő regiszter címe.
        */
        Increase(RegisterName register_name) : register_name{ register_name }
        {
        }

        virtual void ChangeRegisters(State& state) override
        {
            ++state.GetRegisterValue(register_name);
        }
    };

    /// A végrehajtható Decrease utasítás.
    struct Decrease final : public Instruction
    {
        RegisterName register_name; ///< a csökkentendő regiszter címe.

        /// Konstruktor.
        /**
        * \param register_name a csökkentendő regiszter címe.
        */
        Decrease(RegisterName register_name) : register_name{ register_name }
        {
        }

        virtual void ChangeRegisters(State& state) override
        {
            auto& reg_ref = state.GetRegisterValue(register_name);
            if (reg_ref == 0)
            {
                throw ExceptionNoLocation(Constants::ErrorMessages::decrease_zero, register_name);
            }
            --state.GetRegisterValue(register_name);
        }
    };

    /// A végrehajtható Clear utasítás.
    struct Clear final : public Instruction
    {
        RegisterName register_name; ///< a kinullázandó regiszter címe.

        /// Konstruktor.
        /**
        * \param register_name a kinullázandó regiszter címe.
        */
        Clear(RegisterName register_name) : register_name{ register_name }
        {
        }

        virtual void ChangeRegisters(State& state) override
        {
            state.GetRegisterValue(register_name) = 0;
        }
    };

    /// A végrehajtható Copy utasítás.
    struct Copy final : public Instruction
    {
        RegisterName from_register; ///< a forrás regiszter címe.
        RegisterName to_register;   ///< a cél regiszter címe.

        /// Konstruktor.
        /**
        * \param from_register a forrás regiszter címe.
        * \param to_register a cél regiszter címe.
        */
        Copy(RegisterName from_register, RegisterName to_register) : from_register{ from_register }, to_register{ to_register }
        {
        }

        virtual void ChangeRegisters(State& state) override
        {
            state.GetRegisterValue(to_register) = state.GetRegisterValue(from_register);
        }
    };

    /// A végrehajtható Jump If Zero utasítás.
    struct JumpIfZero final : public Instruction
    {
        RegisterName register_name; ///< a feltétel-regiszter címe.
        size_t jump_destination;    ///< az ugrás célja.

        /// Konstruktor.
        /**
        * \param register_name a feltétel regiszter címe.
        * \param jump_destination az ugrás célja.
        */
        JumpIfZero(RegisterName register_name, size_t jump_destination) : register_name{ register_name }, jump_destination{ jump_destination }
        {
        }

        virtual void ToNextInstruction(State& state) override
        {
            if (state.GetRegisterValue(register_name) == 0)
            {
                state.GetNextInstruction() = jump_destination;
            }
            else
            {
                Instruction::ToNextInstruction(state);
            }
        }
    };

    /// A végrehajtható Jump If Equal utasítás.
    struct JumpIfEqual final : public Instruction
    {
        RegisterName register_a; ///< az egyik összehasonlítandó regiszter címe.
        RegisterName register_b; ///< a másik összehasonlítandó regiszter címe.
        size_t jump_destination; ///< az ugrás célja.

        /// Konstruktor.
        /**
        * \param register_a az egyik összehasonlítandó regiszter címe.
        * \param register_b a másik összehasonlítandó regiszter címe.
        * \param jump_destination az ugrás célja.
        */
        JumpIfEqual(RegisterName register_a, RegisterName register_b, size_t jump_destination)
            : register_a{ register_a }, register_b{ register_b }, jump_destination{ jump_destination }
        {
        }

        virtual void ToNextInstruction(State& state) override
        {
            if (state.GetRegisterValue(register_a) == state.GetRegisterValue(register_b))
            {
                state.GetNextInstruction() = jump_destination;
            }
            else
            {
                Instruction::ToNextInstruction(state);
            }
        }
    };

    /// A végrehajtható Halt utasítás.
    struct Halt final : public Instruction
    {
        virtual void ToNextInstruction(State& state) override
        {
            state.Halt();
        }
    };

}