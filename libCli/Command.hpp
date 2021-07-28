#pragma once

#include <libCli/Configuration.hpp>

namespace Cli
{
    class Command
    {
    public:
        Command();
        Command(const char *);

        bool IsNull() const;
        const char * GetName() const;
        size_t ArgumentCount() const;

    protected:
        void _Clear();

    private:
        char _data[Configuration::MAX_COMMAND_LENGTH + 1];
        char *_name;
    };
}