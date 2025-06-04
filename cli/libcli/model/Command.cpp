#include "Command.hpp"
#include <cstring>
#include <cctype>

using namespace cli::model;

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
        _arguments.clear();
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

    if(_name == nullptr)
        return false;

    if(std::strlen(_name) > Configuration::MAX_COMMAND_NAME)
    {
        _name = nullptr;
        return false;
    }
    else
        return true;
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
                if(_arguments.full())
                    return false;
                else
                    _arguments[*name] = Argument(*name, nullptr);

            name = &token[1];

            
            if(std::strlen(token) > 2)
            {
                if(_arguments.full())
                    return false;
                else
                {
                    _arguments[*name] = Argument(*name, &token[2]);
                    name = nullptr;
                }
            }
        }
        else
        {
            if(name == nullptr)
                return false;
            else
            {
                if(_arguments.full())
                    return false;
                else
                {
                    _arguments[*name] = Argument(*name, token);
                    name = nullptr;
                }
            }
        }

        token = std::strtok(nullptr, " ");
    }

    if(name != nullptr)
    {
        if(_arguments.full())
            return false;
        else
        {
            _arguments[*name] = Argument(*name, nullptr);
        }

    }

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