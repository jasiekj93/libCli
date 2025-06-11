#include "OutputController.hpp"
#include <cstring>

using namespace mock;

OutputController::OutputController()
{
}

OutputController& OutputController::operator<<(char c)
{
    line.push(c);
    return *this;
}

OutputController& OutputController::operator<<(etl::string_view string)
{
    line.push(string.data());
    return *this;
}

OutputController& OutputController::operator<<(const cli::formatspec::Base& format)
{
    switch (format.type) 
    {
    case cli::formatspec::Type::NEW_LINE:
        newLine();
        break;
    case cli::formatspec::Type::CLEAR_SCREEN:
        clearScreen();
        break;
    case cli::formatspec::Type::FLUSH:
        // Flush is not used in this implementation
        break;
    
    default:
        break;
    }

    return *this;
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
