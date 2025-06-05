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
    output.write("zastosowanie: ");
    output.write(command.getName().c_str());

    if (not command.getArguments().empty())
    {
        output.write(' ');
        printArgumentUsage(command);
    }

    output.write("\r\n");
}

void CommandHelper::printArgumentUsage(const templates::Command &command)
{
    for(auto& argument : command.getArguments())
    {
        if (argument.second.isMandatory() == false)
            output.write('[');

        output.write('-');
        output.write(argument.first);

        if (argument.second.isMandatory() == false)
            output.write(']');

        output.write(' ');
    }
}

void CommandHelper::printCommandHelp(const templates::Command &command)
{
    output.write('\t');
    output.write(command.getHelp().c_str());
    output.write("\r\n");
}

void CommandHelper::printArguments(const templates::Command &command)
{
    output.write("\r\n");

    for (auto& argument : command.getArguments())
    {
        output.write('-');
        output.write(argument.first);
        output.write('\t');
        printArgumentType(argument.second);


        if (not argument.second.getHelp().empty())
        {
            output.write('\t');
            output.write(argument.second.getHelp().c_str());
        }

        output.write("\r\n");
    }
}

void CommandHelper::printArgumentType(const templates::Argument &argument)
{
    switch(argument.getType())
    {
        case model::Argument::Type::DECIMAL:
            return output.write("calkowity");
        case model::Argument::Type::DOUBLE:
            return output.write("zmiennoprzecinkowy");
        case model::Argument::Type::EMPTY:
            return output.write(" ");
        case model::Argument::Type::HEX:
            return output.write("szesnastkowy");
        case model::Argument::Type::STRING:
            return output.write("ciag znakow");
    }
}
