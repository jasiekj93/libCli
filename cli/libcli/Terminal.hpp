#pragma once

/**
 * @file Terminal.hpp
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
    class Terminal
    {
    public:
        using TemplatessBuffer = utils::Dictionary<templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~Terminal() {}

        virtual void receivedCharCallback(char) = 0;
        virtual void receivedStringCallback(const char*) = 0;
        
        virtual TemplatessBuffer & templates() = 0;

        virtual void putString(const char*) = 0;
        virtual size_t printf(const char*, ...) = 0;
        virtual void disableInput() = 0;
        virtual void enableInput() = 0;
        virtual bool isInputEnabled() = 0;
    };
}