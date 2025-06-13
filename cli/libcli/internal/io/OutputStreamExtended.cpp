#include "OutputStreamExtended.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli;
using namespace cli::internal;
using namespace cli::internal::io;

OutputStreamExtended::OutputStreamExtended(OutputStream& output)
    : base(output)
{
}

OutputStreamExtended& OutputStreamExtended::operator<<(const formatspec::Repeated& format)
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

void OutputStreamExtended::moveCursorLeft(unsigned int times)
{
    while(times > 0)
    {
        auto moves = (times > ControlSequence::MAX_ARROW_REPEAT) ? ControlSequence::MAX_ARROW_REPEAT : times;
        write(ControlSequence(ControlSequence::Type::ARROW_LEFT, moves).getData().data());
        times -= moves;
    }
}

void OutputStreamExtended::moveCursorRight(unsigned int times)
{
    while(times > 0)
    {
        auto moves = (times > ControlSequence::MAX_ARROW_REPEAT) ? ControlSequence::MAX_ARROW_REPEAT : times;
        write(ControlSequence(ControlSequence::Type::ARROW_RIGHT, moves).getData().data());
        times -= moves;
    }
}

void OutputStreamExtended::backspace(unsigned int times)
{
    for(auto i = 0U; i < times; i++)
        write(ControlChar::BACKSPACE);
}

void OutputStreamExtended::putDelete(unsigned int times)
{
    write(ControlSequence(ControlSequence::Type::DELETE, times).getData());
}