#include "OutputControllerImpl.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli;
using namespace cli::internal;
using namespace cli::internal::io;

OutputControllerImpl::OutputControllerImpl(Output& output)
    : output(output)
{
}


void OutputControllerImpl::putChar(char c)
{
    output.write(c);
}

void OutputControllerImpl::putString(etl::string_view string)
{
    output.write(string.data());
}

void OutputControllerImpl::moveCursorLeft(unsigned int times)
{
    output.write(ControlSequence(ControlSequence::Type::ARROW_LEFT, times).getData().data());
}

void OutputControllerImpl::moveCursorRight(unsigned int times)
{
    output.write(ControlSequence(ControlSequence::Type::ARROW_RIGHT, times).getData().data());
}

void OutputControllerImpl::backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        output.write(ControlChar::BACKSPACE);
}

void OutputControllerImpl::putDelete(unsigned int times)
{
    //not used
}

void OutputControllerImpl::newLine()
{
    output.write('\r');
    output.write('\n');
}

void OutputControllerImpl::clearScreen()
{
    output.write('\f');
}