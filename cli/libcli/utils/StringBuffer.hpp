#pragma once

/**
 * @file StringBuffer.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/utils/Buffer.hpp>

namespace cli::utils
{
    template<size_t SIZE>
    class StringBuffer : public Buffer<char, SIZE + 1>
    {
    public:
        StringBuffer();

        bool Put(const char &c) override;
    };
}

#include <libcli/utils/StringBuffer.tpp>