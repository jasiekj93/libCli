#include "ArgumentTemplate.hpp"
#include <cstring>

using namespace Cli;

ArgumentTemplate::ArgumentTemplate()
    : _name(Argument::INVALID_NAME)
    , _type(Argument::Type::Empty)
    , _isMandatory(false)
    , _help{'\0'}
{
}

ArgumentTemplate::ArgumentTemplate(char name, 
    Argument::Type type, 
    bool isMandatory, 
    const char * help)
    : ArgumentTemplate()
    {
        if(help != nullptr)
        {
            if(std::strlen(help) > Configuration::MAX_ARGUMENT_HELP_LENGTH)
                return;
            else
                std::strcpy(_help, help);
        }

        _name = name;
        _type = type;
        _isMandatory = isMandatory;
    }
