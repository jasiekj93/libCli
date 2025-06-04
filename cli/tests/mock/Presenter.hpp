#pragma once

#include <libcli/internal/Presenter.hpp>

namespace mock
{
    class Presenter : public cli::internal::Presenter
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

        void unknownCommand(etl::string_view) override;
        void noMandatoryArguments(char argument, const cli::templates::Command&) override;
        void invalidArgument(char argument, const cli::templates::Command&) override;
        void invalidArgumentType(char argument, const cli::templates::Command&) override;
        void help(const cli::templates::Command&) override;
        void prompt(bool) override;
        
        inline size_t promptLength() override { return 5; }

        Operation operation = Operation::Idle;
    };
}