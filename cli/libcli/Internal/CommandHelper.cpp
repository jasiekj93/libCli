#include "CommandHelper.hpp"
#include <cstring>

using namespace cli;
using namespace cli::Internal;

CommandHelper::CommandHelper(IOutput &output)
    : _output(output)
{
}


void CommandHelper::DisplayHelp(const Template::Command &command)
{
    _PrintUsage(command);

    if (std::strlen(command.Help()) > 0)
        _PrintCommandHelp(command);

    if(command.Arguments().Count() > 0)
        _PrintArguments(command);
}

void CommandHelper::_PrintUsage(const Template::Command &command)
{
    _output.PutString("zastosowanie: ");
    _output.PutString(command.Name());

    if (command.Arguments().Count() > 0)
    {
        _output.PutChar(' ');
        _PrintArgumentUsage(command);
    }

    _output.PutString("\r\n");
}

void CommandHelper::_PrintArgumentUsage(const Template::Command &command)
{
    for (size_t i = 0; i < command.Arguments().Count(); i++)
    {
        auto argument = command.Arguments()[i];

        if (argument.IsMandatory() == false)
            _output.PutChar('[');

        _output.PutChar('-');
        _output.PutChar(argument.Name());

        if (argument.IsMandatory() == false)
            _output.PutChar(']');

        _output.PutChar(' ');
    }
}

void CommandHelper::_PrintCommandHelp(const Template::Command &command)
{
    _output.PutChar('\t');
    _output.PutString(command.Help());
    _output.PutString("\r\n");
}

void CommandHelper::_PrintArguments(const Template::Command &command)
{
    _output.PutString("\r\n");

    for (size_t i = 0; i < command.Arguments().Count(); i++)
    {
        auto argument = command.Arguments()[i];

        _output.PutChar('-');
        _output.PutChar(argument.Name());
        _output.PutChar('\t');
        _PrintArgumentType(argument);


        if (std::strlen(argument.Help()) > 0)
        {
            _output.PutChar('\t');
            _output.PutString(argument.Help());
        }

        _output.PutString("\r\n");
    }
}

void CommandHelper::_PrintArgumentType(const Template::Argument &argument)
{
    switch(argument.GetType())
    {
        case Model::Argument::Type::Decimal:
            return _output.PutString("calkowity");
        case Model::Argument::Type::Double:
            return _output.PutString("zmiennoprzecinkowy");
        case Model::Argument::Type::Empty:
            return _output.PutString(" ");
        case Model::Argument::Type::Hex:
            return _output.PutString("szesnastkowy");
        case Model::Argument::Type::String:
            return _output.PutString("ciag znakow");
    }
}
