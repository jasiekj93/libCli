#pragma once

#include <cstddef>

namespace Terminal
{
    template<size_t SIZE>
    class InputBuffer
    {
    public:
        InputBuffer();

        bool Put(char);
        void Clear();

        bool MoveCursorLeft();
        bool MoveCursorRight();
        bool Delete();
        
        inline const auto Data() const { return _data; }
        inline const auto Counter() const { return _counter; }
        inline const auto Cursor() const { return _cursor; }

    private:
        char _data[SIZE];
        size_t _count;
        size_t _cursor;
    };
}

#include <libTerminal/InputBuffer.tpp>