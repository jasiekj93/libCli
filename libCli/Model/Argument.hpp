#pragma once

/**
 * @file Argument.hpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

namespace Cli::Model
{
    class Argument
    {
    public:
        static constexpr char INVALID_NAME = '\0';
    
        enum class Type
        {
            Decimal,
            Hex,
            String,
            Double,
            Empty
        };

        Argument();
        Argument(char c, const char *);

        inline auto Name() const { return _name; }
        inline auto GetType() const { return _type; }

        bool AsDecimal(unsigned long &) const;
        bool AsDecimal(unsigned long long &) const;
        bool AsHex(unsigned long &) const;
        bool AsHex(unsigned long long &) const; 
        bool AsDouble(double &) const;

        inline auto AsString() const { return _value; }

        bool operator==(const Argument &) const;

    protected:
        bool _ContainsHexPrefix() const;
        bool _IsDecimal() const;
        bool _IsHex() const;
        bool _IsDouble() const;

    private:
        char _name;
        const char *_value;
        Type _type;
    };
}