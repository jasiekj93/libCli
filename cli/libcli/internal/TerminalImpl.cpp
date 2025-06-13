#include "TerminalImpl.hpp"
#include <cstdio>

using namespace cli;
using namespace cli::internal;

TerminalImpl::TerminalImpl(OutputStream &out,
    CommandObserver &observer,
    etl::string_view userName,
    language::Dictionary dictionary)
    : observer(observer)
    , inputBuffer()
    , output(out)
    , inputController(output,
        *this,
        inputBuffer)
    , presenter(output, userName, dictionary)
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
    InputStream& input = stream1;
    OutputStream& output = stream2;

    model::Command command(line);

    if(command.isNull())
    {
        presenter.prompt(false);
        return;
    }

    if(verifier.verify(command) == false)
        return;

    inputEnabledFlag = false;
    observer.receivedCommandCallback(command, input, output);
    presenter.prompt();
    inputEnabledFlag = true;
}

etl::string_view TerminalImpl::receivedAutoCompleteCallback(etl::string_view substring)
{
    return verifier.find(substring);
}

void TerminalImpl::write(char c)
{
    write(etl::string_view(&c, 1));
}

void TerminalImpl::write(etl::string_view string)
{
    if(isInputEnabled())
        output << newLine;

    output << string;

    if(isInputEnabled())
        enableInput();
}

void TerminalImpl::flush()
{
    //TODO
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
