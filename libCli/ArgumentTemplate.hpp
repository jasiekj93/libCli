#pragma once

/**
 * @file ArgumentTemplate.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Argument.hpp>
#include <libCli/Configuration.hpp>

namespace Cli
{
    class ArgumentTemplate
    {
    public:
        ArgumentTemplate();
        ArgumentTemplate(char, 
            Argument::Type, 
            bool, 
            const char * = nullptr);

        inline auto Name() const { return _name; }        
        inline auto Type() const { return _type; }
        inline auto IsMandatory() const { return _isMandatory; }
        inline auto Help() const { return _help; }        

    private:
        char _name;
        Argument::Type _type;
        bool _isMandatory;
        char _help[Configuration::MAX_ARGUMENT_HELP_LENGTH];
    };
}