#pragma once

#include "Exceptions.h"

#include "Processing/Lexer.h"

namespace Processing
{
    /// A különböző parserek őse.
    struct ParserBase
    {

        ///Konstruktor.
        /**
        * \param stream az elemző input-stream
        * \param name a parsert identifikáló név.
        */
        ParserBase(std::unique_ptr<std::istream>&& stream, const char* name) :
            lexer{ name, std::move(stream) },
            name{ name }
        {
        }

        /// Az olvasás jelenlegi helyének lekérése.
        /**
        * \return Az olvasás jelenlegi helye.
        */
        LocationInfo GetLocationInfo() const
        {
            return LocationInfo{ name, lexer.GetLineNumber() };
        }

        /// A jelenlegi szimbólum típusának ellenőrzése.
        /**
        * \tparam ExactSymbol az elvárt típus.
        */
        template<class ExactSymbol>
        bool CurrentSymbolIs() const
        {
            return !lexer.IsEndOfFile() && lexer.GetCurrentSymbol()->IsA<ExactSymbol>();
        }

        /// A jelenlegi szimbólum típusának ellenőrzése.
        /**
        * \tparam ExactSymbol az elvárt típus.
        */
        template<class ExactSymbol>
        void CurrentSymbolShouldBe() const
        {
            ShouldNotBeEOF();
            if (!CurrentSymbolIs<ExactSymbol>())
            {
                RaiseNotOfType<ExactSymbol>();
            }
        }

        void ShouldNotBeEOF() const
        {
            if (lexer.IsEndOfFile())
            {
                ThrowWithLocation(Constants::ErrorMessages::unexpected_eof);
            }
        }

        /// A jelenlegi szimbólum bizonyos típussá castolása ellenőrzéssel.
        /**
        * \tparam ExactSymbol az elvárt típus
        * \return Az átcastolt szimbólumra mutató pointer.
        */
        template<class ExactSymbol>
        ViewPtr<const ExactSymbol> SafelyGetSymbolAs() const
        {
            CurrentSymbolShouldBe<ExactSymbol>();
            return lexer.GetCurrentSymbol()->As<ExactSymbol>();
        }

        /// Hiba dobása az olvasás jelenlegi helyét is a hibába foglalva.
        /**
        * \tparam Args a hiba paramétereinek típusai
        * \param args a hiba paraméterei: első egy hibaüzenet-string, aztán annak a paramétereinek az értéke
        */
        template<class... Args>
        void ThrowWithLocation(Args... args) const
        {
            throw ExceptionWithLocation{ GetLocationInfo(), args... };
        }

        /// Váratlan szimbólumtípus jelzése. Nem tudjuk pontosan megmondani, milyet vártunk.
        void RaiseUnexpectedSymbol() const
        {
            const Symbol* unexpected = lexer.GetCurrentSymbol();
            ThrowWithLocation(Constants::ErrorMessages::unexpected_symbol,
                unexpected->GetTypeDescription(), unexpected->GetInfoString());
        }

        /// Váratlan szimbólumtípus jelzése. Meg tudjuk pontosan mondani, milyet vártunk.
        /**
        * \tparam ExpectedSymbolType a várt szimbólumtípus.
        */
        template<typename ExpectedSymbolType>
        void RaiseNotOfType() const
        {
            const Symbol* unexpected = lexer.GetCurrentSymbol();
            ThrowWithLocation(Constants::ErrorMessages::not_expected_symbol,
                unexpected->GetTypeDescription(), unexpected->GetInfoString(),
                ExpectedSymbolType::description);
        }

        /// Váratlan szimbólumérték jelzése.
        void RaiseUnknownSymbolValue() const
        {
            const Symbol* unexpected = lexer.GetCurrentSymbol();
            ThrowWithLocation(Constants::ErrorMessages::unknown_symbol_value,
                unexpected->GetTypeDescription(), unexpected->GetInfoString());
        }

    protected:

        Lexer lexer; ///< A lexikális elemző.

        const char* name; ///< A parser neve.
    };

}