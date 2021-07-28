#include "Command.hpp"
#include <cstring>
#include <cctype>

using namespace Cli;

Command::Command()
    : _data("")
    , _name(nullptr)
{

}

Command::Command(const char *string)
    : Command()
{
    if(std::strlen(string) > Configuration::MAX_COMMAND_LENGTH)
        return;

    std::strcpy(_data, string);
    
    _name = _FindWord(_data);
    
    if(_name == nullptr)
        return;
    
    auto pointer = _FindEndOfWord(_name);

    if(pointer == nullptr)
        return;

    
}


bool Command::IsNull() const
{
    return (_name == nullptr);
}

const char * Command::GetName() const
{
    return _name;
}

size_t Command::ArgumentCount() const
{
    return 0;
}


char * Command::_FindWord(char *pointer)
{
    while((*pointer != '\0') &&
        (std::isspace(*pointer) == true))
        pointer++;

    if(*pointer == '\0')
        return nullptr;
    else
        return pointer;
}

char * Command::_FindEndOfWord(char *pointer)
{
    while((*pointer != '\0') &&
        (std::isgraph(*pointer) == true))
        pointer++;

    if(*pointer == '\0')
        return nullptr;
    else
        return pointer;
}

char * Command::_FindArgument(char *)
{
    return nullptr;
}

void Command::_Clear()
{

}

