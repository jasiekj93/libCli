#pragma once

/**
 * @file IPresenter.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/Template/Command.hpp>
#include <libcli/IOutput.hpp>

namespace cli::Internal
{
    class IPresenter
    {
    public:
        virtual ~IPresenter() {}

        virtual void UnknownCommand(const char *) = 0;
        virtual void NoMandatoryArguments(char argument, const Template::Command &) = 0;
        virtual void InvalidArgument(char argument, const Template::Command &) = 0;
        virtual void InvalidArgumentType(char argument, const Template::Command &) = 0;
        virtual void Help(const Template::Command &) = 0;
        virtual void Prompt(bool addNewLine = true) = 0;
        virtual size_t PromptLength() = 0;
    };
}