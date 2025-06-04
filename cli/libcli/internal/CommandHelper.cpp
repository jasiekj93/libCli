#include "CommandHelper.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

CommandHelper::CommandHelper(Output& output)
    : _output(output)
{
}


void CommandHelper::DisplayHelp(const templates::Command &command)
{
    _PrintUsage(command);

    if (std::strlen(command.Help()) > 0)
        _PrintCommandHelp(command);

    if(command.Arguments().Count() > 0)
        _PrintArguments(command);
}

void CommandHelper::_PrintUsage(const templates::Command &command)
{
    _output.putString("zastosowanie: ");
    _output.putString(command.Name());

    if (command.Arguments().Count() > 0)
    {
        _output.putChar(' ');
        _PrintArgumentUsage(command);
    }

    _output.putString("\r\n");
}

void CommandHelper::_PrintArgumentUsage(const templates::Command &command)
{
    for (size_t i = 0; i < command.Arguments().Count(); i++)
    {
        auto argument = command.Arguments()[i];

        if (argument.isMandatory() == false)
            _output.putChar('[');

        _output.putChar('-');
        _output.putChar(argument.getName());

        if (argument.isMandatory() == false)
            _output.putChar(']');

        _output.putChar(' ');
    }
}

void CommandHelper::_PrintCommandHelp(const templates::Command &command)
{
    _output.putChar('\t');
    _output.putString(command.Help());
    _output.putString("\r\n");
}

void CommandHelper::_PrintArguments(const templates::Command &command)
{
    _output.putString("\r\n");

    for (size_t i = 0; i < command.Arguments().Count(); i++)
    {
        auto argument = command.Arguments()[i];

        _output.putChar('-');
        _output.putChar(argument.getName());
        _output.putChar('\t');
        _PrintArgumentType(argument);


        if (std::strlen(argument.help()) > 0)
        {
            _output.putChar('\t');
            _output.putString(argument.help());
        }

        _output.putString("\r\n");
    }
}

void CommandHelper::_PrintArgumentType(const templates::Argument &argument)
{
    switch(argument.getType())
    {
        case model::Argument::Type::DECIMAL:
            return _output.putString("calkowity");
        case model::Argument::Type::DOUBLE:
            return _output.putString("zmiennoprzecinkowy");
        case model::Argument::Type::EMPTY:
            return _output.putString(" ");
        case model::Argument::Type::HEX:
            return _output.putString("szesnastkowy");
        case model::Argument::Type::STRING:
            return _output.putString("ciag znakow");
    }
}
