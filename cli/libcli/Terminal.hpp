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
#include <libcli/IOStream.hpp>

namespace cli
{
    class Terminal : public OutputStream
    {
    public:
        using TemplatesBuffer = etl::map<etl::string_view, templates::Command, Configuration::MAX_COMMAND_TEMPLATES_COUNT>;

        virtual ~Terminal() {}

        virtual void receivedCharCallback(char) = 0;
        virtual void receivedStringCallback(const char*) = 0;
        
        virtual TemplatesBuffer& templates() = 0;

        virtual void disableInput() = 0;
        virtual void enableInput() = 0;
        virtual bool isInputEnabled() = 0;

    protected:
        virtual void write(char c) override = 0;
        virtual void write(etl::string_view) override = 0;
        virtual void flush() override = 0;
    };
}