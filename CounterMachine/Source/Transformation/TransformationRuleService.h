#pragma once

#include <array>

#include "BoostIncludes.h"

#include "Transformation/TransformationRules.h"
#include "Descriptors/Instruction.h"

namespace Transformation
{
    // Az �t�r�si szab�lyokat tartalmaz� oszt�ly.
    struct TransformationRuleService
    {
        /// Utas�t�shalmaz t�pus.
        using InstructionSet = boost::container::flat_set<InstructionType>;
        /// Utas�t�shalmaz-t�mb t�pus.
        using InstructionSets = std::array<InstructionSet, 3>;
        
        /// �t�r�si szab�ly t�pus.
        using Transformation = std::function<void(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr)>;
        
        /// �t�r�si szab�lyokat tartalmaz� t�mb t�pus.
        using Transformations = std::array<boost::container::flat_map<InstructionType, Transformation>, 3>;

        /// Utas�t�shalmazok lek�r�se.
        /**
        * \return az utas�t�shalmazokat tartalmaz� t�mb.
        */
        const InstructionSets& GetSets() const
        {
            return sets;
        }

        /// A kihagy�si szab�ly lek�r�se.
        /**
        * \return a h�vhat� kihagy�si szab�ly.
        */
        const Transformation GetSkip() const
        {
            return Skip;
        }

        /// �t�r�si szab�ly lek�r�se.
        /**
        * \param set_number az �t�r�s c�lhalmaza.
        * \param type az �t�rand� szab�ly t�pusa.
        */
        const Transformation GetRuleFor(size_t set_number, InstructionType type)
        {
            return rules[set_number].at(type);
        }

    private:

        /// Utas�t�shalmazokat tartalmaz� t�mb.
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

        /// �t�r�si szab�lyokat tartalmaz� t�mb.
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
