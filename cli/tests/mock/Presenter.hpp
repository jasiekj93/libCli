#pragma once

#include <libcli/internal/IPresenter.hpp>

namespace mock
{
    class Presenter : public cli::internal::IPresenter
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
        void NoMandatoryArguments(char argument, const cli::templates::Command &) override;
        void InvalidArgument(char argument, const cli::templates::Command &) override;
        void InvalidArgumentType(char argument, const cli::templates::Command &) override;
        void Help(const cli::templates::Command &) override;
        void Prompt(bool) override;
        
        inline size_t PromptLength() override { return 5; }

        Operation operation = Operation::Idle;
    };
}