#include "Argument.hpp"
#include <cstring>

using namespace cli::templates;

Argument::Argument()
    : name(model::Argument::INVALID_NAME)
    , type(model::Argument::Type::EMPTY)
    , mandatoryValue(false)
    , helpMessage{'\0'}
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
                std::strcpy(helpMessage, help);
        }

        this->name = name;
        this->type = type;
        this->mandatoryValue = isMandatory;
    }


bool Argument::operator==(const Argument &arg) const
{
    if(this->name != arg.name)
        return false;

    if(this->type != arg.type)
        return false;

    if(this->mandatoryValue != arg.mandatoryValue)
        return false;

    return (std::strcmp(this->helpMessage, arg.helpMessage) == 0);
}

bool Argument::operator!=(const Argument &arg) const
{
    return ((*this == arg) == false);
}

