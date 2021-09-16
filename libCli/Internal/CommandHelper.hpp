#pragma once

/**
 * @file CommandHelper.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libCli/Template/Command.hpp>
#include <libCli/IOutput.hpp>

namespace Cli::Internal
{
    class CommandHelper
    {
    public:
        CommandHelper(IOutput &);

        void DisplayHelp(const Template::Command &);

    protected:
        void _PrintUsage(const Template::Command &);
        void _PrintArgumentUsage(const Template::Command &);
        void _PrintCommandHelp(const Template::Command &);
        void _PrintArguments(const Template::Command &);
        void _PrintArgumentType(const Template::Argument &);
    
    private:
        IOutput &_output;
    };
}