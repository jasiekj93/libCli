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

namespace Cli::Internal::IO
{
    class ControlChar
    {
    public:
        static constexpr size_t MAX_SIZE = 4;
        static constexpr size_t KNOWN_TYPES = 7;

        enum class Type
        {
            ArrowUp,
            ArrowDown,
            ArrowLeft,
            ArrowRight,
            Delete,
            Home,
            End,

            Unknown,
        };

        ControlChar();
        ControlChar(Type);
        ControlChar(std::initializer_list<char>);
        ControlChar(const char *);

        bool Put(char);
        void Clear();
        Type GetType();
        
        bool IsFull();
        bool IsNotEmpty();
        bool IsEmpty();
        
        inline auto Data() const { return _data; }
        inline auto operator[](size_t i) const { return _data[i]; }

        bool operator==(const ControlChar &);

    protected:

    private:
        static const ControlChar _knownCharacters[KNOWN_TYPES];

        char _data[MAX_SIZE + 1];
    };
}