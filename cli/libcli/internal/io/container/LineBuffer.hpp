#pragma once

/**
 * @file LineBuffer.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

#include <etl/string.h>

#include <libcli/Configuration.hpp>

namespace cli::internal::io::container
{
    class LineBuffer
    {
    public:
        static constexpr size_t SIZE = Configuration::MAX_LINE_LENGTH;

        LineBuffer();

        bool push(char);
        bool push(etl::string_view);
        void clear();

        bool moveCursorLeft();
        bool moveCursorRight();
        size_t moveCursorHome();
        size_t moveCursorEnd();
        bool remove();

        inline const auto& getData() const { return buffer; }
        inline const auto getCount() const { return buffer.size(); }
        inline const auto getCursor() const { return etl::distance(buffer.begin(), (const char*)cursor); }

        etl::string_view getDataAfterCursor() const;
        inline bool isCursorAtEnd() const { return cursor == buffer.end(); }
        inline const auto getCursorCount() const { return etl::distance((const char*)cursor, buffer.end()); }

        inline auto operator[](size_t i) const { return buffer[i]; }

    protected:
        void copyTo(etl::istring&) const;
        void copyFrom(const etl::istring&);

    private:
        etl::string<SIZE> buffer;
        etl::string<SIZE>::iterator cursor;
    };
}