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
    IOStream* in = &stream1;
    IOStream* out = &stream2;

    auto start = 0;
    auto end = line.find('|', start);

    while (end != etl::string_view::npos)
    {
        model::Command command(line.substr(start, end - start));

        if(command.isNull())
        {
            presenter.prompt(false);
            return;
        }

        if(verifier.verify(command) == false)
            return;

        inputEnabledFlag = false;
        observer.receivedCommandCallback(command, *in, *out);
        //TODO zabezpieczenie flag

        start = end + 1;
        start = line.find_first_not_of(' ', start);
        end = line.find('|', start);
        std::swap(in, out);
        in->seekg(0);
    }

    model::Command command(line.substr(start, line.size() - start));

    if(command.isNull())
    {
        presenter.prompt(false);
        return;
    }

    if(verifier.verify(command) == false)
        return;

    inputEnabledFlag = false;
    observer.receivedCommandCallback(command, *in, *this);
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
