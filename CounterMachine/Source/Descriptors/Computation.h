#pragma once

#include <vector>

#include "BoostIncludes.h"
#include "Descriptors/Instruction.h"

namespace Descriptors
{
    /// Utasítás-leírók vektora.
    using InstructionVector = std::vector<std::unique_ptr<Instruction>>;

    /// Számlálógép-leíró osztály.
    struct Computation
    {

        /// Az alapértelmezett move konstruktor.
        Computation(Computation&&) = default;

        /// Konstruktor, amely feltölti adattal az osztályt. Az utasítások klónozódnak.
        Computation(const InstructionVector& instructions,
            const RegisterNameSet& input_regs,
            const RegisterValueMap& register_inits,
            RegisterName result_reg,
            size_t register_count);

        InstructionVector instructions; ///< Az utasításokat tartalmazó vektor.

        RegisterNameSet input_regs; ///< A bemeneti regiszerek halmaza.

        RegisterValueMap register_inits; ///< A nem bemeneti regiszterek és a kezeti értékeik.

        RegisterName result_reg; ///< A számítás eredményét tartalmazó regiszter.

        size_t register_count; ///< A regiszerek száma.
    };

    /// Kiírás operátor.
    /**
    * Fájlba írás esetén a Processing::Parser::Parse az inverze.
    * \param os a kiírás cél streamje.
    * \param comp a kiírandó számlálógép-leíró.
    */
    std::ostream& operator<<(std::ostream& os, const Descriptors::Computation& comp);
}