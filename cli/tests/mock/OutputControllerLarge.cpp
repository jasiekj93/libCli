#include "OutputControllerLarge.hpp"
#include <cstring>

using namespace mock;

OutputControllerLarge::OutputControllerLarge()
{
}

cli::OutputController& OutputControllerLarge::operator<<(char c)
{
    line.push_back(c);
    return *this;
}

cli::OutputController& OutputControllerLarge::operator<<(etl::string_view string)
{
    line.insert(line.end(), string.begin(), string.end());
    return *this;
}

cli::OutputController& OutputControllerLarge::operator<<(const cli::formatspec::Base& format)
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

void OutputControllerLarge::newLine()
{
    line.push_back('\r');
    line.push_back('\n');
}

void OutputControllerLarge::clearScreen()
{
    line.clear();
}
