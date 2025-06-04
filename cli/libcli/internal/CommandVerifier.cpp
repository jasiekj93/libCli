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
    if(_buffer.contains(command.GetName()) == false)
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

    for(auto& command : _buffer)
    {
        auto found = std::strstr(command.first.data(), substring);

        if(found != nullptr)
        {
            if(std::strcmp(found, substring) == 0)
                return nullptr; 
            else if(found == command.first.data())
                return found; 
        }
    }

    return nullptr;
}


bool CommandVerifier::_CheckMandatoryArguments(const model::Command &command)
{
    auto templateCommand = _buffer.at(command.GetName());

    for(auto& argument : templateCommand.getArguments())
    {
        if(command.Arguments().contains(argument.first)) 
        {
            if(command.Arguments().at(argument.first).getType() != argument.second.getType())
            {
                _presenter.InvalidArgumentType(argument.second.getName(), templateCommand);
                return false;
            }
        }
        else if(argument.second.isMandatory())
        {
            _presenter.NoMandatoryArguments(argument.first, templateCommand);
            return false;
        }
    }

    return true;
}

bool CommandVerifier::_CheckOptionalArguments(const model::Command &command)
{
    auto templateCommand = _buffer.at(command.GetName());

    for(auto& argument : command.Arguments())
    {
        if(not templateCommand.getArguments().contains(argument.first))
        {
            if(argument.second == _help)
            {
                _presenter.Help(templateCommand);
                return false;
            }
            else
            {
                _presenter.InvalidArgument(argument.first, templateCommand);
                return false;
            }
        }
    }
    
    return true;
}

