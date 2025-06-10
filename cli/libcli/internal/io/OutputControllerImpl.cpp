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

OutputController& OutputControllerImpl::operator<<(char c)
{
    output.write(c);
    return *this;
}

OutputController& OutputControllerImpl::operator<<(etl::string_view string)
{
    output.write(string);
    return *this;
}

OutputController& OutputControllerImpl::operator<<(const formatspec::Base& format)
{
    switch (format.type) 
    {
    case formatspec::Type::CURSOR_LEFT:
        moveCursorLeft(1);
        break;
    case formatspec::Type::CURSOR_RIGHT:
        moveCursorRight(1);
        break;
    case formatspec::Type::BACKSPACE:
        backspace(1);
        break;
    case formatspec::Type::DELETE:
        putDelete(1);
        break;
    case formatspec::Type::NEW_LINE:
        newLine();
        break;
    case formatspec::Type::CLEAR_SCREEN:
        clearScreen();
        break;
    case formatspec::Type::FLUSH:
        // Flush is not used in this implementation
        break;
    
    default:
        break;
    }

    return *this;
}

OutputController& OutputControllerImpl::operator<<(const formatspec::Repeated& format)
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
    case formatspec::Type::NEW_LINE:
        newLine();
        break;
    case formatspec::Type::CLEAR_SCREEN:
        clearScreen();
        break;
    case formatspec::Type::FLUSH:
        // Flush is not used in this implementation
        break;
    default:
        break;
    }

    return *this;
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