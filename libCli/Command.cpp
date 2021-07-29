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
    
    if(_FindName() == false)
        return;

    if(_FindArguments() == false)
        _arguments.Clear();
}


bool Command::IsNull() const
{
    return (_name == nullptr);
}

const char * Command::GetName() const
{
    return _name;
}

bool Command::_FindName()
{
    _name = std::strtok(_data, " ");

    return (_name != nullptr);
}

bool Command::_FindArguments()
{
    char * token = std::strtok(nullptr, " ");
    const char *name = nullptr; 

    while(token != nullptr)
    {
        if(_HyphenCount(token) > 1)
            return false;

        if(token[0] == '-')
        {
            if(std::strlen(token) == 1)
                return false;

            if(name != nullptr)
                 if(_arguments.Put(Argument(*name, nullptr)) == false)
                    return false;

            name = &token[1];

            
            if(std::strlen(token) > 2)
            {
                if(_arguments.Put(Argument(*name, &token[2])) == false)
                    return false;
                else
                    name = nullptr;
            }
        }
        else
        {
            if(name == nullptr)
                return false;
            else
            {
                if(_arguments.Put(Argument(*name, token)) == false)
                    return false;
                else
                    name = nullptr;
            }
        }

        token = std::strtok(nullptr, " ");
    }


    if(name != nullptr)
        if(_arguments.Put(Argument(*name, nullptr)) == false)
            return false;

    return true;
}

unsigned int Command::_HyphenCount(const char *token) const
{
    unsigned int result = 0;

    while (*token != '\0')
    {
        if(*token == '-')
            result++;

        token ++;
    }
    
    return result;
}