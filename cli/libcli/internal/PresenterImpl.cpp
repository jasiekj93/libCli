#include "PresenterImpl.hpp"
#include <cstring>

using namespace cli;
using namespace cli::internal;

PresenterImpl::PresenterImpl(OutputController& output, etl::string_view string, language::Dictionary dictionary)
    : output(output)
    , helper(output, dictionary)
    , userName("")
    , dictionary(dictionary)
{
    if(string.size() <= Configuration::MAX_USER_NAME)
        this->userName = string;

    prompt();
}

void PresenterImpl::unknownCommand(etl::string_view name)
{
    output << name.data() << ": " << dictionary.unknownCommand;
    prompt();
}

void PresenterImpl::noMandatoryArguments(char arg, const templates::Command& command)
{
    output << command.getName() << ": " << dictionary.noMandatoryArguments << ": -" << arg << newLine;
    help(command);
}

void PresenterImpl::invalidArgument(char arg, const templates::Command& command)
{
    output << command.getName() << ": " << dictionary.invalidArgument << ": -" << arg << newLine;
    help(command);
}

void PresenterImpl::invalidArgumentType(char arg, const templates::Command& command)
{
    output << command.getName() << ": " << dictionary.invalidArgumentType << ": -" << arg << newLine;
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