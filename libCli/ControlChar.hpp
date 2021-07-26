#pragma once

/**
 * @file ControlChar.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>
#include <utility>

namespace Cli
{
    class ControlChar
    {
    public:
        static constexpr size_t MAX_SIZE = 4;
        static constexpr size_t KNOWN_TYPES = 5;
        static constexpr char ESCAPE_CHAR = '\e';

        enum class Type
        {
            ArrowUp,
            ArrowDown,
            ArrowLeft,
            ArrowRight,
            Delete,

            Unknown,
        };

        ControlChar();
        ControlChar(Type);

        bool Put(char);
        void Clear();
        Type GetType();
        
        inline auto Count() const { return _count; }
        inline auto Data() const { return _data; }
        inline auto operator[](size_t i) const { return _data[i]; }

        bool operator==(const ControlChar &);

    protected:
        ControlChar(std::initializer_list<char>);

    private:
        static const ControlChar _knownCharacters[KNOWN_TYPES];

        char _data[MAX_SIZE + 1];
        size_t _count;
    };
}