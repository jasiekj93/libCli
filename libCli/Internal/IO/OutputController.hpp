#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libCli/IOutput.hpp>
#include <libCli/Internal/IO/IOutputController.hpp>

namespace Cli::Internal::IO
{
    class OutputController : public IOutputController
    {
    public:
        OutputController(IOutput &);

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft(unsigned int) override;
        void MoveCursorRight(unsigned int) override;
        void Backspace(unsigned int) override;
        void NewLine() override;
        void ClearScreen() override;
        void ClearLine() override;
        void ClearToEndOfLine() override;

    private:
        IOutput &_output;
    };
}