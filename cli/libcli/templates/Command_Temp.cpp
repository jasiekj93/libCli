#include "Command.hpp"
#include <cstring>

using namespace cli::templates;

Command::Command()
    : name("")
    , help("")
    , arguments()
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
        
    this->name = name;
    this->help = help;
    arguments = list;
}

bool Command::operator==(const Command &command) const
{
    return (this->name == command.name) and
           (this->help == command.help) and
           (this->arguments == command.arguments);
}