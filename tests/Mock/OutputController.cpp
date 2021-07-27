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

void OutputController::MoveCursorLeft()
{
    line.MoveCursorLeft();
}

void OutputController::MoveCursorRight()
{
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

void OutputController::Delete(unsigned int times)
{
    for(unsigned int i = 0; i < times; i++)
        line.Delete();
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
