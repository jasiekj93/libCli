#pragma once

/**
 * @file OutputStreamExtended.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/IOStream.hpp>
#include <libcli/internal/io/FormatSpecificationExtended.hpp>

namespace cli::internal::io
{
    class OutputStreamExtended : public OutputStream
    {
    public:
        OutputStreamExtended(OutputStream&);

        using OutputStream::operator<<;
        OutputStreamExtended& operator<<(const formatspec::Repeated&);

        inline void write(char c) override { base.write(c); };
        inline void write(etl::string_view str) override { base.write(str); };
        inline void flush() override { base.flush(); };

    protected:
        void moveCursorLeft(unsigned int times);
        void moveCursorRight(unsigned int times);
        void backspace(unsigned int times);
        void putDelete(unsigned int times);

    private:
        OutputStream& base;

    };
}