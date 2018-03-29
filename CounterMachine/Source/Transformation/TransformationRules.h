#pragma once

#include "Descriptors/Computation.h"
#include "Transformation/TransformedComputation.h"

/* Ebben a fájlban az átírási szabályok találhatóak. */

namespace Transformation
{
    /// Ez a szabály akkor használandó, amikor nincs szükség átírásra.
    void Skip(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    /* A szabályok nevének formátuma a következő :
    * <megcélzott halmaz sorszáma>_<az adott halmazba éréshez átalakítandó utasítás>
    */
    void Set1_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    void Set1_Copy(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    void Set1_JumpIfEqual(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    void Set2_Decrease(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    void Set2_JumpIfZero(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

    void Set3_Clear(TransformedComputation& comp, std::unique_ptr<Descriptors::Instruction>&& instr);

}