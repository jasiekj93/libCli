#pragma once

/**
 * @file IOutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */
namespace Cli
{
    class IOutputController
    {
    public:
        virtual ~IOutputController() {}

        virtual void PutChar(char) = 0;
        virtual void PutString(const char *) = 0;
        virtual void MoveCursorLeft() = 0;
        virtual void MoveCursorRight() = 0;
        virtual void Backspace(unsigned int times = 1) = 0;
        virtual void Delete(unsigned int times = 1) = 0;
        virtual void NewLine() = 0;
        virtual void ClearScreen() = 0;
    };
}