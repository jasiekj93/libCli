#pragma once

/**
 * @file Configuration.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace cli::Configuration
{
    static constexpr size_t MAX_ARGUMENT_COUNT = 8;
    static constexpr size_t MAX_COMMAND_TEMPLATES_COUNT = 32;
    static constexpr size_t MAX_LINE_LENGTH = 128;
    static constexpr size_t MAX_USER_NAME = 16;
    static constexpr size_t MAX_HISTORY = 8;
}