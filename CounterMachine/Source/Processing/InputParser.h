#pragma once

#include <sstream>

#include "Processing/ParserBase.h"

namespace Processing
{

    /// A bemeneti regiszterértékek parsere.
    struct InputParser : protected ParserBase
    {
        /// A parancssorból indított program argumentumainak feldolgozására készült konstruktor.
        /**
        * \param argc az argumentumok száma.
        * \param argv a paraméterek.
        */
        InputParser(int argc, char* argv[]);

        /// String forrás feldolgozására készült konstruktor.
        /**
        * \param args a feldolgozandó szöveg.
        */
        InputParser(const std::string& args);

        /// Parser futtatása.
        void Parse();

        /// A parseolt regiszterértékek kinyerése.
        /**
        * \return az inputregiszterek inicializási értékei.
        */
        RegisterValueMap GetInits() { return inits; }

    private:

        /// A parancssorból kapott argumentumok streammé konvertálása.
        /**
        * \param argc az argumentumok száma.
        * \param argv a paraméterek.
        * \return a konkatenált argumentumoknak megfelelő stream.
        */
        static std::unique_ptr<std::istream> MakeArgStream(int argc, char* argv[]);

        RegisterValueMap inits; ///< A parsolt regiszterértékek.
    };

}