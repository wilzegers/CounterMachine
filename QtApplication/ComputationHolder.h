#ifndef MACHINELOGIC_H
#define MACHINELOGIC_H

#include "BoostIncludes.h"
#include "Utility.h"

#include "Execution/Computation.h"

#include <iostream>

#include <QString>

/// A futtatható számlálógép-objektumot tartalmazó osztály.
struct ComputationHolder
{
    /// A számlálógépet inicializáló konstruktor.
    /**
     * \param filename a számlálógépet leíró fájl neve.
     * \param input_str a bemeneti paraméterek szövege.
    */
    ComputationHolder(const QString& filename, const std::string& input_str);

    /// A futtatható számlálógép megtekintését biztosító metódus.
    /**
     * \return Konstans referencia a számlálógép-objektumra.
    */
    const Descriptors::Computation& GetComputationDescriptor();

    /// A számlálógép léptetése a lépés utáni állapot kinyerésével.
    /**
    * \param func const Execution::State& paraméterű hívható objektum.
    */
    template<typename Func>
    void StepProgramWith(Func func)
    {
        comp.StepWith(func);
    }

    /// A tartalmazott számlálógép futtatása a végállapot kinyerésével.
    /**
    * \param func const Execution::State& paraméterű hívható objektum.
    */
    template<typename Func>
    void RunProgramWith(Func func)
    {
        comp.RunWith(func);
    }

private:
    /// A számlálógép-leíró felépítését végző függvény.
    /**
     * \param filename a számlálógépet leíró fájl neve.
     * \return A felépített számlálógép-leíró.
     */
    static Descriptors::Computation CreateDescriptor(const QString& filename);
    /// A bemeneti regiszterek értékeinek kinyerését végző függvény.
    /**
     * \param input_str a bemeneti paraméterek szövege.
     * \return a beolvasott regisztercím -> regiszterérték hozzárendelés.
     */
    static RegisterValueMap ParseInputs(const std::string& input_str);

    Descriptors::Computation comp_descriptor; ///< A számlálógép-leíró objektum.
    Execution::Computation comp; ///< A futtatható számlálógép-objektum.
};

#endif // MACHINELOGIC_H
