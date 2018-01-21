#pragma once

#include <string>
#include "Constants.h"


namespace Processing
{

	enum class SymbolType
	{
		Label,
		Colon,
		Number,
		Dot,
		InstructionName,
		OpenParentheses,
		CloseParentheses,
		Comma
	};

	class Symbol
	{
	public:

		virtual SymbolType GetType() const = 0;

		virtual const char* GetTypeDescription() const = 0;

		virtual std::string GetInfoString() const = 0;

		virtual ~Symbol() {}

		template<class ExactSymbol>
		ViewPtr<const ExactSymbol> As() const
		{
			if (!IsA<ExactSymbol>())
			{
				throw InternalError("Bad Symbol cast");
			}

			return static_cast<ViewPtr<const ExactSymbol>>(this);
		}

		template<class ExactSymbol>
		bool IsA() const
		{
			return ExactSymbol::type_enum == GetType();
		}
	};

#define DEFINE_SYMBOL(Type, Description, InfoType) class Type; \
class Type : public Symbol {  \
	InfoType information; \
public: \
	static constexpr SymbolType type_enum = SymbolType::Type; \
	static constexpr const char* description = Description; \
	SymbolType GetType() const override \
	{ \
		return SymbolType::Type; \
	} \
	const char* GetTypeDescription() const override \
	{ \
		return Description; \
	} \
	const auto GetInformation() const \
	{ \
		return information; \
	} \
	std::string GetInfoString() const \
	{ \
		std::stringstream ss; \
		ss << GetInformation(); \
		return ss.str(); \
	} \
	Type(InfoType information) : information{ information } {} \
};

	namespace Symbols
	{
		DEFINE_SYMBOL(Label, Constants::Symbols::label, std::string)

		DEFINE_SYMBOL(InstructionName, Constants::Symbols::instruction_name, std::string)

		DEFINE_SYMBOL(Number, Constants::Symbols::number, size_t)

		DEFINE_SYMBOL(Colon, Constants::Symbols::colon, char)

		DEFINE_SYMBOL(Dot, Constants::Symbols::dot, char)

		DEFINE_SYMBOL(OpenParentheses, Constants::Symbols::open_parentheses, char)

		DEFINE_SYMBOL(CloseParentheses, Constants::Symbols::closed_parentheses, char)

		DEFINE_SYMBOL(Comma, Constants::Symbols::comma, char)
	}

}