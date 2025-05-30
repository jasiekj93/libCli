#pragma once

/**
 * @file ITerminal.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/utils/Dictionary.hpp>
#include <libcli/templates/Command.hpp>
#include <libcli/Configuration.hpp>

namespace cli
{
    class ITerminal
    {
    public:
        using templatessBuffer = utils::Dictionary<templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~ITerminal() {}

        virtual void ReceivedCharCallback(char) = 0;
        virtual void ReceivedStringCallback(const char *) = 0;
        
        virtual templatessBuffer & templatess() = 0;

        virtual void PutString(const char *) = 0;
        virtual size_t Printf(const char *, ...) = 0;
        virtual void DisableInput() = 0;
        virtual void EnableInput() = 0;
        virtual bool IsInputEnabled() = 0;
    };
}