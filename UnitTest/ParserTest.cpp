#include "CppUnitTest.h"

#include <sstream>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define private public
#include "Processing\Parser.h"
#include "Processing\Parser.cpp"
#undef private

typedef void (Processing::Parser::*ParseFun)();

void ShouldParse(std::string str, ParseFun fun)
{
    Processing::Parser p{ std::make_unique<std::stringstream>(str) };
    (p.*fun)();
}

void ShouldNotParse(std::string str, ParseFun fun)
{
    try
    {
        Processing::Parser p{ std::make_unique<std::stringstream>(str) };
        (p.*fun)();
    }
    catch (...)
    {
        return;
    }
    Assert::Fail(L"Parse should not have been successful.");
}

#define TEST_PARSE_ARGS(...) Assert::IsTrue(Processing::Parser{std::make_unique<std::stringstream>("(" #__VA_ARGS__ ")")}.ParseArguments() == std::vector<size_t>{__VA_ARGS__})

namespace  UnitTest
{
    TEST_CLASS(ParserTest)
    {
        TEST_METHOD(Parser_Configuration)
        {
            ShouldParse(
                "register_number: 1"
                "output: 0"
                "inits :"
                "0 : 0",
            &Processing::Parser::ParseConfiguration);

            ShouldParse(
                "register_number: 4"
                "output: 1"
                "inits :"
                "0 : 0"
                "1 : 1"
                "2 : 0"
                "3 : input",
            &Processing::Parser::ParseConfiguration);

            ShouldParse(
                "register_number: 2"
                "output: 1"
                "inits :"
                "0 : input"
                "1 : input",
            &Processing::Parser::ParseConfiguration);

            ShouldNotParse(
                "register_number: "
                "output: 1",
            &Processing::Parser::ParseConfiguration);

            ShouldNotParse(
                "register_number: 1"
                "output: 1"
                "HALT()",
            &Processing::Parser::ParseConfiguration);
        }

        TEST_METHOD(Parser_Arguments)
        {
            TEST_PARSE_ARGS();
            TEST_PARSE_ARGS(1, 2);
            TEST_PARSE_ARGS(123, 456, 789, 12, 345, 678);
            TEST_PARSE_ARGS(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }

        TEST_METHOD(Parser_Instruction)
        {
            ShouldParse(
                "HALT()",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "INC(123123)",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "DEC(2)",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "COPY(0, 0)",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "CLR(9898)",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "JZ(123, 456)",
            &Processing::Parser::ParseInstruction);

            ShouldParse(
                "JE(987, 654, 321)",
            &Processing::Parser::ParseInstruction);

            ShouldNotParse(
                "JE(987, , 321)",
            &Processing::Parser::ParseInstruction);

            ShouldNotParse(
                "JE(987, 321)",
            &Processing::Parser::ParseInstruction);

            ShouldNotParse(
                "ALMAFA(987, , 321)",
            &Processing::Parser::ParseInstruction);
        }

        TEST_METHOD(Parser_ParsingWritingAreInverses)
        {
            const auto program_code =
                "register_number:2\n"
                "output:1\n"
                "inits:\n"
                "0:1\n"
                "1:0\n"
                "program:\n"
                "0.INC(0)\n"
                "1.DEC(0)\n"
                "2.CLR(0)\n"
                "3.JZ(0,4)\n"
                "4.JE(0,0,5)\n"
                "5.COPY(1,0)\n"
                "HALT()\n";
            auto stream = std::make_unique<std::stringstream>(program_code);
            Processing::Parser p{ std::move(stream) };
            p.Parse();
            std::stringstream ss;

            ss << p.GetResultComputation();
            auto original = ss.str();

            Processing::Parser p2{ std::make_unique<std::stringstream>(ss.str()) };
            p2.Parse();
            ss = std::stringstream{};
            ss << p2.GetResultComputation();

            Assert::IsTrue(ss.str() == original);
        }
    };
}