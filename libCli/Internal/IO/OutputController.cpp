#include "OutputController.hpp"
#include <libCli/Internal/IO/ControlSequence.hpp>
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
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowLeft).Data());
}

void OutputController::MoveCursorRight()
{
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowRight).Data());
}

void OutputController::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        _output.PutChar(ControlChar::BACKSPACE);
}

void OutputController::Delete(unsigned int times)
{
    //not used
}

void OutputController::NewLine()
{
    _output.PutChar('\r');
    _output.PutChar('\n');
}

void OutputController::ClearScreen()
{
    _output.PutChar('\f');
}