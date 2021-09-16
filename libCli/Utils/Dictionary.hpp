#pragma once

/**
 * @file Dictionary.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/Buffer.hpp>

namespace Cli::Utils
{
    template<class T, size_t SIZE>
    class Dictionary : public Buffer<T, SIZE>
    {
    public:
        bool Put(const T &) override;

        bool Contains(const char *) const;
        int At(const char *) const;
        T Get(const char *) const;
    };
}

#include <libCli/Utils/Dictionary.tpp>