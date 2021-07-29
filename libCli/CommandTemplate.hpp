#pragma once

#include <libCli/Configuration.hpp>
#include <libCli/ArgumentTemplate.hpp>
#include <libCli/Utils/Buffer.hpp>
#include <utility>

namespace Cli
{
    class CommandTemplate
    {
    public:
        CommandTemplate();
        CommandTemplate(const char *name, const char *help = nullptr);
        CommandTemplate(const char *name, std::initializer_list<ArgumentTemplate>);
        CommandTemplate(const char *name, const char *help, std::initializer_list<ArgumentTemplate>);

        inline auto Name() { return _name; }
        inline auto Help() { return _help; }
        inline auto Arguments() { return _arguments; }

    private:
        char _name[Configuration::MAX_COMMAND_NAME + 1];
        char _help[Configuration::MAX_COMMAND_HELP_LENGTH + 1];
        Utils::Buffer<ArgumentTemplate, Configuration::MAX_ARGUMENT_COUNT> _arguments;
    };
}