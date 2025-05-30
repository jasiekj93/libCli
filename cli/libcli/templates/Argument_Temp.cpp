#include "Argument.hpp"
#include <cstring>

using namespace cli::templates;

Argument::Argument()
    : _name(model::Argument::INVALID_NAME)
    , _type(model::Argument::Type::Empty)
    , _isMandatory(false)
    , _help{'\0'}
{
}

Argument::Argument(char name, 
    model::Argument::Type type, 
    bool isMandatory, 
    const char * help)
    : Argument()
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


bool Argument::operator==(const Argument &arg) const
{
    if(this->_name != arg._name)
        return false;

    if(this->_type != arg._type)
        return false;

    if(this->_isMandatory != arg._isMandatory)
        return false;

    return (std::strcmp(this->_help, arg._help) == 0);
}

bool Argument::operator!=(const Argument &arg) const
{
    return ((*this == arg) == false);
}

