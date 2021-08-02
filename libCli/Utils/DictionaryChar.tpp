#pragma once

namespace Cli::Utils
{
    template<class T, size_t SIZE>
    bool DictionaryChar<T, SIZE>::Put(const T &object)
    {
        if (Contains(object.Name()) == true)
            return false;
        else
            return Buffer<T, SIZE>::Put(object);
    }

    template<class T, size_t SIZE>
    bool DictionaryChar<T, SIZE>::Contains(char c) const
    {
        return (At(c) != -1);
    }

    template<class T, size_t SIZE>
    int DictionaryChar<T, SIZE>::At(char c) const
    {
        for (size_t i = 0; i < Buffer<T, SIZE>::_count; i++)
            if (Buffer<T, SIZE>::_data[i].Name() == c)
                return i;

        return -1;
    }

    template<class T, size_t SIZE>
    T DictionaryChar<T, SIZE>::Get(char c) const
    {
        auto at = At(c);

        if (at == -1)
            return T();
        else
            return Buffer<T, SIZE>::_data[at];
    }

}
