#pragma once

namespace Cli::Utils
{
    template<class T, size_t SIZE>
    Buffer<T, SIZE>::Buffer()
        : _count(0)
    {
    }

    template<class T, size_t SIZE>
    bool Buffer<T, SIZE>::Put(const T& object)
    {
        if(_count == SIZE)
            return false;

        _data[_count++] = object;
        return true;
    }

    template<class T, size_t SIZE>
    void Buffer<T, SIZE>::Clear()
    {
        _count = 0;
    }
}