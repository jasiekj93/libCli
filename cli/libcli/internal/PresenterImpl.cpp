#include "PresenterImpl.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

PresenterImpl::PresenterImpl(Output& output, etl::string_view string)
    : output(output)
    , helper(output)
    , userName("")
{
    if(string.size() <= Configuration::MAX_USER_NAME)
        this->userName = string;

    prompt();
}

void PresenterImpl::unknownCommand(etl::string_view name)
{
    output.putString(name.data());
    output.putString(": nie znaleziono polecenia");
    prompt();
}

void PresenterImpl::noMandatoryArguments(char arg, const templates::Command& command)
{
    output.putString(command.getName().c_str());
    output.putString(": brak wymaganych argumentow: -");
    output.putChar(arg);
    newLine();
    help(command);
}

void PresenterImpl::invalidArgument(char arg, const templates::Command& command)
{
    output.putString(command.getName().c_str());
    output.putString(": nieprawidlowy argument -");
    output.putChar(arg);
    newLine();
    help(command);
}

void PresenterImpl::invalidArgumentType(char arg, const templates::Command& command)
{
    output.putString(command.getName().c_str());
    output.putString(": nieprawidlowy typ argumentu -");
    output.putChar(arg);
    newLine();
    help(command);
}

void PresenterImpl::help(const templates::Command& command)
{
    helper.displayHelp(command);
    prompt();
}

void PresenterImpl::prompt(bool addNewLine)
{
    if(addNewLine == true)
        newLine();
        
    output.putString(userName.data());
    output.putChar(PROMPT_CHAR);
    output.putChar(' ');
}


inline void PresenterImpl::newLine()    
{
    output.putString("\r\n");
}