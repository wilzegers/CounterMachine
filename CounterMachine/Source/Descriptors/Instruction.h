#pragma once

#include "Utility.h"
#include "Constants.h"

#include <string>

/// A különféle utasítás-típusokat reprezentáló felsorolási típus.
enum class InstructionType
{
    Increase,
    Decrease,
    Clear,
    Copy,
    JumpIfZero,
    JumpIfEqual,
    Halt
};

#define REAL_INSTRUCTION_DESCRIPTOR(Name) \
    CLONEABLE(Name, Instruction) \
    InstructionType GetType() const override final \
    { \
        return InstructionType::Name; \
    } \
    static constexpr InstructionType type_enum = InstructionType::Name; \

namespace Descriptors
{
    /// Az utasítás-leírók közös őse.
    struct Instruction
    {
        /// Virtuális destruktor.
        virtual ~Instruction() = default;

        CLONEABLE_BASE(Instruction)

        /// Az utasítás típusát lekérő függvény.
        /**
        * \return Az utasítás típusa.
        */
        virtual InstructionType GetType() const = 0;

        /// A függvénnyel lekérhető, hogy az adott típusú-e az utasítás.
        /** \tparam ActualInstruction a típus, amivel az egyezés kérdéses
            \return Igaz, ha a kérdezett típusú az utasítás.
        */
        template <class ActualInstruction>
        bool IsA() const
        {
            return ActualInstruction::type_enum == GetType();
        }

        /// Ellenőrzötten az adott típussá castolja a konstans utasítást.
        /** Ha nem ActualInstruction típusú az objektum, akkor belső hibajelzés történik.
         *  \tparam ActualInstruction a cast céltípus.
         *  \return Megfelelő típusú pointer.
         */
        template <class ActualInstruction>
        ViewPtr<const ActualInstruction> const As() const
        {
            if (!IsA<ActualInstruction>())
            {
                throw InternalError("Invalid Instruction cast");
            }
            return static_cast<ViewPtr<const ActualInstruction>>(this);
        }

        /// Ellenőrzötten az adott típussá castolja a nem konstans utasítást.
        /** Ha nem ActualInstruction típusú az objektum, akkor belső hibajelzés történik.
        *  \tparam ActualInstruction a cast céltípus.
        *  \return Megfelelő típusú pointer.
        */
        template <class ActualInstruction>
        ViewPtr<ActualInstruction> As()
        {
            if (!IsA<ActualInstruction>())
            {
                throw InternalError("Invalid Instruction cast");
            }
            return static_cast<ViewPtr<ActualInstruction>>(this);
        }

        /// Utasítás szöveggé konvertálása.
        virtual std::string ToString() const = 0;


        /// Egyenlőség-vizsgálat utasításokra.
        bool operator==(const Instruction& other) const
        {
            return this->ToString() == other.ToString();
        }
    };

    /// Az Increase utasítás leírója.
    struct Increase : public Instruction
    {
        RegisterName reg_name; ///< A növelendő regiszter címe.

        static constexpr size_t param_no{ 1 };  ///< Az utasítás számára szükséges paraméterek.
        
        /// Konstruktor.
        /**
         * \param reg_name a növelendő regiszter címe.
         */
        Increase(RegisterName reg_name)
            : reg_name{ reg_name }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(Increase)

        std::string ToString() const override final
        {
            return Constants::Instructions::increase
                + ("(" + std::to_string(reg_name) + ")");
        }
    };

    /// Az Decrease utasítás leírója.
    struct Decrease : public Instruction
    {
        RegisterName reg_name; ///< A csökkentendő regiszter címe.

        static constexpr size_t param_no{ 1 }; ///< Az utasítás számára szükséges paraméterek.


        /// Konstruktor.
        /**
        * \param reg_name a csökkentendő regiszter címe.
        */
        Decrease(RegisterName reg_name)
            : reg_name{ reg_name }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(Decrease)

