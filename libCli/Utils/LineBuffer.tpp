#pragma once

#include <cstring>

namespace Cli::Utils
{
    template<size_t SIZE>
    LineBuffer<SIZE>::LineBuffer()
        : _count(0)
        , _cursor(0)
    {
    }

    template<size_t SIZE>
    bool LineBuffer<SIZE>::Put(char c)
    {
        if(_cursor == SIZE)
            return false;

        _data[_cursor] = c;

        if(_count == _cursor)
        {
            _count++;
            _data[_count] = '\0';
        }
        
        _cursor++;
        return true;
    }

    template<size_t SIZE>
    bool LineBuffer<SIZE>::PutString(const char *string)
    {
        auto length = std::strlen(string);

        if((_cursor + length + 1) == SIZE)
            return false;

        for(size_t i = 0; i < length; i ++)
            Put(string[i]);
        
        return true;
    }

    template<size_t SIZE>
    void LineBuffer<SIZE>::Clear()
    {
        _count = 0;
        _cursor = 0;
        _data[0] = '\0';
    }


    template<size_t SIZE>
    bool LineBuffer<SIZE>::MoveCursorLeft()
    {
        if(_cursor == 0)
            return false;

        _cursor--;
        return true;
    }

    template<size_t SIZE>
    bool LineBuffer<SIZE>::MoveCursorRight()
    {
        if(_cursor == _count)
            return false;

        _cursor++;
        return true;
    }

    template<size_t SIZE>
    bool LineBuffer<SIZE>::Delete()
    {   
        if(_cursor == _count)
            return false;

        auto size = _count - _cursor;
        std::memcpy(&_data[_cursor], &_data[_cursor + 1], size);
        _count--;

        return true;
    }

    template<size_t SIZE>
    void LineBuffer<SIZE>::_CopyTo(char *output)
    {
        std::strcpy(output, _data);
    }
    
    template<size_t SIZE>
    void LineBuffer<SIZE>::_CopyFrom(const char *input)
    {
        std::strcpy(_data, input);
        _count = strlen(input);
        _cursor = _count;
    }
}