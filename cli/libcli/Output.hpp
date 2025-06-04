#pragma once

/**
 * @file Output.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

namespace cli
{
    class Output
    {
    public:
        virtual ~Output() {}

        virtual void putChar(char c) = 0;
        virtual void putString(const char*) = 0;
    };
}