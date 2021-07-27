#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libCli/IOutputController.hpp>
#include <libCli/Utils/LineBuffer.hpp>

namespace Mock
{
    class OutputController : public Cli::IOutputController
    {
    public:
        OutputController(size_t);
        ~OutputController();

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft() override;
        void MoveCursorRight() override;
        void Backspace(unsigned int times) override;
        void Delete(unsigned int times) override;
        void NewLine() override;
        void ClearScreen() override;


        char *previousLine;
        Cli::Utils::LineBuffer line;

    private:
        OutputController(const OutputController &) = delete;
        auto operator=(const OutputController &) = delete;
    };
}