#pragma once

/**
 * @file OutputControllerImpl.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Output.hpp>
#include <libcli/internal/io/OutputController.hpp>

namespace cli::internal::io
{
    class OutputControllerImpl : public OutputController
    {
    public:
        OutputControllerImpl(Output&);

        void PutChar(char) override;
        void PutString(const char *) override;
        void MoveCursorLeft(unsigned int) override;
        void MoveCursorRight(unsigned int) override;
        void Backspace(unsigned int) override;
        void Delete(unsigned int) override;
        void NewLine() override;
        void ClearScreen() override;

    private:
        Output& _output;
    };
}