#include "CommandTemplate.hpp"
#include <cstring>

using namespace Cli;

CommandTemplate::CommandTemplate()
    : _name{'\0'}
    , _help{'\0'}
    , _arguments()
{
}

CommandTemplate::CommandTemplate(const char *string, const char *help)
    : CommandTemplate()
{
    if(string == nullptr)
        return;

    if(std::strlen(string) > Configuration::MAX_COMMAND_NAME)
        return;

    if(help != nullptr)
    {
        if(std::strlen(help) > Configuration::MAX_COMMAND_HELP_LENGTH)
            return;
        else
            std::strcpy(_help, help);
    }

    std::strcpy(_name, string);    
}

CommandTemplate::CommandTemplate(const char * string, 
    std::initializer_list<ArgumentTemplate> list)
    : CommandTemplate(string, nullptr, list)
{  
}

CommandTemplate::CommandTemplate(const char * string, 
    const char *help,
    std::initializer_list<ArgumentTemplate> list)
    : CommandTemplate(string, nullptr)
{
     if(std::strlen(_name) == 0)
        return;

    if(list.size() > Configuration::MAX_ARGUMENT_COUNT)
        return;

    for(auto argument : list)
        _arguments.Put(argument);    
}
