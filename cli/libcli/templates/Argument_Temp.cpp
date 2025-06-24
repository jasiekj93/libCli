#include "Argument.hpp"
#include <cstring>

using namespace cli::templates;

Argument::Argument()
    : type(model::Argument::Type::EMPTY)
    , mandatoryValue(false)
    , helpMessage("")
{
}

Argument::Argument(model::Argument::Type type, 
    bool isMandatory, 
    etl::string_view help)
    : Argument()
    {
        this->helpMessage = help;
        this->type = type;
        this->mandatoryValue = isMandatory;
    }


bool Argument::operator==(const Argument& arg) const
{
    return (this->type == arg.type and
            this->mandatoryValue == arg.mandatoryValue and
            this->helpMessage == arg.helpMessage);
}

bool Argument::operator!=(const Argument& arg) const
{
    return (not (*this == arg));
}

