#pragma once

/**
 * @file CommandVerifier.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Command.hpp>
#include <libcli/model/Command.hpp>
#include <libcli/utils/Dictionary.hpp>
#include <libcli/internal/Presenter.hpp>

namespace cli::internal
{
    class CommandVerifier
    {
    public:
        CommandVerifier(Presenter&);

        bool Verify(const model::Command&);
        const char* Find(const char*);
        

        auto& templates() { return _buffer; }

    protected:
        bool _CheckMandatoryArguments(const model::Command&);
        bool _CheckOptionalArguments(const model::Command&);

    private:
        static model::Argument _help;

        Presenter &_presenter;
        utils::Dictionary<templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT> _buffer;
    };
}