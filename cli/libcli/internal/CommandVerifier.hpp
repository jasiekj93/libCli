#pragma once

/**
 * @file CommandVerifier.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <etl/map.h>
#include <etl/string.h>

#include <libcli/templates/Command.hpp>
#include <libcli/model/Command.hpp>
#include <libcli/internal/Presenter.hpp>

namespace cli::internal
{
    class CommandVerifier
    {
    public:
        using Templates = etl::map<etl::string_view, templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        CommandVerifier(Presenter&);

        bool verify(const model::Command&);
        etl::string_view find(etl::string_view);
        
        auto& templates() { return buffer; }

    protected:
        bool checkMandatoryArguments(const model::Command&);
        bool checkOptionalArguments(const model::Command&);

    private:
        static model::Argument help;

        Presenter& presenter;
        Templates buffer;
    };
}