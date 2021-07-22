#pragma once

namespace Terminal
{
    template<size_t SIZE>
    InputBuffer<SIZE>::InputBuffer()
        : _cursor(0)
        , _count(0)
    {
    }

    template<size_t SIZE>
    bool InputBuffer<SIZE>::Put(char c)
    {
        if(_cursor == SIZE)
            return false;

        _data[_cursor] = c;

        if(_count == _cursor)
            _count++;
        
        _cursor++;
    }

    template<size_t SIZE>
    void InputBuffer<SIZE>::Clear()
    {
        _count = 0;
        _cursor = 0;
    }


    template<size_t SIZE>
    bool InputBuffer<SIZE>::MoveCursorLeft()
    {
        if(_cursor == 0)
            return false;

        _cursor--;
        return true;
    }

    template<size_t SIZE>
    bool InputBuffer<SIZE>::MoveCursorRight()
    {
        if(_cursor == _count)
            return false;

        _cursor++;
        return true;
    }

    template<size_t SIZE>
    bool InputBuffer<SIZE>::Delete()
    {
        //TODO
    }
}