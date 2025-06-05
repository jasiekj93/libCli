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
        static constexpr unsigned int MAX_CURSOR_MOVE_SIZE = 9;
        static constexpr size_t SIZE = Configuration::MAX_COMMAND_LENGTH;

        LineBuffer();

        bool put(char);
        bool putString(etl::string_view);
        void clear();

        bool moveCursorLeft();
        bool moveCursorRight();
        unsigned int moveCursorMaxLeft();
        unsigned int moveCursorMaxRight();
        bool remove();

        inline const auto& getData() const { return buffer; }
        inline const auto getCount() const { return buffer.size(); }
        inline const auto getCursor() const { return etl::distance(buffer.begin(), (const char*)cursor); }

        inline auto operator[](size_t i) const { return buffer[i]; }

    protected:
        void copyTo(etl::istring&) const;
        void copyFrom(const etl::istring&);

    private:
        etl::string<SIZE> buffer;
        etl::string<SIZE>::iterator cursor;
    };
}