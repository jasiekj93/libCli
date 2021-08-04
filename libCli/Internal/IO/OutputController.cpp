#include "OutputController.hpp"
#include <libCli/Internal/IO/ControlChar.hpp>

using namespace Cli::Internal::IO;

OutputController::OutputController(IOutput &output)
    : _output(output)
{
}


void OutputController::PutChar(char c)
{
    _output.PutChar(c);
}

void OutputController::PutString(const char *string)
{
    _output.PutString(string);
}

void OutputController::MoveCursorLeft()
{
    _output.PutString(ControlChar(ControlChar::Type::ArrowLeft).Data());
}

void OutputController::MoveCursorRight()
{
    _output.PutString(ControlChar(ControlChar::Type::ArrowRight).Data());
}

void OutputController::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        _output.PutChar(DELETE_CHAR);
}

void OutputController::Delete(unsigned int times)
{

    for(unsigned int i = 0; i < times; i++)
    {
        _output.PutString(ControlChar(ControlChar::Type::Delete).Data());
    }
}

void OutputController::NewLine()
{
    _output.PutChar('\n');
    _output.PutChar('\r');
}

void OutputController::ClearScreen()
{
    _output.PutChar('\f');
}