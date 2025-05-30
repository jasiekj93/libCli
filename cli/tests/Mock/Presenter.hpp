#pragma once

#include <libcli/Internal/IPresenter.hpp>

namespace Mock
{
    class Presenter : public cli::Internal::IPresenter
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
        void NoMandatoryArguments(char argument, const cli::Template::Command &) override;
        void InvalidArgument(char argument, const cli::Template::Command &) override;
        void InvalidArgumentType(char argument, const cli::Template::Command &) override;
        void Help(const cli::Template::Command &) override;
        void Prompt(bool) override;
        
        inline size_t PromptLength() override { return 5; }

        Operation operation = Operation::Idle;
    };
}