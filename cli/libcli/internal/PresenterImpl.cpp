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
    output.write(name.data());
    output.write(": nie znaleziono polecenia");
    prompt();
}

void PresenterImpl::noMandatoryArguments(char arg, const templates::Command& command)
{
    output.write(command.getName());
    output.write(": brak wymaganych argumentow: -");
    output.write(arg);
    newLine();
    help(command);
}

void PresenterImpl::invalidArgument(char arg, const templates::Command& command)
{
    output.write(command.getName());
    output.write(": nieprawidlowy argument -");
    output.write(arg);
    newLine();
    help(command);
}

void PresenterImpl::invalidArgumentType(char arg, const templates::Command& command)
{
    output.write(command.getName());
    output.write(": nieprawidlowy typ argumentu -");
    output.write(arg);
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
        
    output.write(userName.data());
    output.write(PROMPT_CHAR);
    output.write(' ');
}


inline void PresenterImpl::newLine()    
{
    output.write("\r\n");
}