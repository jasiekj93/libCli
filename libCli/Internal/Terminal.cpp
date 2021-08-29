#include "Terminal.hpp"

using namespace Cli;
using namespace Cli::Internal;

Terminal::Terminal(IOutput &output,
    ICommandObserver &observer,
    size_t depth,
    const char *userName)
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
{
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

    _observer.ReceivedCommandCallback(command);
    _presenter.Prompt();
}

const char * Terminal::ReceivedAutoComapleteCallback(const char *substring)
{
    return _verifier.Find(substring);
}

void Terminal::PutString(const char *string)
{
    _presenter.NewLine();
    _output.PutString(string);

    if(_isInputEnabled)
    {
        _presenter.Prompt();
        _inputController.RestoreLine();
    }
}

void Terminal::DisableInput()
{
    _isInputEnabled = false;
    _presenter.NewLine();
}

void Terminal::EnableInput()
{
    _isInputEnabled = true;
    _presenter.Prompt();
}
