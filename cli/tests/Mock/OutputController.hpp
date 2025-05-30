#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Internal/IO/IOutputController.hpp>
#include <libcli/Internal/IO/Container/LineBuffer.hpp>

namespace Mock
{
    class OutputController : public cli::Internal::IO::IOutputController
    {
    public:
        OutputController(size_t);
        ~OutputController();

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft(unsigned int times) override;
        void MoveCursorRight(unsigned int times) override;
        void Backspace(unsigned int times) override;
        void Delete(unsigned int times) override;
        void NewLine() override;
        void ClearScreen() override;


        char *previousLine;
        cli::Internal::IO::Container::LineBuffer line;

    private:
        OutputController(const OutputController &) = delete;
        auto operator=(const OutputController &) = delete;
    };
}