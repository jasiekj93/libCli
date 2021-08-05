#include "OutputController.hpp"
#include <cstring>

using namespace Mock;

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
    line.Put(c);
}

void OutputController::PutString(const char *string)
{
    line.PutString(string);
}

void OutputController::MoveCursorLeft(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.MoveCursorLeft();
}

void OutputController::MoveCursorRight(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.MoveCursorRight();
}

void OutputController::Backspace(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
    {
        line.MoveCursorLeft();
        line.Delete();
    }
}

void OutputController::NewLine()
{
    std::strcpy(previousLine, line.Data());
    line.Clear();
}

void OutputController::ClearScreen()
{
    previousLine[0] = '\0';
    line.Clear();
}

void OutputController::ClearLine()
{
    line.Clear();
}

void OutputController::ClearToEndOfLine()
{
    line.ClearFromCursor();
}
