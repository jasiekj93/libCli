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
    if(line.empty())
        return presenter.prompt(false);

    IOStream* in = &streams[0];
    IOStream* out = &streams[1];

    auto start = 0;
    auto end = line.find('|', start);

    while (end != etl::string_view::npos)
    {
        model::Command command(line.substr(start, end - start));
        if(not executeCommand(command, *in, *out))
            return cleanAfterExecutions();

        start = end + 1;
        start = line.find_first_not_of(' ', start);
        end = line.find('|', start);
        std::swap(in, out);
        in->seekg(0);
    }

    model::Command command(line.substr(start, line.size() - start));
    if(executeCommand(command, *in, *this))
        presenter.prompt();

    return cleanAfterExecutions();
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

bool TerminalImpl::executeCommand(const model::Command& command, InputStream& in, OutputStream& out)
{
    if(command.isNull())
    {
        presenter.prompt(false);
        return false;
    }

    if(verifier.verify(command) == false)
        return false;

    inputEnabledFlag = false;
    observer.receivedCommandCallback(command, in, out);
    return true;
}

void TerminalImpl::cleanAfterExecutions()
{
    inputEnabledFlag = true;
    for(auto& stream : streams)
    {
        stream.clear();
    }
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
