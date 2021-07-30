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


bool ArgumentTemplate::operator==(const ArgumentTemplate &arg) const
{
    if(this->_name != arg._name)
        return false;

    if(this->_type != arg._type)
        return false;

    if(this->_isMandatory != arg._isMandatory)
        return false;

    return (std::strcmp(this->_help, arg._help) == 0);
}

bool ArgumentTemplate::operator!=(const ArgumentTemplate &arg) const
{
    return ((*this == arg) == false);
}

