#include "Processing/ArgParser.h"

#include <memory>

namespace Processing
{

	ArgParser::ArgParser(int argc, char* argv[])
		: ParserBase{ MakeArgStream(argc, argv), Constants::Locations::parameters }
	{
	}


	ArgParser::ArgParser(const std::string& args)
		: ParserBase{ std::make_unique<std::stringstream>(args), Constants::Locations::parameters }
	{
	}


	void ArgParser::Parse()
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


	std::unique_ptr<std::istream> ArgParser::MakeArgStream(int argc, char* argv[])
	{
		auto stream = std::make_unique<std::stringstream>();
		for (int i = 1; i < argc; ++i)
		{
			*stream << argv[i];
		}
		return std::move(stream);
	}

}
