#include "OutputControllerExtendedImpl.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli;
using namespace cli::internal;
using namespace cli::internal::io;

OutputControllerExtendedImpl::OutputControllerExtendedImpl(Output& output)
    : base(output)
    , output(output)
{
}

OutputController& OutputControllerExtendedImpl::operator<<(const formatspec::Repeated& format)
{
    switch (format.type) 
    {
    case formatspec::Type::CURSOR_LEFT:
        moveCursorLeft(format.times);
        break;
    case formatspec::Type::CURSOR_RIGHT:
        moveCursorRight(format.times);
        break;
    case formatspec::Type::BACKSPACE:
        backspace(format.times);
        break;
    case formatspec::Type::DELETE:
        putDelete(format.times);
        break;
    default:
        break;
    }

    return *this;
}

void OutputControllerExtendedImpl::moveCursorLeft(unsigned int times)
{
    output.write(ControlSequence(ControlSequence::Type::ARROW_LEFT, times).getData().data());
}

void OutputControllerExtendedImpl::moveCursorRight(unsigned int times)
{
    output.write(ControlSequence(ControlSequence::Type::ARROW_RIGHT, times).getData().data());
}

void OutputControllerExtendedImpl::backspace(unsigned int times)
{
    for(auto i = 0U; i < times; i++)
        output.write(ControlChar::BACKSPACE);
}

void OutputControllerExtendedImpl::putDelete(unsigned int times)
{
    output.write(ControlSequence(ControlSequence::Type::DELETE, times).getData());
}