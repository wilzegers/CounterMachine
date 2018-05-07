#include "CppUnitTest.h"

#include "Processing\Parser.h"
#include "Execution\Computation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool StringMatches(const std::string& string_template,const std::string& string)
{
    auto first_param_place = std::find(std::begin(string_template), std::end(string_template), '%');

    return std::equal(std::begin(string_template), first_param_place, std::begin(string));
}

template<typename StringT1, typename StringT2>
void ShouldThrowOn(StringT1&& to_parse, StringT2&& message, RegisterValueMap&& inits = {})
{
    try
    {
        auto stream = std::make_unique<std::stringstream>(std::forward<StringT1>(to_parse));

        Processing::Parser p{ std::move(stream) };
        p.Parse();
        Execution::Computation{ p.GetResultComputation(), inits }.Run();
    }
    catch (std::exception& e)
    {
        Assert::IsTrue(StringMatches(message, e.what()));
        return;
    }
    Assert::Fail(L"function was expected to fail but it succeded.");
}

#define VALID_CONFIG "register_number:1" \
"output:0" \
"inits:" \
"0:0"

#define VALID_PROGRAM VALID_CONFIG "program: HALT()"

namespace UnitTest
{
    TEST_CLASS(InstructionTest)
    {
        TEST_METHOD(Errors_UnsupportedChar)
        {
            ShouldThrowOn(
                ";",
                Constants::ErrorMessages::unsupported_character
            );
        }

        TEST_METHOD(Errors_UnexpectedEOF)
        {
            ShouldThrowOn(
                "register_number",
                Constants::ErrorMessages::unexpected_eof
            );
        }

        TEST_METHOD(Errors_UnexpectedSymbol)
        {
            ShouldThrowOn(
                VALID_CONFIG
                "program:"
                "alma",
                Constants::ErrorMessages::unexpected_symbol
            );
        }

        TEST_METHOD(Errors_UnexpectedSymbolValue)
        {
            ShouldThrowOn(
                "almafa:",
                Constants::ErrorMessages::unknown_symbol_value
            );
        }

        TEST_METHOD(Errors_NotExpectedSymbol)
        {
            ShouldThrowOn(
                "register_number12",
                Constants::ErrorMessages::not_expected_symbol
            );
        }

        TEST_METHOD(Errors_ArgumentError)
        {
            ShouldThrowOn(
                VALID_CONFIG
                "program:"
                "HALT(1)",
                Constants::ErrorMessages::argument_error
            );
        }

        TEST_METHOD(Errors_MultipleRegisterDef)
        {
            ShouldThrowOn(
                VALID_CONFIG
                " 0:0 ",
                Constants::ErrorMessages::multiple_register_def
            );
        }

        TEST_METHOD(Errors_InputCountMismatch)
        {
            ShouldThrowOn(
                VALID_PROGRAM,
                Constants::ErrorMessages::input_reg_count_mismatch,
                { {0,0} }
            );
        }

        TEST_METHOD(Errors_InputNameMismatch)
        {
            ShouldThrowOn("register_number:1"
                "output:0"
                "inits:"
                "0:input"
                " program:"
                " HALT()",
                Constants::ErrorMessages::input_reg_name_mismatch,
                { { 1,0 } }
            );
        }

        TEST_METHOD(Errors_NonexistantRegister)
        {
            ShouldThrowOn(
                VALID_CONFIG
                " program:"
                " INC(42)",
                Constants::ErrorMessages::nonexistant_register
            );
        }

        TEST_METHOD(Errors_OutOfRangeInstruction)
        {
            ShouldThrowOn(
                VALID_CONFIG
                " program:"
                " JE(0,0,42)",
                Constants::ErrorMessages::instruction_out_of_range
            );
        }
    };
}