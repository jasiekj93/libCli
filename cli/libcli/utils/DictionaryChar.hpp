#pragma once

/**
 * @file DictionaryChar.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <etl/map.h>

namespace cli::utils
{
    template<class T, size_t SIZE>
    using DictionaryChar = etl::map<char, T, SIZE>;
}
