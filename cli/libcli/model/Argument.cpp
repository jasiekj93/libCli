#include "Argument.hpp"
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace cli::model;

Argument::Argument()
    : name(INVALID_NAME)
    , value("")
    , type(Type::EMPTY)
{

}

Argument::Argument(char c, etl::string_view val)
    : name(c)
    , value("")
{
    if(val != nullptr)
        value = val;

    unsigned long long output;

    if(value.empty())
        type = Type::EMPTY;
    else if(asDecimal(output) == true)
        type = Type::DECIMAL;
    else if(asHex(output) == true)
        type = Type::HEX;
    else if(asDouble((double &)output) == true)
        type = Type::DOUBLE;
    else
        type = Type::STRING;
}

bool Argument::asDecimal(unsigned long &output) const
{
    if(isDecimal() == false)
        return false;

    char *end;
    output = std::strtoul(value.data(), &end, 10);

    return (value.data() != end);
}

bool Argument::asDecimal(unsigned long long &output) const
{
    if(isDecimal() == false)
        return false;

    char *end;
    output = std::strtoull(value.data(), &end, 10);

    return (value.data() != end);
}

bool Argument::asHex(unsigned long &output) const
{
    if(isHex() == false)
        return false;

    char *end;
    output = std::strtoul(value.data(), &end, 16);

    return (value.data() != end);
}

bool Argument::asHex(unsigned long long &output) const
{
    if(isHex() == false)
        return false;

    char *end;
    output = std::strtoull(value.data(), &end, 16);

    return (value.data() != end);
}

bool Argument::asDouble(double &output) const
{
    if(isDouble() == false)
        return false;

    char *end;
    output = std::strtod(value.data(), &end);

    return (value.data() != end);
}

bool Argument::containsHexPrefix() const
{
     if(value.size() > 2)
        if(value[0] == '0' &&
            value[1] == 'x')
            return true;

    return false;
}

bool Argument::operator==(const Argument &arg) const
{
    return (this->name == arg.name and
            this->type == arg.type and
            this->value == arg.value);
}


bool Argument::isDecimal() const
{
    if(containsHexPrefix() == true)
        return false;

    for(auto& c : value)
    {
        if(not std::isdigit(c))
            return false;
    }

    return true;
}

bool Argument::isHex() const
{
    auto pointer = value.begin();
    
    if(containsHexPrefix() == true)
        pointer += 2;


    for(auto it = pointer; it != value.end(); ++it)
    {
        if(not std::isxdigit(*it))
            return false;
    }

    return true;
}

bool Argument::isDouble() const
{
    if(containsHexPrefix() == true)
        return false;

    auto dotCount = 0U;

    for(auto& c : value)
    {
        if(not std::isdigit(c))
        {
            if(c == '.')
                dotCount++;
            else
                return false;
        }
    }

    return (dotCount <= 1);
}

