#include "Presenter.hpp"
#include <cstring>

using namespace Cli;
using namespace Cli::Internal;

Presenter::Presenter(IOutput &output, const char *userName)
    : _output(output)
    , _helper(output)
    , _userName{'\0'}
{
    if(userName != nullptr &&
        std::strlen(userName) <= Configuration::MAX_USER_NAME)
            std::strcpy(_userName, userName);

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

void Presenter::Prompt(bool addNewLine)
{
    if(addNewLine == true)
        _NewLine();
        
    _output.PutString(_userName);
    _output.PutChar(PROMPT_CHAR);
    _output.PutChar(' ');
}


inline void Presenter::_NewLine()
{
    _output.PutString("\r\n");
}