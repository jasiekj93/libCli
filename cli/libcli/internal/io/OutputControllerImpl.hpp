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

        void putChar(char) override;
        void putString(etl::string_view) override;
        void moveCursorLeft(unsigned int) override;
        void moveCursorRight(unsigned int) override;
        void backspace(unsigned int) override;
        void putDelete(unsigned int) override;
        void newLine() override;
        void clearScreen() override;

    private:
        Output& output;
    };
}