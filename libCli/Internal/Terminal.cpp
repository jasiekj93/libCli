#include "Terminal.hpp"

using namespace Cli;
using namespace Cli::Internal;

Terminal::Terminal(IOutput &output,
            size_t depth)
    : _inputBuffer(Configuration::MAX_COMMAND_LENGTH, depth)
    , _outputController(output)
    , _inputController(_outputController,
        *this,
        _inputBuffer)
    , _verifier()
    , _presenter(output)
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
        _presenter.InvalidCommandFormat();
        return;
    }

    auto status = _verifier.Verify(command);

    switch(status)
    {
        case CommandVerifier::Status::Help:
            return _presenter.Help(command);
        case CommandVerifier::Status::InvalidArgument:
            return _presenter.InvalidArgument(command.GetName());
        case CommandVerifier::Status::InvalidArgumentType:
            return _presenter.InvalidArgumentType(command.GetName());
        case CommandVerifier::Status::NoMandatoryArguments:
            return _presenter.NoMandatoryArguments(command.GetName());
        case CommandVerifier::Status::Unknown:
            return _presenter.UnknownCommand(command.GetName());
        case CommandVerifier::Status::Ok:
            return _observer.
    }
}
