#pragma once

#include <libCli/Template/Command.hpp>
#include <libCli/Model/Command.hpp>
#include <libCli/Utils/Dictionary.hpp>
#include <libCli/Internal/IPresenter.hpp>

namespace Cli::Internal
{
    class CommandVerifier
    {
    public:
        CommandVerifier(IPresenter &);

        bool Verify(const Model::Command &);

        auto & Templates() { return _buffer; }

    protected:
        bool _CheckMandatoryArguments(const Model::Command &);
        bool _CheckOptionalArguments(const Model::Command &);

    private:
        static Model::Argument _help;

        IPresenter &_presenter;
        Utils::Dictionary<Template::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT> _buffer;
    };
}