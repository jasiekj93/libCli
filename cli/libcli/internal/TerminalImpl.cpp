#include "TerminalImpl.hpp"
#include <cstdio>

using namespace cli;
using namespace cli::internal;

TerminalImpl::TerminalImpl(Output &output,
    CommandObserver &observer,
    etl::string_view userName)
    : observer(observer)
    , output(output)
    , inputBuffer()
    , outputController(output)
    , inputController(outputController,
        *this,
        inputBuffer)
    , presenter(output, userName)
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

void TerminalImpl::putString(etl::string_view string)
{
    if(isInputEnabled())
        presenter.newLine();
    
    output.write(string);

    if(isInputEnabled())
        enableInput();
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
