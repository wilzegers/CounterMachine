#include "Processing/InputParser.h"

namespace Processing
{

    InputParser::InputParser(int argc, char* argv[])
        : ParserBase{ MakeArgStream(argc, argv), Constants::Locations::parameters }
    {
    }


    InputParser::InputParser(const std::string& args)
        : ParserBase{ std::make_unique<std::stringstream>(args), Constants::Locations::parameters }
    {
    }


    void InputParser::Parse()
    {
        while (!lexer.IsEndOfFile())
        {
            RegisterName register_name = SafelyGetSymbolAs<Symbols::Number>()->GetInformation();
            lexer.ReadNextSymbol();

            CurrentSymbolShouldBe<Symbols::Colon>();
            lexer.ReadNextSymbol();

            RegisterValue init_value = SafelyGetSymbolAs<Symbols::Number>()->GetInformation();
            lexer.ReadNextSymbol();

            inits.emplace(register_name, init_value);
        }
    }


    std::unique_ptr<std::istream> InputParser::MakeArgStream(int argc, char* argv[])
    {
        auto stream = std::make_unique<std::stringstream>();
        for (int i = 1; i < argc; ++i)
        {
            *stream << argv[i];
        }
        return std::move(stream);
    }

}
