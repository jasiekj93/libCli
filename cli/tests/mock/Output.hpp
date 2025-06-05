#pragma once

#include <etl/string.h>

#include <libcli/Output.hpp>
#include <cstring>

namespace mock
{
    class Output : public cli::Output
    {
    public:
        static constexpr size_t SIZE = 1024;

        inline void write(char c) override { buffer.push_back(c); }

        inline void write(etl::string_view string) override 
        { 
            buffer.insert(buffer.end(), string.begin(), string.end());
        }

        etl::string<SIZE> buffer;
    };
}