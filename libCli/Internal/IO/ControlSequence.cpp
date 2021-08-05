#include "ControlSequence.hpp"
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace Cli::Internal::IO;

const ControlSequence ControlSequence::_knownCharacters[ControlSequence::KNOWN_TYPES] = 
{
    { '\e', '[', 'A' },
    { '\e', '[', 'B' },
    { '\e', '[', 'D' },
    { '\e', '[', 'C' },
    { '\e', '[', '3', '~' },
    { '\e', '[', '1', '~' },
    { '\e', '[', '4', '~' },
    { '\e', '[', 'K' },
    { '\e', '[', '0', 'K' },
};

ControlSequence::ControlSequence()
{
    Clear();
}

ControlSequence::ControlSequence(Type type)
    : ControlSequence()
{
    if(type != Type::Unknown)
        *this = _knownCharacters[(int)type];
}

ControlSequence::ControlSequence(Type type, unsigned int times)
    : ControlSequence(type)
{
    if(times > MAX_ARROW_REPEAT)
        return;

    if(type == Type::ArrowRight ||
        type == Type::ArrowLeft)
    {
        _data[3] = _data[2];
        _data[2] = '0' + times;
        _data[4] = '\0';
    }
}

ControlSequence::ControlSequence(std::initializer_list<char> list)
{
    if(list.size() <= MAX_SIZE)
    {
        std::copy(list.begin(), list.end(), std::begin(_data));
        _data[list.size()] = '\0';
    }
}

ControlSequence::ControlSequence(const char *string)
{
   std::strcpy(_data, string);
}


bool ControlSequence::Put(char c)
{
    auto length = std::strlen(_data);

    if(length == MAX_SIZE)
        return false;
    
    _data[length++] = c;
    _data[length] = '\0';
    return true;
}

void ControlSequence::Clear()
{
    _data[0] = '\0';
}

ControlSequence::Type ControlSequence::GetType()
{
    for(size_t i = 0; i < KNOWN_TYPES; i++)
        if(*this == _knownCharacters[i])
            return (Type)i;
    
    return Type::Unknown;
}

bool ControlSequence::IsFull()
{
    return (std::strlen(_data) == MAX_SIZE);
}

bool ControlSequence::IsNotEmpty()
{
    return (IsEmpty() == false);
}

bool ControlSequence::IsEmpty()
{
    return (std::strlen(_data) == 0);
}


bool ControlSequence::operator==(const ControlSequence &second)
{
    return (std::strcmp(this->_data, second._data) == 0);
}
