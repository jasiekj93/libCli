#include "CommandVerifier.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

model::Argument CommandVerifier::help('h', "");

CommandVerifier::CommandVerifier(Presenter &presenter)
    : presenter(presenter)
{
}

bool CommandVerifier::verify(const model::Command &command)
{
    if(not buffer.contains(command.getName()))
    {
        presenter.unknownCommand(command.getName().data());
        return false;
    }

    if(not checkMandatoryArguments(command))
        return false;
        
    return checkOptionalArguments(command);
}

etl::string_view CommandVerifier::find(etl::string_view substring)
{
    if(substring.empty())
        return "";

    for(auto& command : buffer)
    {
        auto found = std::strstr(command.first.data(), substring.data());

        if(found != nullptr)
        {
            if(std::strcmp(found, substring.data()) == 0)
                return "";
            else if(found == command.first.data())
                return found; 
        }
    }

    return "";
}


bool CommandVerifier::checkMandatoryArguments(const model::Command &command)
{
    auto templateCommand = buffer.at(command.getName());

    for(auto& argument : templateCommand.getArguments())
    {
        if(command.getArguments().contains(argument.first)) 
        {
            if(command.getArguments().at(argument.first).getType() != argument.second.getType())
            {
                presenter.invalidArgumentType(argument.first, templateCommand);
                return false;
            }
        }
        else if(argument.second.isMandatory())
        {
            presenter.noMandatoryArguments(argument.first, templateCommand);
            return false;
        }
    }

    return true;
}

bool CommandVerifier::checkOptionalArguments(const model::Command &command)
{
    auto templateCommand = buffer.at(command.getName());

    for(auto& argument : command.getArguments())
    {
        if(not templateCommand.getArguments().contains(argument.first))
        {
            if(argument.second == help)
            {
                presenter.help(templateCommand);
                return false;
            }
            else
            {
                presenter.invalidArgument(argument.first, templateCommand);
                return false;
            }
        }
    }
    
    return true;
}

