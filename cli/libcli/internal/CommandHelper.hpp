#pragma once

/**
 * @file CommandHelper.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Command.hpp>
#include <libcli/Output.hpp>

namespace cli::internal
{
    class CommandHelper
    {
    public:
        CommandHelper(Output&);

        void DisplayHelp(const templates::Command&);

    protected:
        void _PrintUsage(const templates::Command&);
        void _PrintArgumentUsage(const templates::Command&);
        void _PrintCommandHelp(const templates::Command&);
        void _PrintArguments(const templates::Command&);
        void _PrintArgumentType(const templates::Argument&);
    
    private:
        Output& _output;
    };
}