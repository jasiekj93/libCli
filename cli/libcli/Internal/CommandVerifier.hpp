#pragma once

/**
 * @file CommandVerifier.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/Template/Command.hpp>
#include <libcli/Model/Command.hpp>
#include <libcli/Utils/Dictionary.hpp>
#include <libcli/Internal/IPresenter.hpp>

namespace cli::Internal
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