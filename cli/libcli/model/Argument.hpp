#pragma once

/**
 * @file Argument.hpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <etl/string.h> 

namespace cli::model
{
    class Argument
    {
    public:
        static constexpr char INVALID_NAME = '\0';
    
        enum class Type
        {
            DECIMAL,
            HEX,
            STRING,
            DOUBLE,
            EMPTY
        };

        Argument();
        Argument(char c, etl::string_view);

        inline auto getName() const { return name; }
        inline auto getType() const { return type; }

        bool asDecimal(unsigned long &) const;
        bool asDecimal(unsigned long long &) const;
        bool asHex(unsigned long &) const;
        bool asHex(unsigned long long &) const; 
        bool asDouble(double &) const;

        inline auto asString() const { return value; }

        bool operator==(const Argument &) const;

    protected:
        bool containsHexPrefix() const;
        bool isDecimal() const;
        bool isHex() const;
        bool isDouble() const;

    private:
        char name;
        etl::string_view value;
        Type type;
    };
}