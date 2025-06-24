#pragma once

/**
 * @file Presenter.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/templates/Command.hpp>

namespace cli::internal
{
    class Presenter
    {
    public:
        virtual ~Presenter() = default;

        virtual void unknownCommand(etl::string_view) = 0;
        virtual void noMandatoryArguments(char argument, const templates::Command&) = 0;
        virtual void invalidArgument(char argument, const templates::Command&) = 0;
        virtual void invalidArgumentType(char argument, const templates::Command&) = 0;
        virtual void help(const templates::Command&) = 0;
        virtual void prompt(bool addNewLine = true) = 0;
        virtual size_t promptLength() = 0;
    };
}