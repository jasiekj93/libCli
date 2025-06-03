#pragma once

/**
 * @file Presenter.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Command.hpp>

namespace cli::internal
{
    class Presenter
    {
    public:
        virtual ~Presenter() {}

        virtual void UnknownCommand(const char *) = 0;
        virtual void NoMandatoryArguments(char argument, const templates::Command&) = 0;
        virtual void InvalidArgument(char argument, const templates::Command&) = 0;
        virtual void InvalidArgumentType(char argument, const templates::Command&) = 0;
        virtual void Help(const templates::Command&) = 0;
        virtual void Prompt(bool addNewLine = true) = 0;
        virtual size_t PromptLength() = 0;
    };
}