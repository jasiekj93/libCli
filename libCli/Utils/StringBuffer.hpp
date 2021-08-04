#pragma once

/**
 * @file StringBuffer.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/Buffer.hpp>

namespace Cli::Utils
{
    template<size_t SIZE>
    class StringBuffer : public Buffer<char, SIZE + 1>
    {
    public:
        StringBuffer();

        bool Put(const char &c) override;
    };
}

#include <libCli/Utils/StringBuffer.tpp>