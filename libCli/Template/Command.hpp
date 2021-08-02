#pragma once

/**
 * @file Command.hpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <libCli/Configuration.hpp>
#include <libCli/Template/Argument.hpp>
#include <libCli/Utils/DictionaryChar.hpp>
#include <utility>

namespace Cli::Template
{
    class Command
    {
    public:
        Command();
        Command(const char *name, const char *help = nullptr);
        Command(const char *name, std::initializer_list<Argument>);
        Command(const char *name, const char *help, std::initializer_list<Argument>);

        inline auto Name() const { return _name; }
        inline auto Help() const { return _help; }
        inline auto Arguments() const { return _arguments; }

        bool operator==(const Command &) const;
        bool operator!=(const Command &) const;

    private:
        char _name[Configuration::MAX_COMMAND_NAME + 1];
        char _help[Configuration::MAX_COMMAND_HELP_LENGTH + 1];
        Utils::DictionaryChar<Argument, Configuration::MAX_ARGUMENT_COUNT> _arguments;
    };
}