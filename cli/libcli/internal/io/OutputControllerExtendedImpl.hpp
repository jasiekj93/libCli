#pragma once

/**
 * @file OutputControllerExtendedImpl.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Output.hpp>
#include <libcli/internal/OutputControllerImpl.hpp>
#include <libcli/internal/io/OutputControllerExtended.hpp>

namespace cli::internal::io
{
    class OutputControllerExtendedImpl : public OutputControllerExtended
    {
    public:
        explicit OutputControllerExtendedImpl(Output&);

        inline OutputController& operator<<(char c) override { return (base << c); }
        inline OutputController& operator<<(etl::string_view string) override { return (base << string); }
        inline OutputController& operator<<(const cli::formatspec::Base& b) override { return (base << b); }

        OutputController& operator<<(const formatspec::Repeated&) override;

    protected:
        void moveCursorLeft(unsigned int);
        void moveCursorRight(unsigned int);
        void backspace(unsigned int);
        void putDelete(unsigned int);
        void newLine();
        void clearScreen();

    private:
        Output& output;
        OutputControllerImpl base;
    };
}