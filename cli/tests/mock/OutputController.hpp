#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/OutputController.hpp>
#include <libcli/internal/io/container/LineBuffer.hpp>

namespace mock
{
    class OutputController : public cli::internal::io::OutputController
    {
    public:
        OutputController(size_t);
        ~OutputController();

        void putChar(char) override;
        void putString(etl::string_view) override;
        void moveCursorLeft(unsigned int times) override;
        void moveCursorRight(unsigned int times) override;
        void backspace(unsigned int times) override;
        void putDelete(unsigned int times) override;
        void newLine() override;
        void clearScreen() override;


        char* previousLine;
        cli::internal::io::container::LineBuffer line;

    private:
        OutputController(const OutputController&) = delete;
        auto operator=(const OutputController&) = delete;
    };
}