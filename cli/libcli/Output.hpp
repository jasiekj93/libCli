#pragma once

/**
 * @file Output.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <etl/string_view.h>

namespace cli
{
    class Output
    {
    public:
        virtual ~Output() {}

        virtual void write(char c) = 0;
        virtual void write(etl::string_view) = 0;
        virtual void flush() {}
    };
}