#pragma once

/**
 * @file CommandHelper.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Command.hpp>
#include <libcli/IOStream.hpp>
#include <libcli/Language.hpp>

namespace cli::internal
{
    class CommandHelper
    {
    public:
        CommandHelper(OutputStream&, language::Dictionary = language::english);

        void displayHelp(const templates::Command&);

    protected:
        void printUsage(const templates::Command&);
        void printArgumentUsage(const templates::Command&);
        void printCommandHelp(const templates::Command&);
        void printArguments(const templates::Command&);
        void printArgumentType(const templates::Argument&);
    
    private:
        OutputStream& output;
        language::Dictionary dictionary;
    };
}