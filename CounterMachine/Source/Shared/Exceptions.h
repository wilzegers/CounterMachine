#pragma once

#include "BoostIncludes.h"
#include "Constants.h"
#include "Utility.h"

struct LocationInfo
{
    const char* parser_name;
    size_t line_number;

    LocationInfo(const char* parser_name, size_t line_number) :
        parser_name{ parser_name },
        line_number{ line_number }
    {
    }
};


class ExceptionStringBuilder
{
    std::string location_string;
    std::string exception_string;
    std::string full_string;

    static void BuildExceptionStringImpl(boost::format& /*temp_string*/) {}

    template<class Arg1, class... Args>
    static void BuildExceptionStringImpl(boost::format& temp_string, Arg1 arg1, Args... args)
    {
        BuildExceptionStringImpl(temp_string % arg1, args...);
    }

public:
    void BuildLocationString(const LocationInfo& location)
    {
        boost::format builder(Constants::ErrorMessages::message_suffix);
        builder % location.parser_name % location.line_number;
        location_string = builder.str();
    }


    template<class... Args>
    void BuildExceptionString(const char* raw_string, Args... args)
    {
        boost::format builder(raw_string);
        BuildExceptionStringImpl(builder, args...);
        exception_string = builder.str();
    }

    void Finalize()
    {
        full_string = exception_string + location_string;
    }

    const std::string& GetString() const
    {
        if (exception_string.size() == 0)
        {
            throw InternalError("ExceptionBuilder used  without exception string");
        }
        return full_string;
    }
};


class ExceptionWithLocation : public std::exception
{
    ExceptionStringBuilder string_builder;

public:
    template<class... Args>
    ExceptionWithLocation(LocationInfo location, const char* exception_string, Args... args)
    {
        string_builder.BuildExceptionString(exception_string, args...);
        string_builder.BuildLocationString(location);
        string_builder.Finalize();
    }


    const char* what() const override
    {
        return string_builder.GetString().c_str();
    }
};

class ExceptionNoLocation : public std::exception
{
    ExceptionStringBuilder string_builder;

public:
    template<class... Args>
    ExceptionNoLocation(const char* exception_string, Args... args)
    {
        string_builder.BuildExceptionString(exception_string, args...);
        string_builder.Finalize();
    }

    const char* what() const override
    {
        return string_builder.GetString().c_str();
    }
};
