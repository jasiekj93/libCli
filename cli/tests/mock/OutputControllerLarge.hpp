#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/OutputController.hpp>
#include <libcli/internal/io/container/LineBuffer.hpp>

namespace mock
{
    class OutputControllerLarge : public cli::OutputController
    {
    public:
        static constexpr auto SIZE = 4096UL;

        OutputControllerLarge();

        OutputController& operator<<(char) override;
        OutputController& operator<<(etl::string_view) override;
        OutputController& operator<<(const cli::formatspec::Base&) override;

        etl::string<SIZE> previousLine;
        etl::string<SIZE> line;

    protected:
        void newLine();
        void clearScreen();
    };
}