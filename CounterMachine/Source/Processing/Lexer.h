#pragma once

#include <fstream>
#include "Utility.h"

#include "Processing/Symbol.h"

namespace Processing
{

    class Lexer
    {
        std::unique_ptr<Symbol> current{ nullptr };
        std::unique_ptr<std::istream> stream;
        bool eof{ true };
        size_t line_number{ 1 };
        const char* name;

    public:

        Lexer(const char* name, std::unique_ptr<std::istream>&& stream);

        class UnexpectedCharException : public std::exception
        {
            std::string message;

        public:

            UnexpectedCharException(const char* name, size_t line_number, char c);

            virtual const char* what() const override { return message.c_str(); }
        };

        void ReadNextSymbol();

        const ViewPtr<Symbol> GetCurrentSymbol() const { return MakeView(current); }

        bool IsEndOfFile() const { return eof; }

        size_t GetLineNumber() const;

    private:

        void ReadLabel();

        void ReadInstructionName();

        void ReadNumber();

        void ReadCharSymbol();

        void EatSpace();

        void CheckForNewLine();

        template<class Pred>
        std::string GetWhile(Pred predicate);
    };

}