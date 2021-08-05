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

void OutputController::MoveCursorLeft(unsigned int times)
{
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowLeft, times).Data());
}

void OutputController::MoveCursorRight(unsigned int times)
{
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowRight, times).Data());
}

void OutputController::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        _output.PutChar(ControlChar::BACKSPACE);
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

void OutputController::ClearLine()
{
    _output.PutString(ControlSequence(ControlSequence::Type::ClearLine).Data());
}

void OutputController::ClearToEndOfLine()
{
    _output.PutString(ControlSequence(ControlSequence::Type::ClearToEndOfLine).Data());
}