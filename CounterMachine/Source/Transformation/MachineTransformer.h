#pragma once

#include "Descriptors/Computation.h"
#include "Transformation/TransformationRuleService.h"

namespace Transformation
{
    /// Számlálógép-átalakító osztály. 
    /**
    * Egy tetszőleges számlálógépet átalakít úgy, hogy annak az utasításai csak egy háromelemű halmazból
    * kerüljenek ki. Három különféle ilyen halmazzá is tud alakítani. Az átalakítás halmazról-halmazra történik,
    * amíg a kívánt halmazt el nem érjük.
    */
    struct MachineTransformer
    {
        /// Az átalakítást végző metódus.
        /**
        * \param set_number a megcélzott halmaz sorszáma.
        * \param initial_state az átalakítás előtti számlálógép-leíró.
        * \return az átalakított számlálógép-leíró.
        */
        Descriptors::Computation Transform(size_t set_number, const Descriptors::Computation& initial_state);

    private:

        TransformationRuleService service; ///< Az átírási szabályokat tartalmazó objektum.
    };

}
