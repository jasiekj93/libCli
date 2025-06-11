#pragma once

/**
 * @file OutputControllerImpl.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Output.hpp>
#include <tests/mock/OutputController.hpp>
#include <libcli/internal/io/OutputControllerExtended.hpp>

namespace mock
{
    class OutputControllerExtended : public cli::internal::io::OutputControllerExtended
    {
    public:
        OutputControllerExtended();

        inline cli::OutputController& operator<<(char c) override { return (base << c); }
        inline cli::OutputController& operator<<(etl::string_view string) override { return (base << string); }
        inline cli::OutputController& operator<<(const cli::formatspec::Base& b) override { return (base << b); }

        cli::OutputController& operator<<(const cli::internal::io::formatspec::Repeated&) override;

        mock::OutputController base;

    protected:
        void moveCursorLeft(unsigned int);
        void moveCursorRight(unsigned int);
        void backspace(unsigned int);
        void putDelete(unsigned int);
    };
}