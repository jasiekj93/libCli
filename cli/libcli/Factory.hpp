#pragma once

/**
 * @file Factory.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/ITerminal.hpp>
#include <libcli/ICommandObserver.hpp>
#include <libcli/IOutput.hpp>

namespace cli::Factory
{
    ITerminal * CreateNewTerminal(IOutput &, 
        ICommandObserver &,
        size_t depth = 5, 
        const char *userName = nullptr,
        size_t printfBufferSize = 256); 
}