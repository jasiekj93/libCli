#pragma once

#include <libcli/IOutput.hpp>
#include <libcli/utils/StringBuffer.hpp>
#include <cstring>

namespace mock
{
    class Output : public cli::IOutput
    {
    public:
        static constexpr size_t SIZE = 1024;

        inline void PutChar(char c) override { buffer.Put(c); }
        inline void PutString(const char *string) override 
        { 
            while(*string != '\0')
            {
                PutChar(*string);
                string++;
            }
        }

        cli::utils::StringBuffer<SIZE> buffer;
    };
}