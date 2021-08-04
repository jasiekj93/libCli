#pragma once

/**
 * @file Configuration.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace Cli::Configuration
{
    static constexpr size_t MAX_ARGUMENT_COUNT = 8;
    static constexpr size_t MAX_COMMAND_TEMPLATES_COUNT = 10;
    static constexpr size_t MAX_COMMAND_LENGTH = 128;
    static constexpr size_t MAX_COMMAND_NAME = 32;
    static constexpr size_t MAX_COMMAND_HELP_LENGTH = 64;
    static constexpr size_t MAX_ARGUMENT_HELP_LENGTH = 32;
}