#pragma once

/**
 * @file Buffer.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace cli::utils
{
    template<class T, size_t SIZE>
    class Buffer
    {
    public:
        Buffer();

        virtual bool Put(const T&);
        void Clear();

        auto Count() const { return _count; }
        auto Size() const { return SIZE; }
        auto Data() const { return _data; }

        const T& operator[](size_t i) const { return _data[i]; }

    protected:
        T _data[SIZE];
        size_t _count;
    };
}

#include <libcli/utils/Buffer.tpp>