#pragma once

/**
 * @file Command.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libCli/Configuration.hpp>
#include <libCli/Utils/DictionaryChar.hpp>
#include <libCli/Model/Argument.hpp>

namespace Cli::Model
{
    class Command
    {
    public:
        Command();
        Command(const char *);

        bool IsNull() const;
        const char * GetName() const;

        inline const auto & Arguments() const { return _arguments; }

    protected:
        bool _FindName();
        bool _FindArguments();
        unsigned int _HyphenCount(const char *) const;

    private:
        char _data[Configuration::MAX_COMMAND_LENGTH + 1];
        char *_name;
        Utils::DictionaryChar<Argument, Configuration::MAX_ARGUMENT_COUNT> _arguments;
    };
}