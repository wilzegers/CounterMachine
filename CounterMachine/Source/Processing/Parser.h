#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>

#include "BoostIncludes.h"

#include "Processing/ComputationBuilder.h"
#include "Constants.h"
#include "Processing/Lexer.h"
#include "Processing/ParserBase.h"

namespace Processing
{


    /// A számlálógép kódjának a parsere.
    struct Parser : protected ParserBase
    {
        /// File feldolgozására készült konstruktor.
        /**
        * \param filename a feldolgozandó file neve.
        */
        Parser(const std::string filename);

        /// Szövegfolyam készült konstruktor.
        /**
        * \param stream a feldolgozandó szövegfolyam.
        */
        Parser(std::unique_ptr<std::istream>&& stream);

        /// Parser futtatása.
        void Parse();

        /// A parseolt számlálógép leírójának a kinyerése.
        /**
        * \return a parseolt számlálógép leírója.
        */
        Descriptors::Computation GetResultComputation();

    private:

        /// A Fájl biztonságos megnyitása, ha nem létezik, megfelelő hibát dob.
        /**
        * \param filename a feldolgozandó file neve.
        * \return a megnyitott filestream.
        */
        static std::unique_ptr<std::istream> SafelyOpenFile(const std::string& filename);

        /// Argumentumok parseolása.
        /**
        * \return a parsolt argumentumok.
        */
        std::vector<size_t> ParseArguments();

        /// A számlálógép adatainak parseolása.
        void ParseConfiguration();

        /// A kimeneti regiszter parseolása.
        void ParseOutputReg();

        /// A regiszterszám parseolása.
        void ParseRegNumber();

        /// A számlálógép regiszter-inicializálásának parseolása.
        void ParseRegInit();

        /// A számlálógép utasításainak parseolása.
        void ParseProgram();

        /// Egy számlálógép-utasítás parseolása.
        void ParseInstruction();

        /// Member used for building the computation descriptor
        ComputationBuilder builder{ std::bind(&ParserBase::GetLocationInfo, static_cast<ParserBase*>(this)) };
    };

}
