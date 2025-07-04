#pragma once

/**
 * @file FormatSpecificationExtended.hpp
 * @author Adrian Szczepanski
 * @date 05-06-2025
 */

#include <libcli/FormatSpecification.hpp>

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
        };

        struct Repeated 
        {
            constexpr Repeated(Type type, unsigned int times)
                : type(type)
                , times(times)
            {
            }

            const Type type;
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
}