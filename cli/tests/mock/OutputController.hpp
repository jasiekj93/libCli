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
        OutputController();

        OutputController& operator<<(char) override;
        OutputController& operator<<(etl::string_view) override;
        OutputController& operator<<(const cli::internal::io::formatspec::Base&) override;
        OutputController& operator<<(const cli::internal::io::formatspec::Repeated&) override;

        etl::string<cli::internal::io::container::LineBuffer::SIZE> previousLine;
        cli::internal::io::container::LineBuffer line;

    protected:
        void moveCursorLeft(unsigned int times);
        void moveCursorRight(unsigned int times);
        void backspace(unsigned int times);
        void putDelete(unsigned int times);
        void newLine();
        void clearScreen();

    private:
        OutputController(const OutputController&) = delete;
        auto operator=(const OutputController&) = delete;
    };
}