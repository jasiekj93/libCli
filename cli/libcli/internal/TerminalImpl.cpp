#include "TerminalImpl.hpp"
#include <cstdarg>
#include <cstdio>

using namespace cli;
using namespace cli::internal;

TerminalImpl::TerminalImpl(Output &output,
    CommandObserver &observer,
    size_t depth,
    const char *userName,
    size_t printfBufferSize)
    : _observer(observer)
    , _output(output)
    , _inputBuffer(Configuration::MAX_COMMAND_LENGTH, depth)
    , _outputController(output)
    , _inputController(_outputController,
        *this,
        _inputBuffer)
    , _presenter(output, userName)
    , _verifier(_presenter)
    , _isInputEnabled(true)
    , _printfBuffer(nullptr)
    , _printfBufferSize(printfBufferSize)
{
    _printfBuffer = new char[printfBufferSize];
}

TerminalImpl::~TerminalImpl()
{
    delete[] _printfBuffer;
}


void TerminalImpl::ReceivedCharCallback(char c)
{
    if(_isInputEnabled)
        _inputController.ReceivedCharCallback(c);
}

void TerminalImpl::ReceivedStringCallback(const char *string)
{
    if(_isInputEnabled)
        _inputController.ReceivedStringCallback(string);
}

void TerminalImpl::ReceivedInputLineCallback(const char *line)
{
    model::Command command(line);

    if(command.IsNull())
    {
        _presenter.Prompt(false);
        return;
    }

    if(_verifier.Verify(command) == false)
        return;

    _isInputEnabled = false;
    _observer.ReceivedCommandCallback(command);
    _presenter.Prompt();
    _isInputEnabled = true;
}

const char * TerminalImpl::ReceivedAutoCompleteCallback(const char *substring)
{
    return _verifier.Find(substring);
}

void TerminalImpl::PutString(const char *string)
{
    if(_isInputEnabled == true)
        _presenter.NewLine();
    
    _output.PutString(string);

    if(_isInputEnabled ==true)
        EnableInput();
}

size_t TerminalImpl::Printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = vsnprintf(_printfBuffer, 
        _printfBufferSize,
        format, 
        args);
    
    PutString(_printfBuffer);

    if(result < 0)
        result = 0;
    else if(result >= (int)_printfBufferSize)
        result = (_printfBufferSize - 1);
    
    va_end (args);
    return result;
}

void TerminalImpl::DisableInput()
{
    auto promptLength = _presenter.PromptLength();
    _isInputEnabled = false;
    _inputController.ClearLine(promptLength);
}

void TerminalImpl::EnableInput()
{
    _isInputEnabled = true;
    _presenter.Prompt();
    _inputController.RestoreLine();
}
