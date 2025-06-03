#include "OutputController.hpp"
#include <cstring>

using namespace mock;

OutputController::OutputController(size_t size)
    : line(size)
{
    previousLine = new char[size + 1];
}

OutputController::~OutputController()
{
    delete[] previousLine;
}

void OutputController::PutChar(char c)
{
    line.put(c);
}

void OutputController::PutString(const char *string)
{
    line.putString(string);
}

void OutputController::MoveCursorLeft(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.moveCursorLeft();
}

void OutputController::MoveCursorRight(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.moveCursorRight();
}

void OutputController::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
    {
        line.moveCursorLeft();
        line.remove();
    }
}

void OutputController::Delete(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.remove();
}

void OutputController::NewLine()
{
    std::strcpy(previousLine, line.data());
    line.clear();
}

void OutputController::ClearScreen()
{
    previousLine[0] = '\0';
    line.clear();
}
