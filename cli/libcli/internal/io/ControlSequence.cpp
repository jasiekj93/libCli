#include "ControlSequence.hpp"
#include <algorithm>
#include <iterator>
#include <cstring>

using namespace cli::internal::io;

const etl::map<ControlSequence::Type, ControlSequence, ControlSequence::KNOWN_TYPES> ControlSequence::knownCharacters = 
{
    { ControlSequence::Type::ARROW_UP, ControlSequence{ '\e', '[', 'A' }},
    { ControlSequence::Type::ARROW_DOWN, ControlSequence{ '\e', '[', 'B' }},
    { ControlSequence::Type::ARROW_LEFT, ControlSequence{ '\e', '[', 'D' }},
    { ControlSequence::Type::ARROW_RIGHT, ControlSequence{ '\e', '[', 'C' }},
    { ControlSequence::Type::DELETE, ControlSequence{ '\e', '[', '3', '~' }},
    { ControlSequence::Type::HOME, ControlSequence{ '\e', '[', '1', '~' }},
    { ControlSequence::Type::END, ControlSequence{ '\e', '[', '4', '~' }},
};

ControlSequence::ControlSequence()
{
    clear();
}

ControlSequence::ControlSequence(Type type)
    : ControlSequence()
{
    if(type != Type::UNKNOWN)
        *this = knownCharacters.at(type);
}

ControlSequence::ControlSequence(Type type, unsigned int times)
    : ControlSequence(type)
{
    if(times > MAX_ARROW_REPEAT)
        return;

    if(type == Type::ARROW_RIGHT ||
        type == Type::ARROW_LEFT)
    {
        data[3] = data[2];
        data[2] = '0' + times;
        data[4] = '\0';
    }
}

ControlSequence::ControlSequence(std::initializer_list<char> list)
{
    if(list.size() <= MAX_SIZE)
        data = list;
}

ControlSequence::ControlSequence(etl::string_view string)
{
   if(string.size() <= data.max_size())
        data = string;
}


bool ControlSequence::put(char c)
{   
    if(data.full())
        return false;

    data.push_back(c);
    return true;
}

ControlSequence::Type ControlSequence::getType()
{
    for(auto& [type, knownCharacter] : knownCharacters)
    {
        if(*this == knownCharacter)
            return type;
    }
    
    return Type::UNKNOWN;
}
