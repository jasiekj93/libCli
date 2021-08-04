#pragma once

/**
 * @file ITerminal.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/Dictionary.hpp>
#include <libCli/Template/Command.hpp>
#include <libCli/Configuration.hpp>

namespace Cli
{
    class ITerminal
    {
    public:
        using TemplatesBuffer = Utils::Dictionary<Template::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~ITerminal() {}

        virtual void ReceivedCharCallback(char) = 0;
        virtual void ReceivedStringCallback(const char *) = 0;
        
        virtual TemplatesBuffer & Templates() = 0;
    };
}