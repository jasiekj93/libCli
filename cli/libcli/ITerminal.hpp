#pragma once

/**
 * @file ITerminal.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/Utils/Dictionary.hpp>
#include <libcli/Template/Command.hpp>
#include <libcli/Configuration.hpp>

namespace cli
{
    class ITerminal
    {
    public:
        using TemplatesBuffer = Utils::Dictionary<Template::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~ITerminal() {}

        virtual void ReceivedCharCallback(char) = 0;
        virtual void ReceivedStringCallback(const char *) = 0;
        
        virtual TemplatesBuffer & Templates() = 0;

        virtual void PutString(const char *) = 0;
        virtual size_t Printf(const char *, ...) = 0;
        virtual void DisableInput() = 0;
        virtual void EnableInput() = 0;
        virtual bool IsInputEnabled() = 0;
    };
}