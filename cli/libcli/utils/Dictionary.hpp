#pragma once

/**
 * @file Dictionary.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <etl/map.h>
#include <etl/string.h>

namespace cli::utils
{
    template<class T, size_t SIZE>
    using Dictionary = etl::map<etl::string_view, T, SIZE>;
}