#include "ControlChar.hpp"
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace Cli::Internal::IO;

const ControlChar ControlChar::_knownCharacters[ControlChar::KNOWN_TYPES] = 
{
    { '\e', '[', 'A' },
    { '\e', '[', 'B' },
    { '\e', '[', 'D' },
    { '\e', '[', 'C' },
    { '\e', '[', '3', '~' },
    { '\e', '[', '1', '~' },
    { '\e', '[', '4', '~' },
};

ControlChar::ControlChar()
{
    Clear();
}

ControlChar::ControlChar(Type type)
    : ControlChar()
{
    if(type != Type::Unknown)
        *this = _knownCharacters[(int)type];
}

ControlChar::ControlChar(std::initializer_list<char> list)
{
    if(list.size() <= MAX_SIZE)
    {
        std::copy(list.begin(), list.end(), std::begin(_data));
        _data[list.size()] = '\0';
    }
}

ControlChar::ControlChar(const char *string)
{
   std::strcpy(_data, string);
}


bool ControlChar::Put(char c)
{
    auto length = std::strlen(_data);

    if(length == MAX_SIZE)
        return false;
    
    _data[length++] = c;
    _data[length] = '\0';
    return true;
}

void ControlChar::Clear()
{
    _data[0] = '\0';
}

ControlChar::Type ControlChar::GetType()
{
    for(size_t i = 0; i < KNOWN_TYPES; i++)
        if(*this == _knownCharacters[i])
            return (Type)i;
    
    return Type::Unknown;
}

bool ControlChar::IsFull()
{
    return (std::strlen(_data) == MAX_SIZE);
}

bool ControlChar::IsNotEmpty()
{
    return (IsEmpty() == false);
}

bool ControlChar::IsEmpty()
{
    return (std::strlen(_data) == 0);
}


bool ControlChar::operator==(const ControlChar &second)
{
    return (std::strcmp(this->_data, second._data) == 0);
}
