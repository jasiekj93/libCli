#include "Presenter.hpp"
#include <cstdio>

using namespace Cli;
using namespace Cli::Internal;

Presenter::Presenter(IOutput &output)
    : _output(output)
    , _helper(output)
{
    Prompt();
}


void Presenter::InvalidCommandFormat()
{
    _output.PutString("Nieprawidlowy format polecenia.");
    Prompt();
}

void Presenter::UnknownCommand(const char *name)
{
    _output.PutString(name);
    _output.PutString(": nie znaleziono polecenia");
    Prompt();
}

void Presenter::NoMandatoryArguments(char arg, const Template::Command &command)
{
    _output.PutString(command.Name());
    _output.PutString(": brak wymaganych argumentow");
    _output.PutChar(arg);
    _NewLine();
    Help(command);
}

void Presenter::InvalidArgument(char arg, const Template::Command &command)
{
    _output.PutString(command.Name());
    _output.PutString(": nieprawidlowy argument -");
    _output.PutChar(arg);
    _NewLine();
    Help(command);
}

void Presenter::InvalidArgumentType(char arg, const Template::Command &command)
{
    _output.PutString(command.Name());
    _output.PutString(": nieprawidlowy typ argumentu -");
    _output.PutChar(arg);
    _NewLine();
    Help(command);
}

void Presenter::Help(const Template::Command &command)
{
    _helper.DisplayHelp(command);
    Prompt();
}

void Presenter::Prompt()
{
    _NewLine();
    _output.PutChar(PROMPT_CHAR);
    _output.PutChar(' ');
}

inline void Presenter::_NewLine()
{
    _output.PutString("\r\n");
}