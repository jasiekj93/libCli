#pragma once

namespace cli::language
{
    struct Dictionary
    {
        const char* unknownCommand;
        const char* noMandatoryArguments;
        const char* invalidArgument;
        const char* invalidArgumentType;

        const char* usage;
        const char* decimal;
        const char* hexadecimal;
        const char* doubleStr;
        const char* empty;
        const char* string;
    };

    static constexpr Dictionary polish = {
        .unknownCommand = "nie znaleziono polecenia",
        .noMandatoryArguments = "brak wymaganych argumentow",
        .invalidArgument = "nieprawidlowy argument",
        .invalidArgumentType = "nieprawidlowy typ argumentu",

        .usage = "zastosowanie",
        .decimal = "calkowity",
        .hexadecimal = "szesnastkowy",
        .doubleStr = "zmiennoprzecinkowy",
        .empty = " ",
        .string = "ciag znakow",
    };

    static constexpr Dictionary english = {
        .unknownCommand = "command not found",
        .noMandatoryArguments = "missing mandatory arguments",
        .invalidArgument = "invalid argument",
        .invalidArgumentType = "invalid argument type",

        .usage = "usage",
        .decimal = "decimal",
        .hexadecimal = "hexadecimal",
        .doubleStr = "double",
        .empty = " ",
        .string = "string",
    };
}