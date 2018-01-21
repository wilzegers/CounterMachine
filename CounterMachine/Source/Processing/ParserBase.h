#pragma once

#include "Processing/Lexer.h"
#include "Exceptions.h"
#include "Processing/ExecutionBuilder.h"

namespace Processing
{

	struct ParserBase
	{
		Lexer lexer;
		const char* name;

		ParserBase(std::unique_ptr<std::istream>&& stream, const char* name) :
			lexer{ name, std::move(stream) },
			name{ name }
		{
		}

		LocationInfo GetLocationInfo() const
		{
			return LocationInfo{ name, lexer.GetLineNumber() };
		}

		template<class ExactSymbol>
		void CurrentSymbolShouldBe() const
		{
			if (lexer.GetCurrentSymbol() == nullptr)
			{
				Throw(Constants::ErrorMessages::unexpected_eof);
			}
			if (!lexer.GetCurrentSymbol()->IsA<ExactSymbol>())
			{
				RaiseNotOfType<ExactSymbol>();
			}
		}

		template<class ExactSymbol>
		const ExactSymbol* SafelyGetSymbolAs() const
		{
			CurrentSymbolShouldBe<ExactSymbol>();
			return lexer.GetCurrentSymbol()->As<ExactSymbol>();
		}

		template<class... Args>
		void Throw(Args... args) const
		{
			throw ExceptionWithLocation(GetLocationInfo(), args...);
		}

		void RaiseUnexpectedSymbol() const
		{
			const Symbol* unexpected = lexer.GetCurrentSymbol();
			Throw(Constants::ErrorMessages::unexpected_symbol,
				unexpected->GetTypeDescription(), unexpected->GetInfoString());
		}

		template<typename ExpectedSymbolType>
		void RaiseNotOfType() const
		{
			const Symbol* unexpected = lexer.GetCurrentSymbol();
			Throw(Constants::ErrorMessages::not_expected_symbol,
				unexpected->GetTypeDescription(), unexpected->GetInfoString(),
				ExpectedSymbolType::description);
		}

		void RaiseUnknownSymbolValue() const
		{
			const Symbol* unexpected = lexer.GetCurrentSymbol();
			Throw(Constants::ErrorMessages::unknown_symbol_value,
				unexpected->GetTypeDescription(), unexpected->GetInfoString());
		}
	};

}