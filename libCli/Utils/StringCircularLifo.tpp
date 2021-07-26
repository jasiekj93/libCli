#pragma once

#include <cstring>

namespace Cli::Utils
{
    template<size_t SIZE, size_t DEPTH>
    StringCircularLifo<SIZE, DEPTH>::StringCircularLifo()
    {
        Clear();
    }
    
    template<size_t SIZE, size_t DEPTH>
    bool StringCircularLifo<SIZE, DEPTH>::Push(const char *string)
    {
        if(std::strlen(string) > SIZE)
            return false;

        std::strcpy(_data[_cursor], string);

        _cursor = (_cursor + 1) % DEPTH;

        if(_count < DEPTH)
            _count++;

        return true;
    }

    template<size_t SIZE, size_t DEPTH>
    const char * StringCircularLifo<SIZE, DEPTH>::Get(size_t id) const
    {
        if(id >= _count)
            return nullptr;

        int index = (_cursor - 1) - (int)id;
        if(index < 0)
            index = DEPTH + index;

        return _data[index];
    }

    template<size_t SIZE, size_t DEPTH>
    void StringCircularLifo<SIZE, DEPTH>::Clear()
    {
        for(size_t i = 0; i < DEPTH; i++)
        {
            _data[i][0] = '\0';
        }
        _count = 0;
        _cursor = 0;
    }
};