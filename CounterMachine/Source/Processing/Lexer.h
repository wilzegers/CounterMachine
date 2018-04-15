#pragma once

#include <fstream>
#include "Utility.h"

#include "Processing/Symbol.h"

namespace Processing
{
    ///< A lexikális elemzést végrehajtó osztály.
    struct Lexer
    {
        /// Konstruktor.
        /**
        * \param name a lexer szövegének a forrásának a neve.
        * \param stream az elemzendő szövegfolyam.
        */
        Lexer(const char* name, std::unique_ptr<std::istream>&& stream);

        /// Ismeretlen karaktert jelző kivétel.
        struct UnexpectedCharException : public std::exception
        {
            /// Konstruktor.
            /**
            * \param name a hibás szöveg forrásának a neve.
            * \param line_number a hibás szöveg sora.
            * \param c a hibás karakter.
            */
            UnexpectedCharException(const char* name, size_t line_number, char c);

            /// A kivétel szövegének lekérése.
            /**
            * \return a kivétel szövege.
            */
            virtual const char* what() const override { return message.c_str(); }

        private:

            std::string message; ///< A kivétel szövege.
        };

        /// A következő szimbólumra állás.
        void ReadNextSymbol();

        /// A jelenlegi szimbólum nézetének lekérése. Ha állunk a következő szimbólumra, invalidálódik.
        /**
        * \return nézet a jelenlegi szimbólumra.
        */
        const ViewPtr<Symbol> GetCurrentSymbol() const { return MakeView(current); }

        /// Annak a lekérése, hogy a fájl végére értünk-e.
        /**
        * \return igaz, ha a fájl végén vagyunk.
        */
        bool IsEndOfFile() const { return eof; }

        /// A jelenlegi sorszám lekérése.
        /**
        * \return a jelenlegi sorszám.
        */
        size_t GetLineNumber() const;

    private:

        /// Címke beolvasása.
        void ReadLabel();

        /// Utasításnév beolvasása.
        void ReadInstructionName();

        /// Szám beolvasása.
        void ReadNumber();

        /// Egyedi karakter szimbólum beolvasása.
        void ReadCharSymbol();

        /// A fehér szóközök eldobása.
        void EatSpace();

        /// A megjegyzett sorszám frissítése, amennyiben sor végén vagyunk.
        void CheckForNewLine();

        /// Szöveg beolvasása addig, amíg a predikátum teljesül.
        /**
        * \param predicate az ellenőrzendő predikátum.
        * \return az így beolvasott szöveg.
        */
        template<class Pred>
        std::string GetWhile(Pred predicate)
        {
            std::stringstream ss;
            while (predicate(stream->peek()))
            {
                CheckForNewLine();
                ss << static_cast<char>(stream->get());
            }
            return ss.str();
        }

        std::unique_ptr<Symbol> current{ nullptr }; ///< A jelenlegi szimbólum.
        std::unique_ptr<std::istream> stream; ///< Az elemzendő szövegfolyam.
        bool eof{ true }; ///< Fájl vége logikai változó.
        size_t line_number{ 1 }; ///< A jelenlegi sor száma.
        const char* name; ///< Az elemzendő szövegforrás neve.
    };

}