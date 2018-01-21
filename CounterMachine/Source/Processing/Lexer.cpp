#include <cctype>
#include <sstream>

#include "BoostIncludes.h"

#include "Constants.h"
#include "Processing/Lexer.h"

namespace Processing
{

    Lexer::Lexer(const char* name, std::unique_ptr<std::istream>&& stream) :
        stream{ std::move(stream) },
        name{ name }
    {
        ReadNextSymbol();
    }


    void Lexer::ReadNextSymbol()
    {
        eof = stream->eof();
        EatSpace();
        if (eof)
        {
            current = nullptr;
            return;
        }
        char next = static_cast<char>(stream->peek());

        if (std::isdigit(next))
        {
            ReadNumber();
        }
        else if (std::isalpha(next))
        {
            if (std::islower(next))
            {
                ReadLabel();
            }
            else
            {
                ReadInstructionName();
            }
        }
        else
        {
            ReadCharSymbol();
        }
    }


    void Lexer::ReadLabel()
    {
        current = std::make_unique<Symbols::Label>(GetWhile([](int c)
        {
            return std::islower(c) || c == '_';
        }));
    }


    void Lexer::ReadInstructionName()
    {
        current = std::make_unique<Symbols::InstructionName>(GetWhile([](int c)
        {
            return std::isupper(c) != 0;
        }));
    }


    void Lexer::ReadNumber()
    {
        size_t value;
        *stream >> value;
        current = std::make_unique<Symbols::Number>(value);
    }


    void Lexer::ReadCharSymbol()
    {
        char next = static_cast<char>(stream->get());
        switch (next)
        {
        case '.':
            current = std::make_unique<Symbols::Dot>(next);
            break;
        case ':':
            current = std::make_unique<Symbols::Colon>(next);
            break;
        case '(':
            current = std::make_unique<Symbols::OpenParentheses>(next);
            break;
        case ')':
            current = std::make_unique<Symbols::CloseParentheses>(next);
            break;
        case ',':
            current = std::make_unique<Symbols::Comma>(next);
            break;
        default:
            throw UnexpectedCharException(name, line_number, next);
        }
    }


    void Lexer::EatSpace()
    {
        while (!stream->eof() && std::isspace(stream->peek()))
        {
            CheckForNewLine();
            stream->get();
        }
        eof = stream->eof();
    }


    void Lexer::CheckForNewLine()
    {
        if (stream->peek() == '\n')
        {
            ++line_number;
        }
    }

    template<class Pred>
    std::string Lexer::GetWhile(Pred predicate)
    {
        std::stringstream ss;
        while (predicate(stream->peek()))
        {
            CheckForNewLine();
            ss << static_cast<char>(stream->get());
        }
        return ss.str();
    }


    size_t Lexer::GetLineNumber() const
    {
        return line_number;
    }


    Lexer::UnexpectedCharException::UnexpectedCharException(const char* name, size_t line_number, char c)
    {
        boost::format prefix(Constants::ErrorMessages::unsupported_character);
        prefix % c;
        boost::format suffix(Constants::ErrorMessages::message_suffix);
        suffix % name % line_number;
        message = prefix.str() + suffix.str();
    }

}