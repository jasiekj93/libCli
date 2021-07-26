#pragma once

/**
 * @file LineBuffer.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace Cli::Utils
{
    template<size_t SIZE>
    class LineBuffer
    {
    public:
        LineBuffer();

        bool Put(char);
        bool PutString(const char *);
        void Clear();

        bool MoveCursorLeft();
        bool MoveCursorRight();
        bool Delete();
        
        inline const auto Data() const { return _data; }
        inline const auto Count() const { return _count; }
        inline const auto Cursor() const { return _cursor; }

        inline auto operator[](size_t i) const { return _data[i]; }
        
    protected:
        void _CopyTo(char *);
        void _CopyFrom(const char *);

    private:
        char _data[SIZE + 1];
        size_t _count;
        size_t _cursor;
    };
}

#include <libCli/Utils/LineBuffer.tpp>