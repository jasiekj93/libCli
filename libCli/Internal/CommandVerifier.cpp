#include "CommandVerifier.hpp"

using namespace Cli;
using namespace Cli::Internal;

Model::Argument CommandVerifier::_help('h', nullptr);


CommandVerifier::Status CommandVerifier::Verify(const Model::Command &command) const
{
    if(_buffer.Contains(command.GetName()) == false)
        return Status::Unknown;

    auto templateCommand = _buffer.Get(command.GetName());

    for(size_t i = 0; i < templateCommand.Arguments().Count(); i++)
    {
        auto &argument = templateCommand.Arguments()[i];
        
        if(command.Arguments().Contains(argument.Name()) == true)
        {
            if(command.Arguments().Get(argument.Name()).GetType() != argument.GetType())
                return Status::InvalidArgumentType;
        }
        else if(argument.IsMandatory() == true)
            return Status::NoMandatoryArguments;
    }

    for(size_t i = 0; i < command.Arguments().Count(); i++)
    {
       if(templateCommand.Arguments().Contains(command.Arguments()[i].Name()) == false)
       {
            if(command.Arguments()[i] == _help)
                return Status::Help;
            else
                return Status::InvalidArgument;
       }
    }

    return Status::Ok;
}
