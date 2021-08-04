#pragma once

#include <cstddef>

namespace Cli::Utils
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

#include <libCli/Utils/Buffer.tpp>