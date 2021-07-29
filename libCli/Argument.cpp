#include "Argument.hpp"
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace Cli;

Argument::Argument()
    : _name(INVALID_NAME)
    , _value(nullptr)
    , _type(Type::Empty)
{

}

Argument::Argument(char c, const char *value)
    : _name(c)
    , _value(value)
{
    unsigned long long output;

    if(_value == nullptr)
        _type = Type::Empty;
    else if(AsDecimal(output) == true)
        _type = Type::Decimal;
    else if(AsHex(output) == true)
        _type = Type::Hex;
    else if(AsDouble((double &)output) == true)
        _type = Type::Double;
    else
        _type = Type::String;
}

bool Argument::AsDecimal(unsigned long &output) const
{
    if(_IsDecimal() == false)
        return false;

    char *end;
    output = std::strtoul(_value, &end, 10);

    return (_value != end);
}

bool Argument::AsDecimal(unsigned long long &output) const
{
    if(_IsDecimal() == false)
        return false;

    char *end;
    output = std::strtoull(_value, &end, 10);

    return (_value != end);
}

bool Argument::AsHex(unsigned long &output) const
{
    if(_IsHex() == false)
        return false;

    char *end;
    output = std::strtoul(_value, &end, 16);

    return (_value != end);
}

bool Argument::AsHex(unsigned long long &output) const
{
    if(_IsHex() == false)
        return false;

    char *end;
    output = std::strtoull(_value, &end, 16);

    return (_value != end);
}

bool Argument::AsDouble(double &output) const
{
    if(_IsDouble() == false)
        return false;

    char *end;
    output = std::strtod(_value, &end);

    return (_value != end);
}

bool Argument::_ContainsHexPrefix() const
{
     if(std::strlen(_value) >= 2)
        if(_value[0] == '0' &&
            _value[1] == 'x')
            return true;

    return false;
}

bool Argument::operator==(const Argument &arg) const
{
    if(this->_name != arg._name)
        return false;

    if(this->_type != arg._type)
        return false;

    if(this->_value != nullptr &&
        arg._value != nullptr)
        return (std::strcmp(this->_value, arg._value) == 0);
    else
        return (this->_value == arg._value);
}


bool Argument::_IsDecimal() const
{
    if(_value == nullptr)
        return false;

    if(_ContainsHexPrefix() == true)
        return false;

    auto pointer = _value;

    while(*pointer != '\0')
    {   
        if(std::isdigit(*pointer) == false)
            return false;

        pointer++;
    }

    return true;
}

bool Argument::_IsHex() const
{
    if(_value == nullptr)
        return false;

    auto pointer = _value;
    
    if(_ContainsHexPrefix() == true)
        pointer = &_value[2]; 


    while(*pointer != '\0')
    {
        if(std::isxdigit(*pointer) == false)
            return false;

        pointer++;
    }

    return true;
}

bool Argument::_IsDouble() const
{
    if(_value == nullptr)
        return false;

    if(_ContainsHexPrefix() == true)
        return false;

    auto pointer = _value;
    unsigned int dotCount = 0;

    while(*pointer != '\0')
    {
        if(std::isdigit(*pointer) == false)
        {
            if(*pointer == '.')
                dotCount++;
            else
                return false;
        }

        pointer++;
    }

    return (dotCount <= 1);
}

