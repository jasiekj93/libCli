#pragma once

/**
 * @file Factory.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libCli/ITerminal.hpp>
#include <libCli/ICommandObserver.hpp>
#include <libCli/IOutput.hpp>

namespace Cli::Factory
{
    ITerminal * CreateNewTerminal(IOutput &, 
        ICommandObserver &, 
        size_t depth = 5, 
        const char *userName = nullptr);
}