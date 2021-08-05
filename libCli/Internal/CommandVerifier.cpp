#include "CommandVerifier.hpp"
#include <cstring>

using namespace Cli;
using namespace Cli::Internal;

Model::Argument CommandVerifier::_help('h', nullptr);

CommandVerifier::CommandVerifier(IPresenter &presenter)
    : _presenter(presenter)
{
}

bool CommandVerifier::Verify(const Model::Command &command)
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


bool CommandVerifier::_CheckMandatoryArguments(const Model::Command &command)
{
    auto templateCommand = _buffer.Get(command.GetName());

    for(size_t i = 0; i < templateCommand.Arguments().Count(); i++)
    {
        auto &argument = templateCommand.Arguments()[i];
        
        if(command.Arguments().Contains(argument.Name()) == true)
        {
            if(command.Arguments().Get(argument.Name()).GetType() != argument.GetType())
            {
                _presenter.InvalidArgumentType(argument.Name(), templateCommand);
                return false;
            }
        }
        else if(argument.IsMandatory() == true)
        {
            _presenter.NoMandatoryArguments(argument.Name(), templateCommand);
            return false;
        }
    }

    return true;
}

bool CommandVerifier::_CheckOptionalArguments(const Model::Command &command)
{
    auto templateCommand = _buffer.Get(command.GetName());
    
    for(size_t i = 0; i < command.Arguments().Count(); i++)
    {
       if(templateCommand.Arguments().Contains(command.Arguments()[i].Name()) == false)
       {
            if(command.Arguments()[i] == _help)
                _presenter.Help(templateCommand);
            else
                _presenter.InvalidArgument(command.Arguments()[i].Name(), templateCommand);

            return false;
       }
    }

    return true;
}

