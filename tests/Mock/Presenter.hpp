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
            UnknownCommand,
            NoMandatoryArguments,
            InvalidArgument,
            InvalidArgumentType,
            Help,
            Prompt
        };

        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const Cli::Template::Command &) override;
        void InvalidArgument(char argument, const Cli::Template::Command &) override;
        void InvalidArgumentType(char argument, const Cli::Template::Command &) override;
        void Help(const Cli::Template::Command &) override;
        void Prompt(bool) override;
        
        inline size_t PromptLength() override { return 5; }

        Operation operation = Operation::Idle;
    };
}