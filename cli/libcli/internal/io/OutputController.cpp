#include "OutputController.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli::internal::io;

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