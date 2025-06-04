#pragma once

/**
 * @file Argument.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/Configuration.hpp>
#include <libcli/model/Argument.hpp>

namespace cli::templates
{
    class Argument
    {
    public:
        Argument();
        Argument(model::Argument::Type, 
            bool isMandatory, 
            etl::string_view help = "");

        inline auto getType() const { return type; }
        inline auto isMandatory() const { return mandatoryValue; }
        inline auto getHelp() const { return helpMessage; }        

        bool operator==(const Argument&) const;
        bool operator!=(const Argument&) const;

    private:
        model::Argument::Type type;
        bool mandatoryValue;
        etl::string<Configuration::MAX_ARGUMENT_HELP_LENGTH> helpMessage;
    };
}