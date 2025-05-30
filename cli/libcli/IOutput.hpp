#pragma once

/**
 * @file IOutput.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

namespace cli
{
    class IOutput
    {
    public:
        virtual ~IOutput() {}

        virtual void PutChar(char c) = 0;
        virtual void PutString(const char *) = 0;
    };
}