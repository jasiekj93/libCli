#pragma once

#include <libCli/Template/Command.hpp>
#include <libCli/Model/Command.hpp>
#include <libCli/Utils/Dictionary.hpp>

namespace Cli::Internal
{
    class CommandVerifier
    {
    public:
        enum class Status
        {
            Ok,
            Unknown,
            NoMandatoryArguments,
            InvalidArgument,
            InvalidArgumentType,
            Help
        };

        Status Verify(const Model::Command &) const;

        auto & Templates() { return _buffer; }

    private:
        static Model::Argument _help;
        Utils::Dictionary<Template::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT> _buffer;
    };
}