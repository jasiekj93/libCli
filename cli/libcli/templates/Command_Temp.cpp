#include "Command.hpp"
#include <cstring>

using namespace cli::templates;

Command::Command()
    : _name("")
    , _help("")
    , _arguments()
{
}

Command::Command(etl::string_view name, 
    const Arguments& list)
    : Command(name, "", list)
{  
}

Command::Command(etl::string_view name, 
    etl::string_view help,
    const Arguments& list)
    : Command()
{
    if(name.empty())
        return;

    if(name.length() > Configuration::MAX_COMMAND_NAME or
       help.length() > Configuration::MAX_COMMAND_HELP_LENGTH)
        return;
        
    this->_name = name;
    this->_help = help;
    _arguments = list;
}

bool Command::operator==(const Command &command) const
{
    return (this->_name == command._name) and
           (this->_help == command._help) and
           (this->_arguments == command._arguments);
}