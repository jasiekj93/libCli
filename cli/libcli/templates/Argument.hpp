#pragma once

/**
 * @file Argument.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/Configuration.hpp>
#include <libcli/model/Argument.hpp>

namespace cli::templates
{
    class Argument
    {
    public:
        Argument();
        Argument(char, 
            model::Argument::Type, 
            bool isMandatory, 
            const char * help = nullptr);

        inline auto getName() const { return name; }        
        inline auto getType() const { return type; }
        inline auto isMandatory() const { return mandatoryValue; }
        inline auto help() const { return helpMessage; }        

        bool operator==(const Argument &) const;
        bool operator!=(const Argument &) const;

    private:
        char name;
        model::Argument::Type type;
        bool mandatoryValue;
        char helpMessage[Configuration::MAX_ARGUMENT_HELP_LENGTH];
    };
}