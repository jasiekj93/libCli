#include "Command.hpp"
#include <cstring>

using namespace Cli::Template;

Command::Command()
    : _name{'\0'}
    , _help{'\0'}
    , _arguments()
{
}

Command::Command(const char *string, const char *help)
    : Command()
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

Command::Command(const char * string, 
    std::initializer_list<Argument> list)
    : Command(string, nullptr, list)
{  
}

Command::Command(const char * string, 
    const char *help,
    std::initializer_list<Argument> list)
    : Command(string, help)
{
     if(std::strlen(_name) == 0)
        return;

    if(list.size() > Configuration::MAX_ARGUMENT_COUNT)
        return;

    for(auto argument : list)
        _arguments.Put(argument);    
}


bool Command::operator==(const Command &command) const
{
    if(std::strcmp(this->_name, command._name) != 0)
        return false;

    if(std::strcmp(this->_help, command._help) != 0)
        return false;

    if(this->_arguments.Count() != command._arguments.Count())
        return false;

    for(size_t i = 0; i < this->_arguments.Count(); i++)
        if(this->_arguments[i] != command._arguments[i])
            return false;
            
    return true;
}