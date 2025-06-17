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
    , type(Type::EMPTY)
{
    if(val.data() == nullptr)
        return;
    else
        value = val;

    if(value.empty())
        type = Type::EMPTY;
    else if(isDecimal())
        type = Type::DECIMAL;
    else if(isHex())
        type = Type::HEX;
    else if(isDouble())
        type = Type::DOUBLE;
    else
        type = Type::STRING;
}

std::optional<unsigned long> Argument::asDecimal() const
{
    if(not isDecimal())
        return std::nullopt;

    char *end;
    auto output = std::strtoul(value.data(), &end, 10);

    return ((value.data() != end) ? std::optional<unsigned long>(output) : std::nullopt);
}

std::optional<unsigned long long> Argument::asLongDecimal() const
{
    if(not isDecimal())
        return std::nullopt;

    char *end;
    auto output = std::strtoull(value.data(), &end, 10);

    return ((value.data() != end) ? std::optional<unsigned long long>(output) : std::nullopt);
}

std::optional<unsigned long> Argument::asHex() const
{
    if(not isHex())
        return std::nullopt;

    char *end;
    auto output = std::strtoul(value.data(), &end, 16);

    return ((value.data() != end) ? std::optional<unsigned long>(output) : std::nullopt);
}

std::optional<unsigned long long> Argument::asLongHex() const
{
    if(not isHex())
        return std::nullopt;

    char *end;
    auto output = std::strtoull(value.data(), &end, 16);

    return ((value.data() != end) ? std::optional<unsigned long long>(output) : std::nullopt);
}

std::optional<double> Argument::asDouble() const
{
    if(not isDouble())
        return std::nullopt;

    char *end;
    auto output = std::strtod(value.data(), &end);

    return ((value.data() != end) ? std::optional<double>(output) : std::nullopt);
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

