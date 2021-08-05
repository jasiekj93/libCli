#include "Terminal.hpp"

using namespace Cli;
using namespace Cli::Internal;

Terminal::Terminal(IOutput &output,
    ICommandObserver &observer,
    size_t depth,
    const char *userName)
    : _observer(observer)
    , _inputBuffer(Configuration::MAX_COMMAND_LENGTH, depth)
    , _outputController(output)
    , _inputController(_outputController,
        *this,
        _inputBuffer)
    , _presenter(output, userName)
    , _verifier(_presenter)
{
}


void Terminal::ReceivedCharCallback(char c)
{
    _inputController.ReceivedCharCallback(c);
}

void Terminal::ReceivedStringCallback(const char *string)
{
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