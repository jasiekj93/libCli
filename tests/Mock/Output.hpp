#pragma once

#include <libCli/IOutput.hpp>
#include <libCli/Utils/StringBuffer.hpp>
#include <cstring>

namespace Mock
{
    class Output : public Cli::IOutput
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

        Cli::Utils::StringBuffer<SIZE> buffer;
    };
}