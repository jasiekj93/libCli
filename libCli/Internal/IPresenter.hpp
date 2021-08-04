#pragma once

/**
 * @file IPresenter.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libCli/Template/Command.hpp>
#include <libCli/IOutput.hpp>

namespace Cli::Internal
{
    class IPresenter
    {
    public:
        virtual ~IPresenter() {}

        virtual void InvalidCommandFormat() = 0;
        virtual void UnknownCommand(const char *) = 0;
        virtual void NoMandatoryArguments(char argument, const Template::Command &) = 0;
        virtual void InvalidArgument(char argument, const Template::Command &) = 0;
        virtual void InvalidArgumentType(char argument, const Template::Command &) = 0;
        virtual void Help(const Template::Command &) = 0;
        virtual void Prompt() = 0;
    };
}