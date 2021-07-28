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
        char *_FindWord(char *);
        char *_FindEndOfWord(char *);
        char *_FindArgument(char *);
        void _Clear();

    private:
        char _data[Configuration::MAX_COMMAND_LENGTH + 1];
        char *_name;
    };
}