#include "OutputControllerExtended.hpp"

using namespace mock;

OutputControllerExtended::OutputControllerExtended()
{
}

cli::OutputController& OutputControllerExtended::operator<<(const cli::internal::io::formatspec::Repeated& format)
{
    switch (format.type) 
    {
    case cli::internal::io::formatspec::Type::CURSOR_LEFT:
        moveCursorLeft(format.times);
        break;
    case cli::internal::io::formatspec::Type::CURSOR_RIGHT:
        moveCursorRight(format.times);
        break;
    case cli::internal::io::formatspec::Type::BACKSPACE:
        backspace(format.times);
        break;
    case cli::internal::io::formatspec::Type::DELETE:
        putDelete(format.times);
        break;
    default:
        break;
    }

    return *this;
}

void OutputControllerExtended::moveCursorLeft(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        base.line.moveCursorLeft();
}

void OutputControllerExtended::moveCursorRight(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        base.line.moveCursorRight();
}

void OutputControllerExtended::backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
    {
        base.line.moveCursorLeft();
        base.line.remove();
    }
}

void OutputControllerExtended::putDelete(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        base.line.remove();
}