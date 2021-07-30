#include "CommandVerifier.hpp"

using namespace Cli;

bool CommandVerifier::Verify(const Command &command) const
{
    if(_buffer.Contains(command.GetName()) == false)
        return false;

    auto templateCommand = _buffer.Get(command.GetName());

    for(size_t i = 0; i < templateCommand.Arguments().Count(); i++)
    {
        auto &argument = templateCommand.Arguments()[i];
        
        if(argument.IsMandatory() == true)
            if(command.Arguments().Contains(argument.Name()) == false)
                return false;
    }

    for(size_t i = 0; i < command.Arguments().Count(); i++)
    {
        if(templateCommand.Arguments().Containts(command.Arguments()[i].Name()) == false)
            return false;
    }
}
