#include "PresenterImpl.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

PresenterImpl::PresenterImpl(OutputController& output, etl::string_view string)
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
    output << name.data() << ": nie znaleziono polecenia";
    prompt();
}

void PresenterImpl::noMandatoryArguments(char arg, const templates::Command& command)
{
    output << command.getName() << ": brak wymaganych argumentow: -" << arg << newLine;
    help(command);
}

void PresenterImpl::invalidArgument(char arg, const templates::Command& command)
{
    output << command.getName() << ": nieprawidlowy argument -" << arg << newLine;
    help(command);
}

void PresenterImpl::invalidArgumentType(char arg, const templates::Command& command)
{
    output << command.getName() << ": nieprawidlowy typ argumentu -" << arg << newLine;
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
        output << newLine;

    output << userName.data() << PROMPT_CHAR << ' ';
}