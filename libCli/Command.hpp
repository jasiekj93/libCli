#pragma once

#include <libCli/Configuration.hpp>
#include <libCli/Utils/Buffer.hpp>
#include <libCli/Argument.hpp>

namespace Cli
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
        Utils::Buffer<Argument, Configuration::MAX_ARGUMENT_COUNT> _arguments;
    };
}