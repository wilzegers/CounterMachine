#pragma once

#include <sstream>

#include "BoostIncludes.h"
#include "Constants.h"

#include "Processing/ParserBase.h"

namespace Processing
{

	class ArgParser : protected ParserBase
	{
		boost::container::flat_map<size_t, RegisterValue> inits;

	public:

		ArgParser(int argc, char* argv[]);

		ArgParser(const std::string& args);

		void Parse();

		boost::container::flat_map<size_t, RegisterValue> GetInits() { return inits; }

	private:

		static std::unique_ptr<std::istream> MakeArgStream(int argc, char* argv[]);
	};

}