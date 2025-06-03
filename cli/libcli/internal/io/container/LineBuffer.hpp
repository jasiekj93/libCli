#pragma once

/**
 * @file LineBuffer.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace cli::internal::io::container
{
    class LineBuffer
    {
    public:
        static constexpr unsigned int MAX_CURSOR_MOVE_SIZE = 9;

        LineBuffer(size_t);
        ~LineBuffer();

        bool put(char);
        bool putString(const char *);
        void clear();

        bool moveCursorLeft();
        bool moveCursorRight();
        unsigned int moveCursorMaxLeft();
        unsigned int moveCursorMaxRight();
        bool remove();

        inline const auto data() const { return _data; }
        inline const auto count() const { return _count; }
        inline const auto cursor() const { return _cursor; }

        inline auto operator[](size_t i) const { return _data[i]; }
        
    protected:
        void copyTo(char *) const;
        void copyFrom(const char *);

    private:
        char *_data;
        const size_t _size;
        size_t _count;
        size_t _cursor;

        LineBuffer(const LineBuffer &) = delete;
        auto operator=(const LineBuffer &) = delete;
    };
}