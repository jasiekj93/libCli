#include "CommandVerifier.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

model::Argument CommandVerifier::_help('h', nullptr);

CommandVerifier::CommandVerifier(Presenter &presenter)
    : _presenter(presenter)
{
}

bool CommandVerifier::Verify(const model::Command &command)
{
    if(_buffer.Contains(command.GetName()) == false)
    {
        _presenter.UnknownCommand(command.GetName());
        return false;
    }

    if(_CheckMandatoryArguments(command) == false)
        return false;
        
    return _CheckOptionalArguments(command);
}

const char * CommandVerifier::Find(const char *substring)
{
    if(std::strlen(substring) == 0)
        return nullptr;

    for(size_t i = 0; i < _buffer.Count(); i++)
    {
        auto found = std::strstr(_buffer[i].Name(), substring);

        if(found != nullptr)
        {
            if(std::strcmp(found, substring) == 0)
                return nullptr;
            else if(found == _buffer[i].Name())
                return found;
        }
    }

    return nullptr;
}


bool CommandVerifier::_CheckMandatoryArguments(const model::Command &command)
{
    auto templateCommand = _buffer.Get(command.GetName());

    for(size_t i = 0; i < templateCommand.Arguments().Count(); i++)
    {
        auto &argument = templateCommand.Arguments()[i];
        
        if(command.Arguments().Contains(argument.getName()) == true)
        {
            if(command.Arguments().Get(argument.getName()).getType() != argument.getType())
            {
                _presenter.InvalidArgumentType(argument.getName(), templateCommand);
                return false;
            }
        }
        else if(argument.isMandatory() == true)
        {
            _presenter.NoMandatoryArguments(argument.getName(), templateCommand);
            return false;
        }
    }

    return true;
}

bool CommandVerifier::_CheckOptionalArguments(const model::Command &command)
{
    auto templateCommand = _buffer.Get(command.GetName());
    
    for(size_t i = 0; i < command.Arguments().Count(); i++)
    {
       if(templateCommand.Arguments().Contains(command.Arguments()[i].getName()) == false)
       {
            if(command.Arguments()[i] == _help)
                _presenter.Help(templateCommand);
            else
                _presenter.InvalidArgument(command.Arguments()[i].getName(), templateCommand);

            return false;
       }
    }

    return true;
}

