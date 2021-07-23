#pragma once

#include <cstddef>

namespace Cli
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
        inline const auto Count() const { return _count; }
        inline const auto Cursor() const { return _cursor; }

        inline auto operator[](size_t i) const { return _data[i]; }
    private:
        char _data[SIZE];
        size_t _count;
        size_t _cursor;
    };
}

#include <libCli/InputBuffer.tpp>