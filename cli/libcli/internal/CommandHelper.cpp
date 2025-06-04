#include "CommandHelper.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

CommandHelper::CommandHelper(Output& output)
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
    output.putString("zastosowanie: ");
    output.putString(command.getName().c_str());

    if (not command.getArguments().empty())
    {
        output.putChar(' ');
        printArgumentUsage(command);
    }

    output.putString("\r\n");
}

void CommandHelper::printArgumentUsage(const templates::Command &command)
{
    for(auto& argument : command.getArguments())
    {
        if (argument.second.isMandatory() == false)
            output.putChar('[');

        output.putChar('-');
        output.putChar(argument.first);

        if (argument.second.isMandatory() == false)
            output.putChar(']');

        output.putChar(' ');
    }
}

void CommandHelper::printCommandHelp(const templates::Command &command)
{
    output.putChar('\t');
    output.putString(command.getHelp().c_str());
    output.putString("\r\n");
}

void CommandHelper::printArguments(const templates::Command &command)
{
    output.putString("\r\n");

    for (auto& argument : command.getArguments())
    {
        output.putChar('-');
        output.putChar(argument.first);
        output.putChar('\t');
        printArgumentType(argument.second);


        if (not argument.second.getHelp().empty())
        {
            output.putChar('\t');
            output.putString(argument.second.getHelp().c_str());
        }

        output.putString("\r\n");
    }
}

void CommandHelper::printArgumentType(const templates::Argument &argument)
{
    switch(argument.getType())
    {
        case model::Argument::Type::DECIMAL:
            return output.putString("calkowity");
        case model::Argument::Type::DOUBLE:
            return output.putString("zmiennoprzecinkowy");
        case model::Argument::Type::EMPTY:
            return output.putString(" ");
        case model::Argument::Type::HEX:
            return output.putString("szesnastkowy");
        case model::Argument::Type::STRING:
            return output.putString("ciag znakow");
    }
}
