#pragma once

#include "BoostIncludes.h"
#include "Constants.h"
#include "Exceptions.h"

/// Belső hibát jelző kivétel
struct InternalError : public std::exception
{
    /// Konstruktor a hibaüzenet szövegével
    /**
    * \param message a hiba leírása.
    */
    InternalError(const std::string message) : message{ "Internal Error: " + message }
    {
    }

private:
    std::string message; ///< A hiba leírása.
};


/// A hibaüzenetért felelős szövegsort jelképező osztály.
struct LocationInfo
{
    const char* parser_name; ///< a hibaforrás parser neve.
    size_t line_number; ///< a hibaforrás sora.
};

/// Hibaüzenetet felépítő osztály.
struct ExceptionStringBuilder
{
    /// A helyet leíró szöveg felépítése.
    /**
    * \param location a helyet leíró objektum.
    */
    void BuildLocationString(const LocationInfo& location)
    {
        boost::format builder(Constants::ErrorMessages::message_suffix);
        builder % location.parser_name % location.line_number;
        location_string = builder.str();
    }

    /// A hibát leíró szöveg felépítése.
    /**
    * \param raw_string a hibát leíró szövegminta.
    * \param args a hibaleíró szöveg felépítéséhez használt adatok.
    */
    template<class... Args>
    void BuildExceptionString(const char* raw_string, Args... args)
    {
        boost::format builder(raw_string);
        BuildExceptionStringImpl(builder, args...);
        exception_string = builder.str();
    }

    /// A hibaüzenet véglegesítése.
    void Finalize()
    {
        full_string = exception_string + location_string;
    }

    /// A hibaüzenet lekérdezése.
    /**
    * \return a hibaüzenet szövege.
    */
    const std::string& GetString() const
    {
        if (exception_string.size() == 0)
        {
            throw InternalError("ExceptionBuilder used without exception string");
        }
        return full_string;
    }

private:

    /// A hibaleíró-szöveg felépítését rekurzívan megtevő függvény.
    /**
    * \param temp_string a felépítésben lévő format_string.
    * \param arg1 a jelenleg feldolgozás alatt álló argumentum.
    * \param args a maradék argumentumok.
    */
    template<class Arg1, class... Args>
    static void BuildExceptionStringImpl(boost::format& temp_string, Arg1 arg1, Args... args)
    {
        BuildExceptionStringImpl(temp_string % arg1, args...);
    }

    /// A hibaleíró-szöveg felépítés rekurziójának alapesete.
    static void BuildExceptionStringImpl(boost::format& /*temp_string*/) {}


    std::string location_string; ///< A helyet leíró szövegrész.
    std::string exception_string; ///< A hibát leíró szövegrész.
    std::string full_string; ///< A felépített hibaüzenet.
};

/// Helyleírással rendelkező kivétel osztály.
struct ExceptionWithLocation : public std::exception
{
    /// Kivételt felépítő konstruktor.
    /**
    * \param location a hiba helye.
    * \param exception_string a hibát leíró szövegminta.
    * \param args a hibaüzenet felépítéséhez használt argumentumok.
    */
    template<class... Args>
    ExceptionWithLocation(LocationInfo location, const char* exception_string, Args... args)
    {
        string_builder.BuildExceptionString(exception_string, args...);
        string_builder.BuildLocationString(location);
        string_builder.Finalize();
    }

    /// A kivétel szövegének lekérése
    /**
    * \return a kivétel szövege.
    */
    const char* what() const throw() override
    {
        return string_builder.GetString().c_str();
    }

private:

    ExceptionStringBuilder string_builder; ///< A hibaüzenetet felépítő objektum.
};

/// Helyleírással nem rendelkező kivétel osztály.
struct ExceptionNoLocation : public std::exception
{
    /// Kivételt felépítő konstruktor.
    /**
    * \param exception_string a hibát leíró szövegminta.
    * \param args a hibaüzenet felépítéséhez használt argumentumok.
    */
    template<class... Args>
    ExceptionNoLocation(const char* exception_string, Args... args)
    {
        string_builder.BuildExceptionString(exception_string, args...);
        string_builder.Finalize();
    }

    /// A kivétel szövegének lekérése
    /**
    * \return a kivétel szövege.
    */
    const char* what() const throw() override
    {
        return string_builder.GetString().c_str();
    }

private:
    ExceptionStringBuilder string_builder; ///< A hibaüzenetet felépítő objektum.
};
