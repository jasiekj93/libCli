#pragma once

#include <libCli/Internal/IPresenter.hpp>

namespace Mock
{
    class Presenter : public Cli::Internal::IPresenter
    {
    public:
        enum class Operation
        {
            Idle,
            InvalidCommandFormat,
            UnknownCommand,
            NoMandatoryArguments,
            InvalidArgument,
            InvalidArgumentType,
            Help,
            Prompt
        };

        void InvalidCommandFormat() override;
        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const Cli::Template::Command &) override;
        void InvalidArgument(char argument, const Cli::Template::Command &) override;
        void InvalidArgumentType(char argument, const Cli::Template::Command &) override;
        void Help(const Cli::Template::Command &) override;
        void Prompt() override;

        Operation operation = Operation::Idle;
    };
}