#pragma once

/**
 * @file DictionaryChar.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/Buffer.hpp>

namespace Cli::Utils
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

#include <libCli/Utils/DictionaryChar.tpp>