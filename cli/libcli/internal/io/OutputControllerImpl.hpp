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

        OutputController& operator<<(char) override;
        OutputController& operator<<(etl::string_view) override;
        OutputController& operator<<(const formatspec::Base&) override;
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
    };
}