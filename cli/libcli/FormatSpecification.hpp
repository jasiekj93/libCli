#pragma once

/**
 * @file FormatSpecification.hpp
 * @author Adrian Szczepanski
 * @date 05-06-2025
 */

namespace cli
{
    namespace formatspec
    {
        enum class Type
        {
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
    }

    static constexpr formatspec::Base newLine(formatspec::Type::NEW_LINE);
    static constexpr formatspec::Base clearScreen(formatspec::Type::CLEAR_SCREEN);
    static constexpr formatspec::Base flush(formatspec::Type::FLUSH);
}