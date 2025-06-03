#include "PresenterImpl.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

PresenterImpl::PresenterImpl(Output& output, const char* userName)
    : _output(output)
    , _helper(output)
    , _userName{'\0'}
{
    if(userName != nullptr &&
        std::strlen(userName) <= Configuration::MAX_USER_NAME)
            std::strcpy(_userName, userName);

    Prompt();
}

void PresenterImpl::UnknownCommand(const char *name)
{
    _output.PutString(name);
    _output.PutString(": nie znaleziono polecenia");
    Prompt();
}

void PresenterImpl::NoMandatoryArguments(char arg, const templates::Command& command)
{
    _output.PutString(command.Name());
    _output.PutString(": brak wymaganych argumentow: -");
    _output.PutChar(arg);
    NewLine();
    Help(command);
}

void PresenterImpl::InvalidArgument(char arg, const templates::Command& command)
{
    _output.PutString(command.Name());
    _output.PutString(": nieprawidlowy argument -");
    _output.PutChar(arg);
    NewLine();
    Help(command);
}

void PresenterImpl::InvalidArgumentType(char arg, const templates::Command& command)
{
    _output.PutString(command.Name());
    _output.PutString(": nieprawidlowy typ argumentu -");
    _output.PutChar(arg);
    NewLine();
    Help(command);
}

void PresenterImpl::Help(const templates::Command& command)
{
    _helper.DisplayHelp(command);
    Prompt();
}

void PresenterImpl::Prompt(bool addNewLine)
{
    if(addNewLine == true)
        NewLine();
        
    _output.PutString(_userName);
    _output.PutChar(PROMPT_CHAR);
    _output.PutChar(' ');
}


inline void PresenterImpl::NewLine()    
{
    _output.PutString("\r\n");
}