#pragma once

/// A szövegkonstansok típusa.
using ConstStr = const char[];

namespace Constants
{
    namespace Locations
    {
        static constexpr ConstStr program       = "program code";
        static constexpr ConstStr parameters    = "input parameters";
    }

    namespace Labels
    {
        static constexpr ConstStr reg_number    = "register_number";
        static constexpr ConstStr output_reg    = "output";
        static constexpr ConstStr reg_init      = "inits";
        static constexpr ConstStr progam        = "program";
        static constexpr ConstStr input         = "input";
    }

    namespace Instructions
    {
        static constexpr ConstStr clear         = "CLR";
        static constexpr ConstStr increase      = "INC";
        static constexpr ConstStr decrease      = "DEC";
        static constexpr ConstStr copy          = "COPY";
        static constexpr ConstStr jump_if_zero  = "JZ";
        static constexpr ConstStr jump_if_equal = "JE";
        static constexpr ConstStr halt          = "HALT";
    }

    namespace ErrorMessages
    {
        static constexpr ConstStr nonexistant_file          = "file not found";
        static constexpr ConstStr unexpected_eof            = "more characters expected after the end";
        static constexpr ConstStr unsupported_character     = "unsupported character \'%1%\' found";
        static constexpr ConstStr unexpected_symbol         = "unexpected %1% \'%2%\' found";
        static constexpr ConstStr not_expected_symbol       = "unexpected %1% \'%2%\' found (expected: %3%)";
        static constexpr ConstStr unknown_symbol_value      = "unknown %1% \'%2%\' found";
        static constexpr ConstStr argument_error            = "wrong number of arguments for instruction \'%1%\' (expected: %2%, received: %3%)";
        static constexpr ConstStr plus_input_register       = "non-input register \'%1%\' given initial value";
        static constexpr ConstStr missing_input_register    = "input register \'%1%\' missing initial value";
        static constexpr ConstStr multiple_register_def     = "register \'%1\' defined multiple times";
        static constexpr ConstStr input_reg_count_mismatch  = "the input value count (%1%) does not match the input register count (%2%)";
        static constexpr ConstStr input_reg_name_mismatch   = "the input register \'%1%\' does not exist";

        static constexpr ConstStr nonexistant_register      = "trying to access nonexistant register no. %1%.";
        static constexpr ConstStr instruction_out_of_range  = "trying to run nonexistant instruction no. %1%.";
        static constexpr ConstStr decrease_zero             = "trying to decrease value of register \'%1%\' but it is already 0";

        static constexpr ConstStr message_suffix            = " - in the %1%, line %2%.";
    }

    namespace Symbols
    {
        static constexpr ConstStr label                 = "label (lower case word)";
        static constexpr ConstStr instruction_name      = "instruction (upper case word)";
        static constexpr ConstStr number                = "number";
        static constexpr ConstStr colon                 = "colon";
        static constexpr ConstStr dot                   = "dot";
        static constexpr ConstStr comma                 = "comma";
        static constexpr ConstStr open_parentheses      = "open parentheses";
        static constexpr ConstStr closed_parentheses    = "closed parentheses";
    }
}
