#pragma once

/**
 * @file Terminal.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <etl/map.h>
#include <etl/string.h>

#include <libcli/templates/Command.hpp>
#include <libcli/Configuration.hpp>
#include <libcli/OutputController.hpp>

namespace cli
{
    class Terminal : public OutputController
    {
    public:
        using TemplatesBuffer = etl::map<etl::string_view, templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~Terminal() {}

        virtual void receivedCharCallback(char) = 0;
        virtual void receivedStringCallback(const char*) = 0;
        
        virtual TemplatesBuffer& templates() = 0;

        virtual OutputController& operator<<(char) override = 0;
        virtual OutputController& operator<<(etl::string_view) override = 0;
        virtual OutputController& operator<<(const formatspec::Base&) override = 0;

        virtual void disableInput() = 0;
        virtual void enableInput() = 0;
        virtual bool isInputEnabled() = 0;
    };
}