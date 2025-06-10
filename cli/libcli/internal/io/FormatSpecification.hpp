#pragma once

/**
 * @file FormatSpecification.hpp
 * @author Adrian Szczepanski
 * @date 05-06-2025
 */

namespace cli::internal::io
{
    namespace formatspec
    {
        enum class Type
        {
            CURSOR_LEFT,
            CURSOR_RIGHT,
            BACKSPACE,
            DELETE,
            NEW_LINE,
            CLEAR_SCREEN,
            FLUSH
        };

        struct Base
        {
            constexpr Base(Type type)
                : type(type)
            {
            }

            const Type type;
        };

        struct Repeated : Base
        {
            constexpr Repeated(Type type, unsigned int times)
                : Base(type)
                , times(times)
            {
            }

            const unsigned int times;
        };
        
    }


    static constexpr formatspec::Repeated cursorLeft(unsigned int times = 1)
    {
        return formatspec::Repeated(formatspec::Type::CURSOR_LEFT, times);
    }

    static constexpr formatspec::Repeated cursorRight(unsigned int times = 1)
    {
        return formatspec::Repeated(formatspec::Type::CURSOR_RIGHT, times);
    }

    static constexpr formatspec::Repeated backspace(unsigned int times = 1)
    {
        return formatspec::Repeated(formatspec::Type::BACKSPACE, times);
    }

    static constexpr formatspec::Repeated deleteChar(unsigned int times = 1)
    {
        return formatspec::Repeated(formatspec::Type::DELETE, times);
    }

    static constexpr formatspec::Base newLine()
    {
        return formatspec::Base(formatspec::Type::NEW_LINE);
    }

    static constexpr formatspec::Base clearScreen()
    {
        return formatspec::Base(formatspec::Type::CLEAR_SCREEN);
    }

    static constexpr formatspec::Base flush()
    {
        return formatspec::Base(formatspec::Type::FLUSH);
    }
}