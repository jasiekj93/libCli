#pragma once

#include <libCli/Model/Command.hpp>
#include <libCli/IOutput.hpp>

namespace Cli::Internal
{
    class Presenter
    {
    public:
        Presenter(IOutput &);

        void InvalidCommandFormat();
        void UnknownCommand(const char *);
        void NoMandatoryArguments(const char *);
        void InvalidArgument(const char *);
        void InvalidArgumentType(const char *);
        void Help(const Model::Command &);

    private:
        IOutput &_output;
    };
}