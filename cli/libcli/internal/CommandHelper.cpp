#include "CommandHelper.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

CommandHelper::CommandHelper(OutputController& output)
    : output(output)
{
}


void CommandHelper::displayHelp(const templates::Command &command)
{
    printUsage(command);

    if(not command.getHelp().empty())
        printCommandHelp(command);

    if (not command.getArguments().empty())
        printArguments(command);
}

void CommandHelper::printUsage(const templates::Command &command)
{
    output << "zastosowanie: " << command.getName();

    if (not command.getArguments().empty())
    {
        output << ' ';
        printArgumentUsage(command);
    }

    output << newLine;
}

void CommandHelper::printArgumentUsage(const templates::Command &command)
{
    for(auto& argument : command.getArguments())
    {
        if (not argument.second.isMandatory())
            output << '[';

        output << '-' << argument.first; 

        if (not argument.second.isMandatory())
            output << ']';

        output << ' ';
    }
}

void CommandHelper::printCommandHelp(const templates::Command &command)
{
    output << '\t' << command.getHelp() << newLine;
}

void CommandHelper::printArguments(const templates::Command &command)
{
    output << newLine;

    for (auto& argument : command.getArguments())
    {
        output << '-' << argument.first << '\t';
        printArgumentType(argument.second);

        if (not argument.second.getHelp().empty())
            output << '\t' << argument.second.getHelp();

        output << newLine;
    }
}

void CommandHelper::printArgumentType(const templates::Argument &argument)
{
    switch(argument.getType())
    {
        case model::Argument::Type::DECIMAL:
            output << "calkowity";
            return;
        case model::Argument::Type::DOUBLE:
            output << "zmiennoprzecinkowy";
            return;
        case model::Argument::Type::EMPTY:
            output << " ";
            return;
        case model::Argument::Type::HEX:
            output << "szesnastkowy";
            return;
        case model::Argument::Type::STRING:
            output << "ciag znakow";
            return;
    }
}
