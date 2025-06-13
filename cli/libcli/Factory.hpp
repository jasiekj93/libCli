#pragma once

/**
 * @file Factory.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <memory>

#include <etl/string.h>

#include <libcli/Terminal.hpp>
#include <libcli/CommandObserver.hpp>
#include <libcli/IOStream.hpp>
#include <libcli/Language.hpp>

namespace cli::Factory
{
    std::shared_ptr<Terminal> createNewTerminal(OutputStream&, 
        CommandObserver&,
        etl::string_view userName = "",
        language::Dictionary = language::english);
}