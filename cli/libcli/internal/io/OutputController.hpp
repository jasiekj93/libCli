#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */
namespace cli::internal::io
{
    class OutputController
    {
    public:
        virtual ~OutputController() {}

        virtual void PutChar(char) = 0;
        virtual void PutString(const char *) = 0;
        virtual void MoveCursorLeft(unsigned int times = 1) = 0;
        virtual void MoveCursorRight(unsigned int times = 1) = 0;
        virtual void Backspace(unsigned int times = 1) = 0;
        virtual void Delete(unsigned int times = 1) = 0;
        virtual void NewLine() = 0;
        virtual void ClearScreen() = 0;
    };
}