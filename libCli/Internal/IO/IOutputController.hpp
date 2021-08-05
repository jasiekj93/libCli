#pragma once

/**
 * @file IOutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */
namespace Cli::Internal::IO
{
    class IOutputController
    {
    public:
        virtual ~IOutputController() {}

        virtual void PutChar(char) = 0;
        virtual void PutString(const char *) = 0;
        virtual void MoveCursorLeft(unsigned int times = 1) = 0;
        virtual void MoveCursorRight(unsigned int times = 1) = 0;
        virtual void Backspace(unsigned int times = 1) = 0;
        virtual void NewLine() = 0;
        virtual void ClearScreen() = 0;
        virtual void ClearLine() = 0;
        virtual void ClearToEndOfLine() = 0;
    };
}