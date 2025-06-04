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
    _output.putChar(c);
}

void OutputControllerImpl::PutString(const char *string)
{
    _output.putString(string);
}

void OutputControllerImpl::MoveCursorLeft(unsigned int times)
{
    _output.putString(ControlSequence(ControlSequence::Type::ArrowLeft, times).Data());
}

void OutputControllerImpl::MoveCursorRight(unsigned int times)
{
    _output.putString(ControlSequence(ControlSequence::Type::ArrowRight, times).Data());
}

void OutputControllerImpl::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        _output.putChar(ControlChar::BACKSPACE);
}

void OutputControllerImpl::Delete(unsigned int times)
{
    //not used
}

void OutputControllerImpl::NewLine()
{
    _output.putChar('\r');
    _output.putChar('\n');
}

void OutputControllerImpl::ClearScreen()
{
    _output.putChar('\f');
}