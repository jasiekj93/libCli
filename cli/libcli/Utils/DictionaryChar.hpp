#pragma once

/**
 * @file DictionaryChar.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/Utils/Buffer.hpp>

namespace cli::Utils
{
    template<class T, size_t SIZE>
    class DictionaryChar : public Buffer<T, SIZE>
    {
    public:
        bool Put(const T &) override;

        bool Contains(char) const;
        int At(char) const;
        T Get(char) const;
    };
}

#include <libcli/Utils/DictionaryChar.tpp>