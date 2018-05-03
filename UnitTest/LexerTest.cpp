#include "CppUnitTest.h"

#include "Processing\Lexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<typename SymbolType>
void ShouldResultIn(const std::string& symbol, const std::string& info_string)
{
    Processing::Lexer lexer{ "test", std::make_unique<std::stringstream>(symbol) };
    Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<SymbolType>());
    Assert::AreEqual(info_string, lexer.GetCurrentSymbol()->GetInfoString());
    lexer.ReadNextSymbol();
    Assert::IsTrue(lexer.IsEndOfFile());
}

template<typename SymbolType>
void ShouldResultIn(const std::string& symbol)
{
    ShouldResultIn<SymbolType>(symbol, symbol);
}

template<typename Fun>
void ShouldThrow(Fun fun, const std::string& str)
{
    try
    {
        fun();
        auto error = L"The function did not throw with input: " + std::wstring(str.begin(), str.end());
        Assert::Fail(error.data());
    }
    catch (...)
    {
    }
}

void ShouldNotLex(const std::string& str)
{
    ShouldThrow([str]()
    {
        Processing::Lexer lexer{ "test", std::make_unique<std::stringstream>(str) };
        while (!lexer.IsEndOfFile())
        {
            lexer.ReadNextSymbol();
        }
    }, str);
}

namespace UnitTest
{
    TEST_CLASS(LexerTest)
    {
        TEST_METHOD(Lexer_TrivialSymbols)
        {
            ShouldResultIn<Processing::Symbols::Number>("0420", "420");
            ShouldResultIn<Processing::Symbols::OpenParentheses>("(");
            ShouldResultIn<Processing::Symbols::CloseParentheses>(")");
            ShouldResultIn<Processing::Symbols::Colon>(":");
            ShouldResultIn<Processing::Symbols::Comma>(",");
            ShouldResultIn<Processing::Symbols::Dot>(".");
            ShouldResultIn<Processing::Symbols::InstructionName>("UPPERCASEWORD");
            ShouldResultIn<Processing::Symbols::Label>("lowercase_words");
        }

        TEST_METHOD(Lexer_RowNumber)
        {
            auto stream = std::make_unique<std::stringstream>();
            const size_t max = 20;
            for (size_t i = 0; i < max; ++i)
            {
                *stream << i << "\n";
            }
            Processing::Lexer lexer{"test",  std::move(stream)};
            for (size_t i = 0; i < max; ++i)
            {
                Assert::AreEqual(i + 1, lexer.GetLineNumber());
                lexer.ReadNextSymbol();
            }
        }
        TEST_METHOD(Lexer_MultipleSymbols)
        {
            using namespace Processing::Symbols;
            auto stream = std::make_unique<std::stringstream>("1label\n:2)(. 3\t\t\t\n\tNAME");
            Processing::Lexer lexer{ "test", std::move(stream) };

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Number>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Label>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Colon>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Number>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<CloseParentheses>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<OpenParentheses>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Dot>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<Number>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.GetCurrentSymbol()->IsA<InstructionName>());
            lexer.ReadNextSymbol();

            Assert::IsTrue(lexer.IsEndOfFile());
        }

        TEST_METHOD(Lexer_Errors)
        {
            ShouldNotLex("123;456");
            ShouldNotLex("asd{HELLO}WORLD");
            ShouldNotLex("12%");
            ShouldNotLex("\"WOW");
        }
    };
}
