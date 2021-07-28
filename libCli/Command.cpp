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
    
    _name = std::strtok(_data, " ");

    if(_name == nullptr)
        return;

    char * token = std::strtok(nullptr, " "); 

    while(token != nullptr)
    {
        if(token[0] != '-')
        {
            _Clear();
            return;
        }

        if(std::strlen(token) == 2)
        {

        }

        token = std::strtok(nullptr, " ");
    }
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

void Command::_Clear()
{
    _name = nullptr;
}

