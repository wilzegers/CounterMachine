#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>

#include "BoostIncludes.h"

#include "Processing/ExecutionBuilder.h"
#include "Constants.h"
#include "Processing/Lexer.h"
#include "Processing/ParserBase.h"

namespace Processing
{

    class Parser : protected ParserBase
    {
        ExecutionBuilder builder{ std::bind(&ParserBase::GetLocationInfo, static_cast<ParserBase*>(this)) };

    public:

        Parser(const std::wstring filename);

        void Parse();

        Descriptors::Computation GetResultComputation();

    private:

        void ParseConfiguration();

        void ParseOutputReg();

        void ParseRegNumber();

        void ParseRegInit();

        void ParseProgram();

        void ParseInstruction();

        static std::unique_ptr<std::istream> SafelyOpenFile(const std::wstring& filename);

        std::vector<size_t> ParseArguments();
    };

}