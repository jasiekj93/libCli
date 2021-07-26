#include "ControlChar.hpp"
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace Cli;

const ControlChar ControlChar::_knownCharacters[ControlChar::KNOWN_TYPES] = 
{
    { '\e', '[', 'A' },
    { '\e', '[', 'B' },
    { '\e', '[', 'D' },
    { '\e', '[', 'C' },
    { '\e', '[', '3', '~' },
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
        _count = list.size();
        _data[_count] = '\0';
    }
}


bool ControlChar::Put(char c)
{
    if(_count == MAX_SIZE)
        return false;
    
    _data[_count++] = c;
    _data[_count] = '\0';
    
    return true;
}

void ControlChar::Clear()
{
    _count = 0;
    _data[_count] = 0;
}

ControlChar::Type ControlChar::GetType()
{
    for(size_t i = 0; i < KNOWN_TYPES; i++)
        if(*this == _knownCharacters[i])
            return (Type)i;
    
    return Type::Unknown;
}

bool ControlChar::operator==(const ControlChar &second)
{
    if(this->_count != second._count)
        return false;

    return (std::strcmp(this->_data, second._data) == 0);
}
