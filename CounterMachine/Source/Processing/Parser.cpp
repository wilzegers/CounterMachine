#pragma once

#include "Processing/Parser.h"

namespace Processing
{

    Parser::Parser(const std::wstring filename) :
        Parser{ SafelyOpenFile(filename) }
    {
    }

    Parser::Parser(std::unique_ptr<std::istream>&& stream) :
        ParserBase{ std::move(stream), Constants::Locations::program }
    {

    }


    void Parser::Parse()
    {
        ParseConfiguration();
        ParseProgram();
    }


    Descriptors::Computation Parser::GetResultComputation()
    {
        return builder.CreateComputation();
    }


    void Parser::ParseConfiguration()
    {
        boost::container::flat_set<std::string> expected_labels{
            Constants::Labels::output_reg,
            Constants::Labels::reg_init,
            Constants::Labels::reg_number
        };

        while (!expected_labels.empty() && !lexer.IsEndOfFile())
        {
            std::string label = SafelyGetSymbolAs<Symbols::Label>()->GetInformation();

            if (expected_labels.find(label) != expected_labels.end())
            {
                if (label == Constants::Labels::output_reg)
                {
                    lexer.ReadNextSymbol();
                    CurrentSymbolShouldBe<Symbols::Colon>();
                    lexer.ReadNextSymbol();
                    ParseOutputReg();
                }
                else if (label == Constants::Labels::reg_init)
                {
                    lexer.ReadNextSymbol();
                    CurrentSymbolShouldBe<Symbols::Colon>();
                    lexer.ReadNextSymbol();
                    ParseRegInit();
                }
                else if (label == Constants::Labels::reg_number)
                {
                    lexer.ReadNextSymbol();
                    CurrentSymbolShouldBe<Symbols::Colon>();
                    lexer.ReadNextSymbol();
                    ParseRegNumber();
                }
                expected_labels.erase(label);
            }
            else
            {
                RaiseUnknownSymbolValue();
            }
        }
    }


    void Parser::ParseOutputReg()
    {
        auto output_reg = SafelyGetSymbolAs<Symbols::Number>();
        builder.ActOnOutputRegisterName(output_reg->GetInformation());
        lexer.ReadNextSymbol();
    }


    void Parser::ParseRegNumber()
    {
        auto output_reg = SafelyGetSymbolAs<Symbols::Number>();
        builder.ActOnRegisterCount(output_reg->GetInformation());
        lexer.ReadNextSymbol();
    }


    void Parser::ParseRegInit()
    {
        while (CurrentSymbolIs<Symbols::Number>())
        {
            const auto reg_symbol = lexer.GetCurrentSymbol();
            size_t reg_name = reg_symbol->As<Symbols::Number>()->GetInformation();
            lexer.ReadNextSymbol();

            CurrentSymbolShouldBe<Symbols::Colon>();
            lexer.ReadNextSymbol();

            switch (lexer.GetCurrentSymbol()->GetType())
            {
            case SymbolType::Number:
            {
                auto value_symbol = lexer.GetCurrentSymbol()->As<Symbols::Number>();
                builder.ActOnInitPair(reg_name, value_symbol->GetInformation());
                break;
            }
            case SymbolType::Label:
            {
                auto label_symbol = lexer.GetCurrentSymbol()->As<Symbols::Label>();
                if (label_symbol->GetInformation() == Constants::Labels::input)
                {
                    builder.ActOnInputReg(reg_name);
                }
                else
                {
                    RaiseUnknownSymbolValue();
                }
                break;
            }
            default:
            {
                RaiseUnexpectedSymbol();
            }
            }
            lexer.ReadNextSymbol();
        }
    }


    void Parser::ParseProgram()
    {
        std::string program_label = SafelyGetSymbolAs<Symbols::Label>()->GetInformation();
        if (program_label != Constants::Labels::progam)
        {
            RaiseUnknownSymbolValue();
        }
        lexer.ReadNextSymbol();

        CurrentSymbolShouldBe<Symbols::Colon>();
        lexer.ReadNextSymbol();

        while (!lexer.IsEndOfFile())
        {
            if (CurrentSymbolIs<Symbols::Number>())
            {
                lexer.ReadNextSymbol();

                CurrentSymbolShouldBe<Symbols::Dot>();
                lexer.ReadNextSymbol();
            }
            ParseInstruction();
        }
    }


    void Parser::ParseInstruction()
    {
        std::string instruction_name = SafelyGetSymbolAs<Symbols::InstructionName>()->GetInformation();
        lexer.ReadNextSymbol();

        std::vector<size_t> arguments = ParseArguments();

        builder.ActOnInstruction(instruction_name, arguments);
    }


    std::vector<size_t> Parser::ParseArguments()
    {
        CurrentSymbolShouldBe<Symbols::OpenParentheses>();
        lexer.ReadNextSymbol();

        std::vector<size_t> result;

        bool parenthesis_open = true;

        if (CurrentSymbolIs<Symbols::CloseParentheses>())
        {
            parenthesis_open = false;
            lexer.ReadNextSymbol();
        }

        while (parenthesis_open)
        {
            size_t parameter = SafelyGetSymbolAs<Symbols::Number>()->GetInformation();
            result.push_back(parameter);
            lexer.ReadNextSymbol();

            ShouldNotBeEOF();

            if (CurrentSymbolIs<Symbols::Comma>())
            {
                lexer.ReadNextSymbol();
            }
            else if (CurrentSymbolIs<Symbols::CloseParentheses>())
            {
                parenthesis_open = false;
                lexer.ReadNextSymbol();
            }
            else
            {
                RaiseUnexpectedSymbol();
            }
        }
        return result;
    }

    std::unique_ptr<std::istream> Parser::SafelyOpenFile(const std::wstring& filename)
    {
        std::unique_ptr<std::ifstream> result = std::make_unique<std::ifstream>(filename);
        if (!result->is_open())
        {
            throw ExceptionNoLocation(Constants::ErrorMessages::nonexistant_file);
        }
        return std::move(result);
    }

}