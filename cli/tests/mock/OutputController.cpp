#include "OutputController.hpp"
#include <cstring>

using namespace mock;

OutputController::OutputController()
{
}

OutputController& OutputController::operator<<(char c)
{
    line.put(c);
    return *this;
}

OutputController& OutputController::operator<<(etl::string_view string)
{
    line.putString(string.data());
    return *this;
}

OutputController& OutputController::operator<<(const cli::internal::io::formatspec::Base& format)
{
    switch (format.type) 
    {
    case cli::internal::io::formatspec::Type::CURSOR_LEFT:
        moveCursorLeft(1);
        break;
    case cli::internal::io::formatspec::Type::CURSOR_RIGHT:
        moveCursorRight(1);
        break;
    case cli::internal::io::formatspec::Type::BACKSPACE:
        backspace(1);
        break;
    case cli::internal::io::formatspec::Type::DELETE:
        putDelete(1);
        break;
    case cli::internal::io::formatspec::Type::NEW_LINE:
        newLine();
        break;
    case cli::internal::io::formatspec::Type::CLEAR_SCREEN:
        clearScreen();
        break;
    case cli::internal::io::formatspec::Type::FLUSH:
        // Flush is not used in this implementation
        break;
    
    default:
        break;
    }

    return *this;
}

OutputController& OutputController::operator<<(const cli::internal::io::formatspec::Repeated& format)
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
    case cli::internal::io::formatspec::Type::NEW_LINE:
        newLine();
        break;
    case cli::internal::io::formatspec::Type::CLEAR_SCREEN:
        clearScreen();
        break;
    case cli::internal::io::formatspec::Type::FLUSH:
        // Flush is not used in this implementation
        break;

    default:
        break;
    }

    return *this;
}

void OutputController::moveCursorLeft(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.moveCursorLeft();
}

void OutputController::moveCursorRight(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.moveCursorRight();
}

void OutputController::backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
    {
        line.moveCursorLeft();
        line.remove();
    }
}

void OutputController::putDelete(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.remove();
}

void OutputController::newLine()
{
    previousLine = line.getData();
    line.clear();
}

void OutputController::clearScreen()
{
    previousLine.clear();
    line.clear();
}
