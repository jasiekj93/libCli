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
    _output.putString(name);
    _output.putString(": nie znaleziono polecenia");
    Prompt();
}

void PresenterImpl::NoMandatoryArguments(char arg, const templates::Command& command)
{
    _output.putString(command.getName().c_str());
    _output.putString(": brak wymaganych argumentow: -");
    _output.putChar(arg);
    NewLine();
    Help(command);
}

void PresenterImpl::InvalidArgument(char arg, const templates::Command& command)
{
    _output.putString(command.getName().c_str());
    _output.putString(": nieprawidlowy argument -");
    _output.putChar(arg);
    NewLine();
    Help(command);
}

void PresenterImpl::InvalidArgumentType(char arg, const templates::Command& command)
{
    _output.putString(command.getName().c_str());
    _output.putString(": nieprawidlowy typ argumentu -");
    _output.putChar(arg);
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
        
    _output.putString(_userName);
    _output.putChar(PROMPT_CHAR);
    _output.putChar(' ');
}


inline void PresenterImpl::NewLine()    
{
    _output.putString("\r\n");
}