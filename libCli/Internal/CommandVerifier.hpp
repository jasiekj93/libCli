#pragma once

/**
 * @file CommandVerifier.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

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
        const char * Find(const char *);
        

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