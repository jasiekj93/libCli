#pragma once

/**
 * @file ControlSequence.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>
#include <utility>

#include <etl/map.h>
#include <etl/string.h>

namespace cli::internal::io
{
    class ControlSequence
    {
    public:
        static constexpr size_t MAX_SIZE = 4;
        static constexpr size_t KNOWN_TYPES = 7;
        static constexpr size_t MAX_ARROW_REPEAT = 9;

        enum class Type
        {
            ARROW_UP,
            ARROW_DOWN,
            ARROW_LEFT,
            ARROW_RIGHT,
            DELETE,
            HOME,
            END,

            UNKNOWN,
        };

        ControlSequence();
        ControlSequence(Type);
        ControlSequence(Type, unsigned int times);
        ControlSequence(std::initializer_list<char>);
        ControlSequence(etl::string_view);

        bool put(char);
        inline void clear() { data.clear(); }
        Type getType();
        
        inline auto isFull() const { return data.full(); }
        inline bool isEmpty() const { return data.empty(); }

        inline auto getData() const { return data; }
        inline auto getSize() const { return data.size(); }

        inline auto operator[](size_t i) const { return data[i]; }

        inline auto operator==(const ControlSequence &other) const { return data == other.data; }

    private:
        static const etl::map<Type, ControlSequence, KNOWN_TYPES> knownCharacters;

        etl::string<MAX_SIZE> data;
    };
}