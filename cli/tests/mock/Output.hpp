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

        inline void putChar(char c) override { buffer.push_back(c); }

        inline void putString(const char* string) override 
        { 
            buffer.insert(buffer.end(), string, string + std::strlen(string));
        }

        etl::string<SIZE> buffer;
    };
}