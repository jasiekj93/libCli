#include "TerminalImpl.hpp"
#include <cstdarg>
#include <cstdio>

using namespace cli;
using namespace cli::internal;

TerminalImpl::TerminalImpl(Output &output,
    CommandObserver &observer,
    etl::string_view userName,
    size_t printfBufferSize)
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
    , printfBuffer(nullptr)
    , printfBufferSize(printfBufferSize)
{
    printfBuffer = new char[printfBufferSize];
}

TerminalImpl::~TerminalImpl()
{
    delete[] printfBuffer;
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

void TerminalImpl::putString(const char *string)
{
    if(isInputEnabled())
        presenter.newLine();
    
    output.putString(string);

    if(isInputEnabled())
        enableInput();
}

size_t TerminalImpl::printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = vsnprintf(printfBuffer, 
        printfBufferSize,
        format, 
        args);
    
    putString(printfBuffer);

    if(result < 0)
        result = 0;
    else if(result >= (int)printfBufferSize)
        result = (printfBufferSize - 1);
    
    va_end (args);
    return result;
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