        std::string ToString() const override final
        {
            return Constants::Instructions::decrease
                + ("(" + std::to_string(reg_name) + ")");
        }
    };

    /// Az Clear utasítás leírója.
    struct Clear : public Instruction
    {
        RegisterName reg_name; ///< A nullázandó regiszter címe.

        static constexpr size_t param_no{ 1 }; ///< Az utasítás számára szükséges paraméterek.

        /// Konstruktor.
        /**
        * \param reg_name a nullázandó regiszter címe.
        */
        Clear(RegisterName reg_name)
            : reg_name{ reg_name }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(Clear)

        std::string ToString() const override final
        {
            return Constants::Instructions::clear
                + ("(" + std::to_string(reg_name) + ")");
        }
    };

    /// Az Copy utasítás leírója.
    struct Copy : public Instruction
    {
        RegisterName from_register; ///< A forrás regiszter címe.
        RegisterName to_register;   ///< A cél regiszter címe.

        static constexpr size_t param_no{ 2 }; ///< Az utasítás számára szükséges paraméterek.

        /// Konstruktor.
        /**
        * \param from_register a forrás regiszter címe.
        * \param to_register a cél regiszter címe.
        */
        Copy(RegisterName from_register, RegisterName to_register)
            : from_register{ from_register },
            to_register{ to_register }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(Copy)

        std::string ToString() const override final
        {
            return Constants::Instructions::copy
                + ("(" + std::to_string(from_register) + "," + std::to_string(to_register) + ")");
        }
    };

    /// Az Jump If Zero utasítás leírója.
    struct JumpIfZero : public Instruction
    {
        RegisterName register_name; ///< A feltétel regiszter címe.
        size_t jump_destination;    ///< Az ugrás célja.

        static constexpr size_t param_no{ 2 }; ///< Az utasítás számára szükséges paraméterek.

        /// Konstruktor.
        /**
        * \param register_name a feltétel regiszter címe.
        * \param jump_destination az ugrás célja.
        */
        JumpIfZero(RegisterName register_name, RegisterName jump_destination)
            : register_name{ register_name },
            jump_destination{ jump_destination }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(JumpIfZero)

        std::string ToString() const override final
        {
            return Constants::Instructions::jump_if_zero
                + ("(" + std::to_string(register_name) + "," + std::to_string(jump_destination) + ")");
        }
    };

    /// Az Jump If Equal utasítás leírója.
    struct JumpIfEqual : public Instruction
    {
        RegisterName register_a; ///< Az egyik összehasonlítandó regiszter címe.
        RegisterName register_b; ///< A másik összehasonlítandó regiszter címe.
        size_t jump_destination; ///< Az ugrás célja.

        static constexpr size_t param_no{ 3 }; ///< Az utasítás számára szükséges paraméterek.

        /// Konstruktor.
        /**
        * \param register_a az egyik összehasonlítandó regiszter címe.
        * \param register_b a másik összehasonlítandó regiszter címe.
        * \param jump_destination az ugrás célja.
        */
        JumpIfEqual(RegisterName register_a, RegisterName register_b,  size_t jump_destination)
            : register_a{ register_a },
            register_b{ register_b },
            jump_destination{ jump_destination }
        {
        }

        REAL_INSTRUCTION_DESCRIPTOR(JumpIfEqual)

        std::string ToString() const override final
        {
            return Constants::Instructions::jump_if_equal
                + ("(" + std::to_string(register_a) + "," + std::to_string(register_b) + "," + std::to_string(jump_destination) + ")");
        }
    };

    /// Az Halt utasítás leírója.
    struct Halt : public Instruction
    {
        static constexpr size_t param_no{ 0 }; ///< Az utasítás számára szükséges paraméterek.

        REAL_INSTRUCTION_DESCRIPTOR(Halt)

        std::string ToString() const override final
        {
            return Constants::Instructions::halt + std::string{ "()" };
        }
    };
}