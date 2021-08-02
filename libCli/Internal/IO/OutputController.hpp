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
        static constexpr char DELETE_CHAR = 0x7f;

        OutputController(IOutput &);

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft() override;
        void MoveCursorRight() override;
        void Backspace(unsigned int) override;
        void Delete(unsigned int) override;
        void NewLine() override;
        void ClearScreen() override;

    private:
        IOutput &_output;
    };
}