#include "OutputControllerImpl.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli;
using namespace cli::internal;
using namespace cli::internal::io;

OutputControllerImpl::OutputControllerImpl(Output& output)
    : _output(output)
{
}


void OutputControllerImpl::PutChar(char c)
{
    _output.PutChar(c);
}

void OutputControllerImpl::PutString(const char *string)
{
    _output.PutString(string);
}

void OutputControllerImpl::MoveCursorLeft(unsigned int times)
{
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowLeft, times).Data());
}

void OutputControllerImpl::MoveCursorRight(unsigned int times)
{
    _output.PutString(ControlSequence(ControlSequence::Type::ArrowRight, times).Data());
}

void OutputControllerImpl::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        _output.PutChar(ControlChar::BACKSPACE);
}

void OutputControllerImpl::Delete(unsigned int times)
{
    //not used
}

void OutputControllerImpl::NewLine()
{
    _output.PutChar('\r');
    _output.PutChar('\n');
}

void OutputControllerImpl::ClearScreen()
{
    _output.PutChar('\f');
}