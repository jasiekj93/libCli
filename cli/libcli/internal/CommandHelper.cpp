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

    if (not command.Arguments().empty())
        _PrintArguments(command);
}

void CommandHelper::_PrintUsage(const templates::Command &command)
{
    _output.putString("zastosowanie: ");
    _output.putString(command.Name());

    if (not command.Arguments().empty())
    {
        _output.putChar(' ');
        _PrintArgumentUsage(command);
    }

    _output.putString("\r\n");
}

void CommandHelper::_PrintArgumentUsage(const templates::Command &command)
{
    for(auto& argument : command.Arguments())
    {
        if (argument.second.isMandatory() == false)
            _output.putChar('[');

        _output.putChar('-');
        _output.putChar(argument.first);

        if (argument.second.isMandatory() == false)
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

    for (auto& argument : command.Arguments())
    {
        _output.putChar('-');
        _output.putChar(argument.first);
        _output.putChar('\t');
        _PrintArgumentType(argument.second);


        if (std::strlen(argument.second.help()) > 0)
        {
            _output.putChar('\t');
            _output.putString(argument.second.help());
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
