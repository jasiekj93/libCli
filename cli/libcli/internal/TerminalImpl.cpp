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


void TerminalImpl::receivedCharCallback(char c)
{
    if(_isInputEnabled)
        _inputController.ReceivedCharCallback(c);
}

void TerminalImpl::receivedStringCallback(const char *string)
{
    if(_isInputEnabled)
        _inputController.ReceivedStringCallback(string);
}

void TerminalImpl::receivedInputLineCallback(const char *line)
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

const char * TerminalImpl::receivedAutoCompleteCallback(const char *substring)
{
    return _verifier.Find(substring);
}

void TerminalImpl::putString(const char *string)
{
    if(_isInputEnabled == true)
        _presenter.NewLine();
    
    _output.PutString(string);

    if(_isInputEnabled ==true)
        enableInput();
}

size_t TerminalImpl::printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = vsnprintf(_printfBuffer, 
        _printfBufferSize,
        format, 
        args);
    
    putString(_printfBuffer);

    if(result < 0)
        result = 0;
    else if(result >= (int)_printfBufferSize)
        result = (_printfBufferSize - 1);
    
    va_end (args);
    return result;
}

void TerminalImpl::disableInput()
{
    auto promptLength = _presenter.PromptLength();
    _isInputEnabled = false;
    _inputController.ClearLine(promptLength);
}

void TerminalImpl::enableInput()
{
    _isInputEnabled = true;
    _presenter.Prompt();
    _inputController.RestoreLine();
}
