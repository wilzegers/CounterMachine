#pragma once

#include <array>

#include "BoostIncludes.h"

#include "Transformation/TransformationRules.h"
#include "Descriptors/Instruction.h"

namespace Transformation
{
    // Az átírási szabályokat tartalmazó osztály.
    struct TransformationRuleService
    {
        /// Utasításhalmaz típus.
        using InstructionSet = boost::container::flat_set<InstructionType>;
        /// Utasításhalmaz-tömb típus.
        using InstructionSets = std::array<InstructionSet, 3>;
        
        /// Átírási szabály típus.
        using Transformation = std::function<void(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)>;
        
        /// Átírási szabályokat tartalmazó tömb típus.
        using Transformations = std::array<boost::container::flat_map<InstructionType, Transformation>, 3>;

        /// Utasításhalmazok lekérése.
        /**
        * \return az utasításhalmazokat tartalmazó tömb.
        */
        const InstructionSets& GetSets() const
        {
            return sets;
        }

        /// A kihagyási szabály lekérése.
        /**
        * \return a hívható kihagyási szabály.
        */
        const Transformation GetSkip() const
        {
            return Skip;
        }

        /// Átírási szabály lekérése.
        /**
        * \param set_number az átírás célhalmaza.
        * \param type az átírandó szabály típusa.
        */
        const Transformation GetRuleFor(size_t set_number, InstructionType type)
        {
            return rules[set_number].at(type);
        }

    private:

        /// Utasításhalmazokat tartalmazó tömb.
        const InstructionSets sets
        {{
            {
                InstructionType::Increase,
                InstructionType::Decrease,
                InstructionType::JumpIfZero
            },
            {
                InstructionType::Clear,
                InstructionType::Increase,
                InstructionType::JumpIfEqual
            },
            {
                InstructionType::Increase,
                InstructionType::Copy,
                InstructionType::JumpIfEqual
            }
        }};

        /// Átírási szabályokat tartalmazó tömb.
        const Transformations rules
        {{
            {
                { InstructionType::Clear, Set1_Clear },
                { InstructionType::Copy, Set1_Copy },
                { InstructionType::JumpIfEqual, Set1_JumpIfEqual }
            },
            {
                { InstructionType::Decrease, Set2_Decrease },
                { InstructionType::JumpIfZero, Set2_JumpIfZero }
            },
            {
                { InstructionType::Clear, Set3_Clear }
            }
        }};

    };

}
