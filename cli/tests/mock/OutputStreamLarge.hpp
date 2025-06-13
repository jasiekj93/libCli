#pragma once

/**
 * @file OutputStreamLarge.hpp
 * @author Adrian Szczepanski
 * @date 13-06-2025
 */

#include <libcli/IOStream.hpp>

namespace mock
{
    class OutputStreamLarge : public cli::OutputStream
    {
    public:
        static constexpr auto SIZE = 4096UL;

        void write(char c) override;
        void write(etl::string_view) override;

        etl::string<SIZE> line;
    };
}