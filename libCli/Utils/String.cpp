#include "String.hpp"
#include <cctype>

using namespace Cli;
using namespace Cli::Utils;

CharSpan String::FindWord(const char *string)
{
    if(string == nullptr)
        return { nullptr, 0 };

    while((*string != '\0') &&
        (std::isspace(*string) != 0))
        string++;

    if(*string == '\0')
        return { nullptr, 0 };

    size_t size = 0;

    while((*string != '\0') &&
        (std::isgraph(*string) != 0))
        size++;

    return { string, size };
}