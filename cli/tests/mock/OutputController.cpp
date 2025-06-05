#include "OutputController.hpp"
#include <cstring>

using namespace mock;

OutputController::OutputController()
{
}

void OutputController::putChar(char c)
{
    line.put(c);
}

void OutputController::putString(etl::string_view string)
{
    line.putString(string.data());
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
