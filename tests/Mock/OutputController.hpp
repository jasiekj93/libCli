#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/IO/IOutputController.hpp>
#include <libCli/Internal/IO/Container/LineBuffer.hpp>

namespace Mock
{
    class OutputController : public Cli::Internal::IO::IOutputController
    {
    public:
        OutputController(size_t);
        ~OutputController();

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft(unsigned int times) override;
        void MoveCursorRight(unsigned int times) override;
        void Backspace(unsigned int times) override;
        void NewLine() override;
        void ClearScreen() override;
        void ClearLine() override;
        void ClearToEndOfLine() override;


        char *previousLine;
        Cli::Internal::IO::Container::LineBuffer line;

    private:
        OutputController(const OutputController &) = delete;
        auto operator=(const OutputController &) = delete;
    };
}