#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

namespace cli::internal::io
{
    class OutputController
    {
    public:
        virtual ~OutputController() {}

        virtual void putChar(char) = 0;
        virtual void putString(etl::string_view) = 0;
        virtual void moveCursorLeft(unsigned int times = 1) = 0;
        virtual void moveCursorRight(unsigned int times = 1) = 0;
        virtual void backspace(unsigned int times = 1) = 0;
        virtual void putDelete(unsigned int times = 1) = 0;
        virtual void newLine() = 0;
        virtual void clearScreen() = 0;
    };
}