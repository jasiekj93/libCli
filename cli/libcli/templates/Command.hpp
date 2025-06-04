#pragma once

/**
 * @file Command.hpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <utility>

#include <etl/string.h>
#include <etl/map.h>

#include <libcli/Configuration.hpp>
#include <libcli/templates/Argument.hpp>

namespace cli::templates
{
    class Command
    {
    public:
        using Name = etl::string<Configuration::MAX_COMMAND_NAME>;
        using Help = etl::string<Configuration::MAX_COMMAND_HELP_LENGTH>;
        using Arguments = etl::map<char, Argument, Configuration::MAX_ARGUMENT_COUNT>;

        Command();
        Command(etl::string_view name, const Arguments&);
        Command(etl::string_view name, etl::string_view help = "", const Arguments& = {});

        inline auto& getName() const { return _name; }
        inline auto& getHelp() const { return _help; }
        inline auto& getArguments() const { return _arguments; }

        bool operator==(const Command&) const;

    private:
        Name _name;
        Help _help;
        Arguments _arguments;
    };
}