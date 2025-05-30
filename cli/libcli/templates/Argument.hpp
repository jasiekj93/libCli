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

        inline auto Name() const { return _name; }        
        inline auto GetType() const { return _type; }
        inline auto IsMandatory() const { return _isMandatory; }
        inline auto Help() const { return _help; }        

        bool operator==(const Argument &) const;
        bool operator!=(const Argument &) const;

    private:
        char _name;
        model::Argument::Type _type;
        bool _isMandatory;
        char _help[Configuration::MAX_ARGUMENT_HELP_LENGTH];
    };
}