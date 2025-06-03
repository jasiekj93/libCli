#pragma once

/**
 * @file Factory.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/Terminal.hpp>
#include <libcli/CommandObserver.hpp>
#include <libcli/Output.hpp>

namespace cli::Factory
{
    Terminal * CreateNewTerminal(Output &, 
        CommandObserver &,
        size_t depth = 5, 
        const char *userName = nullptr,
        size_t printfBufferSize = 256); 
}