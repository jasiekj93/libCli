#include "Terminal.hpp"
#include <cstdarg>
#include <cstdio>

using namespace Cli;
using namespace Cli::Internal;

Terminal::Terminal(IOutput &output,
    ICommandObserver &observer,
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

Terminal::~Terminal()
{
    delete[] _printfBuffer;
}


void Terminal::ReceivedCharCallback(char c)
{
    if(_isInputEnabled)
        _inputController.ReceivedCharCallback(c);
}

void Terminal::ReceivedStringCallback(const char *string)
{
    if(_isInputEnabled)
        _inputController.ReceivedStringCallback(string);
}

void Terminal::ReceivedInputLineCallback(const char *line)
{
    Model::Command command(line);

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

const char * Terminal::ReceivedAutoComapleteCallback(const char *substring)
{
    return _verifier.Find(substring);
}

void Terminal::PutString(const char *string)
{
    if(_isInputEnabled == true)
        _presenter.NewLine();
    
    _output.PutString(string);

    if(_isInputEnabled ==true)
        EnableInput();
}

size_t Terminal::Printf(const char *format, ...)
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

void Terminal::DisableInput()
{
    auto promptLength = _presenter.PromptLength();
    _isInputEnabled = false;
    _inputController.ClearLine(promptLength);
}

void Terminal::EnableInput()
{
    _isInputEnabled = true;
    _presenter.Prompt();
    _inputController.RestoreLine();
}
