#pragma once

#include <cstring>

namespace cli::utils
{
    template<class T, size_t SIZE>
    bool Dictionary<T, SIZE>::Put(const T &object)
    {
        if (Contains(object.Name()) == true)
            return false;
        else
            return Buffer<T, SIZE>::Put(object);
    }

    template<class T, size_t SIZE>
    bool Dictionary<T, SIZE>::Contains(const char *name) const
    {
        return (At(name) >= 0);
    }

    template<class T, size_t SIZE>
    int Dictionary<T, SIZE>::At(const char *name) const
    {
        for (size_t i = 0; i < Buffer<T, SIZE>::_count; i++)
            if (std::strcmp(Buffer<T, SIZE>::_data[i].Name(), name) == 0)
                return i;

        return -1;
    }

    template<class T, size_t SIZE>
    T Dictionary<T, SIZE>::Get(const char *name) const
    {
        auto at = At(name);

        if (at == -1)
            return T();
        else
            return Buffer<T, SIZE>::_data[at];
    }

}