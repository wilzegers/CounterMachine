#pragma once

#include <vector>

#include "BoostIncludes.h"

#include "Constants.h"
#include "Utility.h"
#include "Exceptions.h"

namespace Execution
{
    /// A számlálógép állapota.
    struct State
    {
        /// Konstruktor.
        /**
        * \param init_values a regiszterek kezdeti értékeivel feltöltött vektor.
        */
        State(const std::vector<RegisterValue>& init_values);

        /// A futtatás állapotának lekérdezése.
        /**
        * \return igaz, ha a futtatás befejeződött.
        */
        bool IsDone() const { return done; }

        /// A futtatás leállítása
        void Halt() { done = true; }

        /// A következő utasítás sorszámának a lekérése.
        /**
        * \return a következő utasítás sorszáma.
        */
        size_t GetNextInstruction() const { return next_instruction; }

        /// A következő utasítás sorszámának a lekérése.
        /**
        * \return a következő utasítás sorszámának a referenciája.
        */
        size_t& GetNextInstruction() { return next_instruction; }

        /// Regiszterérték referenciájnak a lekérése
        /**
        * \param name a regiszter címe
        * \return a regiszter értékének a referenciája
        */
        RegisterValue& GetRegisterValue(RegisterName name);

        /// Regiszterérték lekérése
        /**
        * \param name a regiszter címe
        * \return a regiszter értéke
        */
        RegisterValue GetRegisterValue(RegisterName name) const;

        /// A regiszterértékek vektorának lekérdezése
        /**
        * \return a regiszterértékek vektora
        */
        const std::vector<RegisterValue>& GetRegisterValues() const { return registers; }

    private:

        bool done; ///< A futtatás állapota. Ha igaz, akkor Halt-ra futottunk.

        std::vector<RegisterValue> registers; ///< A regiszterek értékeivel feltöltött vektor.

        size_t next_instruction; ///< A következő utasítás sorszáma.

    };

}