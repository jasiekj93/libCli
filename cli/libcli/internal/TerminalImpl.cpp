#include "TerminalImpl.hpp"
#include <cstdio>

using namespace cli;
using namespace cli::internal;

TerminalImpl::TerminalImpl(Output &output,
    CommandObserver &observer,
    etl::string_view userName)
    : observer(observer)
    , inputBuffer()
    , outputController(output)
    , inputController(outputController,
        *this,
        inputBuffer)
    , presenter(outputController, userName)
    , verifier(presenter)
    , inputEnabledFlag(true)
{
}

void TerminalImpl::receivedCharCallback(char c)
{
    if(inputEnabledFlag)
        inputController.receivedCharCallback(c);
}

void TerminalImpl::receivedStringCallback(const char *string)
{
    if(inputEnabledFlag)
        inputController.receivedStringCallback(string);
}

void TerminalImpl::receivedInputLineCallback(etl::string_view line)
{
    model::Command command(line);

    if(command.isNull())
    {
        presenter.prompt(false);
        return;
    }

    if(verifier.verify(command) == false)
        return;

    inputEnabledFlag = false;
    observer.receivedCommandCallback(command);
    presenter.prompt();
    inputEnabledFlag = true;
}

etl::string_view TerminalImpl::receivedAutoCompleteCallback(etl::string_view substring)
{
    return verifier.find(substring);
}

OutputController& TerminalImpl::operator<<(char c) 
{
    return putString({ &c, 1 });
}

OutputController& TerminalImpl::operator<<(etl::string_view string) 
{
    return putString(string);
}

OutputController& TerminalImpl::operator<<(const formatspec::Base& format) 
{
    return outputController << format;
}

OutputController& TerminalImpl::putString(etl::string_view string)
{
    if(isInputEnabled())
        outputController << newLine;

    outputController << string;

    if(isInputEnabled())
        enableInput();

    return *this;
}

void TerminalImpl::disableInput()
{
    auto promptLength = presenter.promptLength();
    inputEnabledFlag = false;
    inputController.clearLine(promptLength);
}

void TerminalImpl::enableInput()
{
    inputEnabledFlag = true;
    presenter.prompt();
    inputController.restoreLine();
}
