#pragma once

#include <sstream>

#include "BoostIncludes.h"
#include "Constants.h"

#include "Processing/ParserBase.h"

namespace Processing
{

	class ArgParser : protected ParserBase
	{
		RegisterValueMap inits;

	public:

		ArgParser(int argc, char* argv[]);

		ArgParser(const std::string& args);

		void Parse();

		RegisterValueMap GetInits() { return inits; }

	private:

		static std::unique_ptr<std::istream> MakeArgStream(int argc, char* argv[]);
	};

}